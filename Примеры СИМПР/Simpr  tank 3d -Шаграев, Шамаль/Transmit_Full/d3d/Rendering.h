#pragma once
// Renderer dependent declarations.
#include <d3d9.h>
#include <d3dx9shader.h>
#include <d3dx9.h>
#include <memory>
#include "TVertexFormat.h"
#include <hash_map>
#include <boost/bind.hpp>
#include <boost/function.hpp>

// Приоритеты пересоздания ресурсов.
enum ResRecreationPriority
{
	PR_Default = 0,
	PR_BaseTexture = 999
};

class IResource
{
	stdext::hash_map<std::string,IResource*>::iterator Where;
	friend class ResourceManager;
	int		RefCount;
	bool	IsRegistered;
public:
	IResource() : RefCount(0), IsRegistered(false), SortIndex(PR_Default)
	{}

	IResource& operator=( const IResource& Other )
	{
		RefCount = 0;
		IsRegistered = false;
		SortIndex = Other.SortIndex;
		return *this;
	}

	// Делать всю основную работу по инициализации здесь (не в конструкторе).
	virtual void Create( LPDIRECT3DDEVICE9 pDevice ) = 0;
	// Вызывается при потере устройства.
	virtual void Destroy() = 0;
	// Контроль времени жизни объектов.
	void AddRef()
	{
		++RefCount;
	}
	void Release()
	{
		if( --RefCount <= 0 )
			delete this;
	}
	// Cортировка по приоритету.
	bool operator<( const IResource* Rhs ) const
	{
		return SortIndex > Rhs->SortIndex;
	}
protected:
	// Приоритет порядка пересоздания объектов.
	int SortIndex;
	// Деструкторы производных классов вызывают свой Destroy()
	// через ResourceManager::Unregister.
	virtual ~IResource()
	{}
};

class ResBaseTexture : public IResource
{
protected:
	LPDIRECT3DBASETEXTURE9	pTexture;
	// Здесь хранятся текстурные параметры.
	D3DXIMAGE_INFO		ImgInfo;

	ResBaseTexture() : pTexture(0)
	{
		SortIndex = PR_BaseTexture;
	}
	virtual ~ResBaseTexture();
public:
	LPDIRECT3DBASETEXTURE9 GetHandle(){ return pTexture; }
	void SetForRendering( int Stage );
	virtual void Destroy()
	{
		if( pTexture )
		{
			pTexture->Release();
			pTexture = 0;
		}
	}
};

class ResTexture : public ResBaseTexture
{
protected:
	std::string			PathName;
public:
	ResTexture( const std::string& TexturePathName )
		: PathName(TexturePathName)
	{}
	virtual void Create( LPDIRECT3DDEVICE9 pDevice );
};

class ResVolume : public ResBaseTexture
{
protected:
	std::string			PathName;
public:
	ResVolume( const std::string& TexturePathName )
		: PathName(TexturePathName)
	{}
	virtual void Create( LPDIRECT3DDEVICE9 pDevice );
};

class ResRenderTarget : public ResBaseTexture
{
	int			Width;
	int			Height;
	D3DFORMAT	Format;
public:
	ResRenderTarget( int BufferWidth, int BufferHeight, D3DFORMAT BufferFormat )
		: Width(BufferWidth), Height(BufferHeight), Format(BufferFormat)
	{}
	virtual void Create( LPDIRECT3DDEVICE9 pDevice );
	LPDIRECT3DSURFACE9 GetSurface();
};

class FontVertex
{
public:
	enum { StreamNumber = 0 };
	float	X, Y;
	float	U, V;
	static D3DVERTEXELEMENT9 (&GetVertexFormat())[3]
	{
		static D3DVERTEXELEMENT9 FormatString[] =
		{
			{0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};
		return FormatString;
	};
};

// Хранит данные для вызова DIP.
struct MaterialBin
{
	int StartIndex;
	int NumIndices;
	int MinVertexIndex, NumVertices;
	int NumPrimitives;
	int BaseVertexIndex;
	
