#pragma once

#include "Rendering.h"
#include "DynMesh.h"
#include <cfloat>


// Параметр шейдера.
class IShaderParam
{
	friend class	ResMaterial;
	D3DXHANDLE		hParam;
public:
	IShaderParam() : hParam(0) {}
	void		AttachTo( class ResMaterial *Mat, const char *VarName );
	virtual		const void *GetData() const = 0;
	virtual		int GetSize() const = 0;
};

//------------------------------------------------------------------------------------------------------------

class ResMaterial : public IResource
{
	std::string				Name;
	LPD3DXEFFECT			pFX;
	D3DXHANDLE				TexParam;
	DWORD					ShaderFlags;
	bool					WasCreated;
	SharedParameterList		*SharedParams;
	// Параметры материала.
	std::vector< 
		std::pair<D3DXHANDLE,ResBaseTexture*>
				>			TextureList;
	BOOL					Translucent;
	std::string				TechName;
	D3DXHANDLE				hTechnique;
	// Прототип, если текущий создан на основе другого.
	ResMaterial				*Proto;

#ifdef NOCACHE
	static const int UseTextureCache = 0;
	static const int UseEffectCache = 0;
#else
	static const int UseTextureCache = 1;
	static const int UseEffectCache = 1;
#endif

public:
	ResMaterial( const std::string& MatName, SharedParameterList *SharedParameters = 0 )
		: Name(MatName),
		Proto(0),
		pFX(0),
		ShaderFlags(0),
		WasCreated(false),
		Translucent(false),
		SharedParams(SharedParameters),
		TechName("RenderScene"),
		hTechnique(0)
	{
	}

	// Создаем копию материала с техникой, отличной от стандартной.
	ResMaterial( ResMaterial *Base, const std::string& TechniqueName );

	void Create( LPDIRECT3DDEVICE9 pDevice );
	void Destroy()
	{
		if( pFX ) pFX->OnLostDevice();
	}
	void SetVectorParameter( const char *ParamName, const Vector3& V );
	void SetMatrixParameter( const char *ParamName, const D3DXMATRIX& M );
	void SetFloatParameter( const char *ParamName, float F );
	void AttachTexture( ResBaseTexture *Texture, unsigned int SamplerNum = 0 );

	// Устанавливает текстуру только на период одного draw сallа.
	void SetDiffuseMap( ResTexture *DiffMap, unsigned SamplerNum = 0 );

	void GetParameter( const char *VarName, IShaderParam* ShaderParam ) const;
	void SetParameter( IShaderParam& ShaderParam );


	// Рисует ResDynamicMesh без индексов.
	template<class VD> 
	void Draw( ResDynamicMesh<VD> *Mesh, int NumPrimitives )
	{
		Mesh->SetupDPCall();
		UINT NumPasses = 0;
		pFX->SetTechnique( hTechnique );
		pFX->Begin( &NumPasses, 0 );
		for( UINT i=0; i < NumPasses; i++ )
		{
			pFX->BeginPass( i );
			Mesh->DrawP( NumPrimitives );
			pFX->EndPass();
		}
		pFX->End();
	}
	// Рисует ResDynamicMesh с индексами.
	template<class VD> 
	void Draw( ResDynamicMesh<VD> *Mesh, MaterialBin *Bin )
	{
		Mesh->SetupDIPCall();
		UINT NumPasses = 0;
		pFX->SetTechnique( hTechnique );
		pFX->Begin( &NumPasses, 0 );
		for( UINT i=0; i < NumPasses; i++ )
		{
			pFX->BeginPass( i );
			Mesh->DrawIP( Bin );
			pFX->EndPass();
		}
		pFX->End();
	}

	template< class ArgType >
	void Draw( DrawCallDelegate<ArgType>& DrawDeleg, ArgType DrawArg )
	{
		DrawDeleg.SetupDrawCall();
		UINT NumPasses = 0;
		pFX->SetTechnique( hTechnique );
		pFX->Begin( &NumPasses, 0 );
		for( UINT i=0; i < NumPasses; i++ )
		{
			pFX->BeginPass( i );
			DrawDeleg.Draw( DrawArg );
			pFX->EndPass();
		}
		pFX->End();
	}
	// Предикат для поиска материалов.
	struct Cmp
	{
		const std::string& Etl;
		Cmp( const std::string& Etalone ) : Etl(Etalone)
		{}
		bool operator()( const ResMaterial* Mat )
		{
			return Mat->Name == Etl;
		}
	};
	friend struct Cmp;
	// Доступ к атрибутам.
	bool IsTranslucent() const
	{
		return !!Translucent;
	}
private:
	void ReadMaterialInfo();
	void SetTextures();
	void SetupTextures( const char *EffectFilePath );
	void SetupTexturesCG( const char *EffectFilePath );
	bool LookForCachedResource( const std::string& ResFullPath );
	void CreateCacheResourceDir( const std::string& ResFullPath );
	~ResMaterial();
};

//------------------------------------------------------------------------------------------------------------

template< typename T > class ShaderParam;

template<> class ShaderParam<float> : public IShaderParam
{
	float F;
public:
	ShaderParam& operator=( float Val )
	{
		F = Val;
		return *this;
	}
	virtual const void* GetData() const
	{
		return &F;
	}
	virtual int GetSize() const
	{
		return sizeof(F);
	}
};

template<> class ShaderParam<D3DXMATRIX> : public IShaderParam
{
	D3DXMATRIXA16 M;

public:
	ShaderParam& operator=( const D3DXMATRIX& Mat )
	{
		M = Mat;
		return *this;
	}
	D3DXMATRIX* GetMatPtr()
	{
		return &M;
	}
	virtual const void* GetData() const
	{
		return &M;
	}
	virtual int GetSize() const
	{
		return sizeof(M);
	}
};

template<> class ShaderParam<Vector3> : public IShaderParam
{
	Vector3	V;
public:
	ShaderParam& operator=( const Vector3& Vec )
	{
		V = Vec;
	}
	virtual const void* GetData() const
	{
		return &V;
	}
	virtual int GetSize() const
	{
		return sizeof(V);
	}
};