	void Clear()
	{
		StartIndex = 0;
		NumIndices = 0;
		MinVertexIndex = 0;
		NumVertices = 0;
		NumPrimitives = 0;
		BaseVertexIndex = 0;
	}
	// Добавляет данные для треугольников.
	void Add( int FirstVertex, int NumberOfVertices, int NumberOfPrimitives )
	{
		if( NumVertices )
		{
			int MinVertInd = MinVertexIndex;
			int MaxVertInd = MinVertInd + NumVertices - 1;
			if( FirstVertex < MinVertInd )
				MinVertInd = FirstVertex;
			if( (FirstVertex + NumberOfVertices - 1) > MaxVertInd )
				MaxVertInd = FirstVertex + NumberOfVertices - 1;
			MinVertexIndex = MinVertInd;
			NumVertices = MaxVertInd - MinVertInd + 1;
		}
		else
		{
			MinVertexIndex = FirstVertex;
			NumVertices = NumberOfVertices;
		}

		NumPrimitives += NumberOfPrimitives;
		NumIndices += 3*NumberOfPrimitives;
	}

	MaterialBin() 
	{
		Clear();
	}
};

class ResourceManager
{
	stdext::hash_map<std::string, IResource*>	ResMap;
	LPDIRECT3DDEVICE9							pDevice;
	LPDIRECT3D9									pD3D;
	D3DPRESENT_PARAMETERS						PresentParams;
	LPDIRECT3DSURFACE9							pOldRT;

	struct ScreenVertex
	{
		D3DXVECTOR4		Pos;
		D3DXVECTOR2		TexCoord;
	};

	ResourceManager();
	~ResourceManager();
	ResourceManager( const ResourceManager& );
public:
	// Если данные ресурс существует, то он будет возвращен,
	// вновь созданный не будет инициализироваться и будет удален.
	// TODO: Сделать Release-метод вместо delete для возможности размещать объекты в стеке?
	template< class T >
	T *Register( T *Resource, const std::string& ResName )
	{
		if( !pDevice )
			AppError() << "Error on creation of " << ResName << " : resource manager is not initialized.";
		if( ResMap.find( ResName ) != ResMap.end() )
		{
			Resource->Release();
			IResource *Res = ResMap[ResName];
			Res->RefCount++;
			return static_cast<T*>( Res );
		}
		Resource->Create( pDevice );
		Resource->RefCount++;
		Resource->IsRegistered = true;
		Resource->Where = ResMap.insert( std::make_pair(ResName,Resource) ).first;
		return Resource;
	}
	template< class T >
	T *GetResourceByName( const std::string& ResName )
	{
		if( ResMap.find( ResName ) != ResMap.end() )
		{
			return static_cast<T*>( ResMap[ResName] );
		}
		return 0;
	}

	static ResourceManager&		GetInstance();

	ResRenderTarget		*CreateRenderTarget( D3DFORMAT Format = D3DFMT_A16B16G16R16F );
	void				SetRenderTarget( ResRenderTarget *RT );
	void				DrawFullScreenQuadF( int Dummy );
	void				DrawFullScreenQuad( class ResMaterial *Mat );
	void				Unregister( IResource *Resource );
	void				Init( LPDIRECT3DDEVICE9 pDevice9, LPDIRECT3D9 pD3D9, const D3DPRESENT_PARAMETERS& PParams );
	LPDIRECT3DDEVICE9	GetDevice();
	void				OnDeviceLost( D3DPRESENT_PARAMETERS *PParams );
	void				ReleaseAll();
};

// Вспомогательный класс для хранения общих параметров.
// Хранит dummy-эффект для каждого разделяемого параметра.
class SharedParameterList : public IResource
{
	struct DummyParameter
	{
		LPD3DXEFFECT	pFX;	// Dummy-эффект.
		D3DXHANDLE		Param;	// Dummy-параметр.
	};
	stdext::hash_map<std::string,DummyParameter> DummyParamList;
	LPD3DXEFFECTPOOL	pSharedPool;
	LPDIRECT3DDEVICE9	pDevice;
	friend class		ResMaterial;
public:
	SharedParameterList() : pSharedPool(0)
	{}
	virtual void Create( LPDIRECT3DDEVICE9 pDevice9 )
	{
		if( !pSharedPool )
			D3DXCreateEffectPool( &pSharedPool );
		else
		{ // Восстановление после device lost.
			for( stdext::hash_map<std::string,DummyParameter>::iterator It=DummyParamList.begin();
				It != DummyParamList.end();
				++It )
			{
				It->second.pFX->OnResetDevice();
			}
		}
		pDevice = pDevice9;
	}
	virtual void Destroy()
	{ // Обработка device-lost. Настоящее освобождение ресурсов в деструкторе.
		for( stdext::hash_map<std::string,DummyParameter>::iterator It=DummyParamList.begin();
			It != DummyParamList.end();
			++It )
		{
			if( It->second.pFX )
				It->second.pFX->OnLostDevice();
		}
	}
	// Cоздаем и регистрируем dymmy-объект.
	void RegisterParameter( const std::string& ParamName, const std::string& ParamType )
	{
		if( DummyParamList.find( ParamName ) == DummyParamList.end() )
		{
			std::string EffectString("shared ");
			EffectString += ParamType + " " + ParamName + ";technique Empty{pass P0{}}";
			LPD3DXEFFECT pEffect = 0;
			HRESULT HR;
			LPD3DXBUFFER pErrorBuf = 0;
			HR = D3DXCreateEffect( pDevice, EffectString.c_str(), EffectString.length()+1, NULL, NULL,
				0, pSharedPool, &pEffect, &pErrorBuf );
			if( FAILED(HR) )
			{
				DXError(HR, (const char*)pErrorBuf->GetBufferPointer());
			}
			DummyParameter Param;
			Param.pFX = pEffect;
			Param.Param = pEffect->GetParameterByName( NULL, ParamName.c_str() );
			DummyParamList[ ParamName ] = Param;
		}
	}
	void SetMatrix( const char *Name, const D3DXMATRIX& M )
	{
		DummyParameter *Param;
		FindParameter( Name, Param );
		if( Param )
			Param->pFX->SetMatrix( Param->Param, &M ); 
		else
			assert( 0 );
	}
	void SetVector( const char *Name, const Vector3& V )
	{
		DummyParameter *Param;
		FindParameter( Name, Param );
		if( Param )
			Param->pFX->SetValue( Param->Param, &V, sizeof(Vector3) );
		else
			assert( 0 );
	}
	void SetFloat( const char *Name, float F )
	{
		DummyParameter *Param;
		FindParameter( Name, Param );
		if( Param )
			Param->pFX->SetFloat( Param->Param, F );
		else
			assert( 0 );
	}
private:
	void FindParameter( const char *Name, DummyParameter* &Param )
	{
		stdext::hash_map<std::string,DummyParameter>::iterator It = DummyParamList.find( Name );
		if( It != DummyParamList.end() )
			Param = &It->second;
		else
			Param = 0;
	}
	~SharedParameterList()
	{ // Освобождение ресурсов.
		for( stdext::hash_map<std::string,DummyParameter>::iterator It=DummyParamList.begin();
			It != DummyParamList.end();
			++It )
		{
			It->second.pFX->Release();
			It->second.pFX = 0;
		}
		if( pSharedPool )
		{
			pSharedPool->Release();
			pSharedPool = 0;
		}
		ResourceManager::GetInstance().Unregister( this );
	}
};

//------------------------------------------------------------------------------------------------------------

// Интерфейс генератора процедурных текстур.
// Допускает создание мелких копий.
class TextureGenerator
{
public:
	virtual TextureGenerator *Replicate() const = 0;
	virtual void FillTexture( LPDIRECT3DTEXTURE9 pTexture ) = 0;
	virtual void FillVolumeTexture( LPDIRECT3DVOLUMETEXTURE9 pVolTexture ) = 0;
	virtual ~TextureGenerator()
	{}
};

class TSTextureGenerator : public TextureGenerator
{
protected:
	LPD3DXTEXTURESHADER	pTexShader;
public:
	TSTextureGenerator( const std::string& ShaderPath ) : pTexShader(0)
	{
		HRESULT HR;
		LPD3DXBUFFER pShaderBuf = 0, pErrMsg = 0;
		HR = D3DXCompileShaderFromFile( ShaderPath.c_str(),
			NULL,
			NULL,
			"ColorFill",
			"tx_1_0",
			0,
			&pShaderBuf,
			&pErrMsg,
			0 );
		if( FAILED(HR) )
		{
			if( pErrMsg )
				DXError(HR, "failed on D3DXCompileShaderFromFile : " << (const char*)pErrMsg->GetBufferPointer() );
			else
				DXError(HR, "file not found: " << ShaderPath.c_str() );
		}

		HR = D3DXCreateTextureShader( (const DWORD*)pShaderBuf->GetBufferPointer(), &pTexShader );
		if( FAILED(HR) )
		{
			DXError(HR, "failed on D3DXCreateTextureShader");
		}
	}

	virtual void FillTexture( LPDIRECT3DTEXTURE9 pTexture )
	{
		HRESULT HR;
		if( FAILED(HR=D3DXFillTextureTX( pTexture, pTexShader )) )
		{
			DXError(HR, "failed on D3DXFillTextureTX");
		}
	}

	virtual void FillVolumeTexture( LPDIRECT3DVOLUMETEXTURE9 pVolTexture )
	{
		assert( 0 );
	}

	// Делаем мелкую копию.
	virtual TextureGenerator* Replicate() const
	{
		pTexShader->AddRef();
		return new TSTextureGenerator( *this );
	}

	~TSTextureGenerator()
	{
		if( pTexShader )
		{
			pTexShader->Release();
			pTexShader = 0;
		}
	}
};

class TSVolumeGenerator : public TSTextureGenerator
{
public:
	TSVolumeGenerator( const std::string& ShaderPath ) : TSTextureGenerator(ShaderPath)
	{}

	virtual void FillTexture( LPDIRECT3DTEXTURE9 pTexture )
	{
		assert( 0 );
	}
	virtual void FillVolumeTexture( LPDIRECT3DVOLUMETEXTURE9 pVolTexture )
	{
		HRESULT HR;
		if( FAILED(HR=D3DXFillVolumeTextureTX( pVolTexture, pTexShader )) )
		{
			DXError(HR, "failed on D3DXFillVolumeTextureTX");
		}
	}
	virtual TextureGenerator* Replicate() const
	{
		pTexShader->AddRef();
		return new TSVolumeGenerator( *this );
	}
};

//--------------------------------------------------------------------------------------------------

// Процедуральная текстура.
class ResProcTexture : public ResBaseTexture
{
	TextureGenerator	*LocalTexGen;
public:
	ResProcTexture( int Width, int Height, int MipLevels, TextureGenerator& TexGen );
	virtual void Create( LPDIRECT3DDEVICE9 pDevice );
	virtual void Destroy();
protected:
	~ResProcTexture();
};

class ResProcVolumeTexture : public ResBaseTexture
{
	TextureGenerator *LocalTexGen;
	std::string CacheFile;
public:
	virtual void Create( LPDIRECT3DDEVICE9 pDevice );
	virtual void Destroy();
	ResProcVolumeTexture( int Width, int Height, int Depth, int MipLevels, TextureGenerator& TexGen, const char *CacheFilePath = 0 );
protected:
	~ResProcVolumeTexture();
};

//--------------------------------------------------------------------------------------------------

// Содержит функции для вызова процедуры рисования:
// функцию инициализации (устанавливает необходимые буферы)
// и собственно функцию рисования (можно задать тип параметра).
template< class DrawArg >
class DrawCallDelegate
{
	boost::function<void(void)> SetupCall;
	boost::function<void(DrawArg)> DrawCall;

public:
	template< class T >
	DrawCallDelegate( T* pMesh, void(T::*SetupDrawFn)(), void(T::*DrawFn)(DrawArg) )
		: SetupCall(boost::bind( SetupDrawFn, pMesh )),
		DrawCall(boost::bind( DrawFn, pMesh, _1 ))
	{
	}

	DrawCallDelegate( boost::function<void(void)> SetupDrawFn, boost::function<void(DrawArg)> DrawFn )
		: SetupCall( boost::bind( SetupDrawFn ) ),
		DrawCall( boost::bind( DrawFn, _1 ) )
	{
	}

	void SetupDrawCall()
	{
		SetupCall();
	}

	void Draw( DrawArg Arg )
	{
		DrawCall( Arg );
	}
};