#include "ObjMain.h"
#include "Rendering.h"
#include "Material.h"
#include <boost/spirit.hpp>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <shlobj.h>

ResBaseTexture::~ResBaseTexture()
{
	ResourceManager::GetInstance().Unregister( this );
}

void ResBaseTexture::SetForRendering( int Stage )
{
	LPDIRECT3DDEVICE9 pDevice = ResourceManager::GetInstance().GetDevice();
	pDevice->SetSamplerState( Stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	pDevice->SetSamplerState( Stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	pDevice->SetTexture( Stage, pTexture );
}

void ResTexture::Create( LPDIRECT3DDEVICE9 pDevice )
{
	LPDIRECT3DTEXTURE9 pTex = 0;
	HRESULT HR;
	if( FAILED( HR=D3DXCreateTextureFromFileEx( pDevice,
					PathName.c_str(),
					0,
					0,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_DEFAULT,
					D3DX_DEFAULT,   // Fixme: Do we actually need this?
					D3DX_FILTER_BOX,
					0,
					&ImgInfo,
					NULL,
					&pTex )
				)
	) DXError(HR, " Unable to create the texture from file : " << PathName );

	pTexture = pTex;
}

void ResVolume::Create( LPDIRECT3DDEVICE9 pDevice )
{
	LPDIRECT3DVOLUMETEXTURE9 pVolTex = 0;
	HRESULT HR;
	if( FAILED( HR=D3DXCreateVolumeTextureFromFileEx(
					pDevice,
					PathName.c_str(),
					D3DX_DEFAULT,
					D3DX_DEFAULT,
					D3DX_DEFAULT,
					1,				// No mipmaps for volumes.
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_DEFAULT,
					D3DX_FILTER_NONE,
					D3DX_DEFAULT,
					0,
					&ImgInfo,
					NULL,
					&pVolTex )
				)
		) AppDXError( HR ) << " Unable to create the volume texture from file : " << PathName;

	pTexture = pVolTex;
}

void ResRenderTarget::Create( LPDIRECT3DDEVICE9 pDevice )
{
	LPDIRECT3DTEXTURE9 pTex = 0;
	HRESULT HR;
	if( FAILED(HR = pDevice->CreateTexture(
						Width,
						Height,
						1,
						D3DUSAGE_RENDERTARGET,
						Format,
						D3DPOOL_DEFAULT,
						&pTex,
						NULL )
				)
		) DXError(HR, "Unable to create render target texture" );
	pTexture = pTex;
}

LPDIRECT3DSURFACE9 ResRenderTarget::GetSurface()
{
	LPDIRECT3DSURFACE9 pSurfLev = 0;
	LPDIRECT3DTEXTURE9 pTex = static_cast<IDirect3DTexture9*>( pTexture );
	HRESULT HR = pTex->GetSurfaceLevel( 0, &pSurfLev );
	if( FAILED(HR) )
		DXError(HR, "Failed on IDirect3DTexture9::GetSurfaceLevel" );
	return pSurfLev;
}

//----------------------------------------------- ResMaterial --------------------------------------------------

void ResMaterial::Create( LPDIRECT3DDEVICE9 pDevice )
{
	HRESULT HR;
	if( WasCreated )
	{
		pFX->OnResetDevice();
		SetTextures();
	}
	else
	{
		LPD3DXBUFFER		pErrBuffer = 0;
		void				*EffBuffer = 0;
		int					EffBufferSize = 0;
		std::vector<char>	EffBuf;
		LPD3DXBUFFER		pEffectBuf = 0;

		// Пробуем загрузить эффект из кэша.
		std::string CachedFilePath = "EffectCache/";
		CachedFilePath += Name;
		std::fstream CompEffFile( CachedFilePath.c_str(), std::ios::in | std::ios::binary );
		if( UseEffectCache && !CompEffFile.fail() )
		{
			std::copy( 
				std::istreambuf_iterator<char>(CompEffFile),
				std::istreambuf_iterator<char>(),
				std::back_inserter( EffBuf )
				);

			EffBuffer = &EffBuf[0];
			EffBufferSize = EffBuf.size();
			CompEffFile.close();
		}
		else
		{
			// Компилируем эффект.
			LPD3DXEFFECTCOMPILER pEffCompiler = 0;
			HR = D3DXCreateEffectCompilerFromFile(
				Name.c_str(),
				NULL,
				NULL,
				ShaderFlags,
				&pEffCompiler,
				&pErrBuffer );
			if( FAILED(HR) )
			{
				if( pErrBuffer )
					DXError(HR, "D3DXCreateEffectFromFile error: " << (const char*)pErrBuffer->GetBufferPointer() );
				else
					DXError(HR, "File not found : " << Name );
			}

			HR = pEffCompiler->CompileEffect( ShaderFlags, &pEffectBuf, &pErrBuffer );
			if( FAILED(HR) )
			{
				DXError(HR, (const char*)pErrBuffer->GetBufferPointer() );
			}
		
			EffBuffer = pEffectBuf->GetBufferPointer();
			EffBufferSize = pEffectBuf->GetBufferSize();

			// Сохраняем скомпилированный эффект в кэш.
			if( UseEffectCache )
			{
				CreateCacheResourceDir( CachedFilePath );
				std::fstream OutpFile( CachedFilePath.c_str(), std::ios::out | std::ios::binary | std::ios::trunc );
				OutpFile.write( (char*)EffBuffer, EffBufferSize );
				OutpFile.close();
			}

			pEffCompiler->Release();
		}

		// Создаем эффект.
		HR = D3DXCreateEffect(
				pDevice,
				EffBuffer,
				EffBufferSize,
				NULL,
				NULL,
				ShaderFlags,
				SharedParams ? SharedParams->pSharedPool : NULL,
				&pFX,
				NULL );

		if( FAILED(HR) )
			DXError(HR, " D3DXCreateEffect failed." );

		SetupTextures( Name.c_str() );
		ReadMaterialInfo();

		hTechnique = pFX->GetTechniqueByName( TechName.c_str() );
		if( hTechnique == NULL )
			Error( "Cannot find default technique in : " << Name.c_str() << ", " << TechName.c_str() );
		WasCreated = true;
	}
}

// Создаем копию материала с техникой, отличной от стандартной.
// Такой прием сработает только для эффектов.
ResMaterial::ResMaterial( ResMaterial *Base, const std::string& TechniqueName )
{
	if( Base->Proto )
		Error( "Cannot create copy of copy: " << Base->Name << ", " << TechniqueName );
	*this = *Base;
	Base->AddRef();
	Proto = Base;
	AddRef();
	TechName = TechniqueName;
	hTechnique = pFX->GetTechniqueByName( TechniqueName.c_str() );
	if( hTechnique == NULL )
		Error( "Technique : " << TechniqueName << " not found in " << Name );
}

ResMaterial::~ResMaterial()
{
	if( Proto )
		Proto->Release();
	else
	{
		if( pFX )
		{
			pFX->Release();
			pFX = 0;
		}
		for( unsigned i = 0; i < TextureList.size(); i++ )
		{
			if( TextureList[i].second )
				TextureList[i].second->Release();
		}
		TextureList.clear();
		ResourceManager::GetInstance().Unregister( this );
	}
}

// Читаем параметры материала (поле MatParams) из файла эффектов.
void ResMaterial::ReadMaterialInfo()
{
	D3DXHANDLE ParamsBlock = pFX->GetParameterByName( NULL, "MatParams" );
	if( ParamsBlock )
	{
		D3DXHANDLE TranspFlag = pFX->GetAnnotationByName( ParamsBlock, "Translucent" );
		if( TranspFlag )
		{
			pFX->GetBool( TranspFlag, &Translucent );
		}
	}
}

// Устанавливает текстуру.
void ResMaterial::SetDiffuseMap( ResTexture *DiffMap, unsigned SamplerNum )
{
	// Устанавливаем на текстурную переменную по счету SamplerNum в исходном файле шейдера.
	if( DiffMap )
	{
		if( TextureList.size() > SamplerNum )
			pFX->SetTexture( TextureList[SamplerNum].first, DiffMap->GetHandle() );
		else
		{ // Переменная с таким номером не существует.
			assert( 0 );
		}
	}
}

void ResMaterial::SetFloatParameter( const char *ParamName, float F )
{
	D3DXHANDLE Param = pFX->GetParameterByName( NULL, ParamName );
	if( Param != NULL )
	{
		pFX->SetFloat( Param, F );
	}
	SetTextures();
}

void ResMaterial::SetVectorParameter( const char *ParamName, const Vector3& V )
{
	D3DXHANDLE Param = pFX->GetParameterByName( NULL, ParamName );
	if( Param != NULL )
	{
		pFX->SetValue( Param, &V, sizeof(V) );
	}
}

void ResMaterial::SetMatrixParameter( const char *ParamName, const D3DXMATRIX& M )
{
	D3DXHANDLE Param = pFX->GetParameterByName( NULL, ParamName );
	if( Param != NULL )
	{
		pFX->SetMatrix( Param, &M );
	}
}

using namespace boost::spirit;

static void AddString2Vector( std::vector<std::string> *SList, const char *First, const char *Last )
{
	SList->push_back( std::string( First, Last ) );
}

bool ResMaterial::LookForCachedResource( const std::string& ResFullPath )
{
	std::fstream CacheFile( ResFullPath.c_str(), std::ios::in | std::ios::binary );
	if( !CacheFile.fail() )
	{
		CacheFile.close();
		return true;
	}
	return false;
}

void ResMaterial::CreateCacheResourceDir( const std::string& ResFullPath )
{
	std::string Dir;
	for( unsigned int i=0; i < ResFullPath.length(); i++ )
	{
		Dir += ResFullPath[i];
		if( ResFullPath[i] == '/' || ResFullPath[i] == '\\' )
		{
			CreateDirectory( Dir.c_str(), NULL );
		}
	}
}

// Устанавливает все текстуры, пути к которым упомянуты в файле эффектов.
void ResMaterial::SetupTextures( const char *EffectFilePath )
{
	std::fstream FxFile( EffectFilePath, std::ios::in | std::ios::binary );
	if( FxFile.bad() )
		Error( "Unable to open file : " << EffectFilePath );
	std::string Buffer( (std::istreambuf_iterator<char>(FxFile)), std::istreambuf_iterator<char>() );

	// Функтор для добавления лексем в список.
	std::vector<std::string> TextureVarNames;
	std::vector<std::string> TextureVarTypes;
	boost::function< void(const char*,const char*) > Sema1 =
		boost::bind( &AddString2Vector, &TextureVarNames, _1, _2 );
	boost::function< void(const char*,const char*) > Sema0 = 
		boost::bind( &AddString2Vector, &TextureVarTypes, _1, _2 );

	// Определяем правила для выделения нужных лексем.
	// FIXME:
	rule<> IdSymb = range_p('a','z') | range_p('A','Z') | ch_p('_') | ch_p('$');
	rule<> Delim = chset_p(" \b\t\n\f\r");
	rule<> Token = +(anychar_p & ~chset_p(" \b\t\n\f\r"));
	rule<> Word = (IdSymb && Word) | (alnum_p && Word) | IdSymb | alnum_p;	
	rule<> Keyword = (IdSymb && Word)[Sema1];
	rule<> TxStr = (str_p("texture2D") | str_p("texture1D") | str_p("texture3D"))[Sema0] && +Delim && Keyword;
	rule<> ParseRule = *( *Delim && (TxStr | Token) && *Delim );

	if( !parse( Buffer.c_str(), ParseRule ).full )
	{	// Ошибка разбора файла. Если эффект был прянят компилятором эффектов,
		// то такая ошибка не должна происходить.
		assert( 0 );
		return;
	}

	// Загружаем требуемые текстуры.
	for( unsigned i = 0; i < TextureVarNames.size(); i++ )
	{
		D3DXHANDLE TexParam = pFX->GetParameterByName( NULL, TextureVarNames[i].c_str() );
		if( !TexParam )
		{
			// Это может быть упоминание о текстурной переменной в комментарии
			// или строке. На данный момент такие случаи не обрабатываются парсером.
			continue;
		}
		ResBaseTexture *NewTexture = 0;
		D3DXHANDLE TexFilePath = pFX->GetAnnotationByName( TexParam, "Name" );
		if( TexFilePath )
		{
			const char *TexFilePathStr = 0;
			pFX->GetString( TexFilePath, &TexFilePathStr );
			const char *TexShaderPath = 0;
			if( TexFilePath )
			{
				// Может быть процедруная текстура.
				bool	IsProcedural = false;
				int		TexWidth, TexHeight, TexDepth, MipLevels;
				D3DXHANDLE TexShader = pFX->GetAnnotationByName( TexParam, "TextureShader" );
				if( TexShader )
				{ // Создаем процедурную текстуру.
					HRESULT HR = pFX->GetString( TexShader, &TexShaderPath );
					assert( !FAILED(HR) );

					IsProcedural = true;
					D3DXHANDLE hTexWidth, hTexHeight, hMipLevels, hTexDepth;
					hTexWidth = pFX->GetAnnotationByName( TexParam, "Width" );
					hTexHeight = pFX->GetAnnotationByName( TexParam, "Height" );
					hTexDepth = pFX->GetAnnotationByName( TexParam, "Depth" );
					hMipLevels = pFX->GetAnnotationByName( TexParam, "MipLevels" );
					
					if( hTexWidth )
					{
						pFX->GetInt( hTexWidth, &TexWidth );
					} else {
						TexWidth = 256;
					}

					if( hTexHeight )
					{
						pFX->GetInt( hTexHeight, &TexHeight );
					} else {
						TexHeight = 256;
					}

					if( hTexDepth )
					{
						pFX->GetInt( hTexDepth, &TexDepth );
					} else {
						TexDepth = 256;
					}

					if( hMipLevels )
					{
						pFX->GetInt( hMipLevels, &MipLevels );
					} else {
						MipLevels = 0;
					}
				}

				// Определяем тип текстуры.
				if( TextureVarTypes[i] == "texture2D" || TextureVarTypes[i] == "texture1D" )
				{
					if( IsProcedural )
					{
						// Создаем через текстурный генератор (шейдер).
						TSVolumeGenerator TexGen( TexShaderPath );
						NewTexture = ResourceManager::GetInstance().Register(
							new ResProcTexture( TexWidth, TexHeight, MipLevels, TexGen ), TexFilePathStr );
					}
					else
					{
						// Грузим текстуру из файла.
						NewTexture = ResourceManager::GetInstance().Register(
							new ResTexture( TexFilePathStr ), TexFilePathStr );
					}
				}
				else if( TextureVarTypes[i] == "texture3D" )
				{
					if( IsProcedural )
					{
						ResBaseTexture *Tex = 0;
						// Проверяем наличие в кэше.
						std::string CachedTexturePath = "TextureCache/";
						CachedTexturePath += TexFilePathStr;
						CachedTexturePath += ".dds";
						if( UseTextureCache && LookForCachedResource( CachedTexturePath ) )
						{
							Tex = new ResVolume( CachedTexturePath );
						}
						else
						{
							const char *SavePath = "\0";
							if( UseTextureCache )
							{	// Сохраняем в кэш.
								CreateCacheResourceDir( CachedTexturePath );
								SavePath = CachedTexturePath.c_str();
							}
							TSVolumeGenerator VolGen( TexShaderPath );
							Tex = new ResProcVolumeTexture( TexWidth, TexHeight, TexDepth, MipLevels, VolGen, SavePath );
						}
						
						NewTexture = ResourceManager::GetInstance().Register( Tex, CachedTexturePath );
					}
					else
					{
						// Грузим из файла.
						NewTexture = ResourceManager::GetInstance().Register(
							new ResVolume( TexFilePathStr ), TexFilePathStr );
					}
				}
				else
				{
					Error( "Texture type " << TextureVarTypes[i] << " is not supported" );
				}
			}
		}
		TextureList.push_back( std::make_pair(TexParam, NewTexture) );
	}
	SetTextures();
}

void ResMaterial::SetTextures()
{
	for( unsigned i=0; i < TextureList.size(); i++ )
	{
		if( TextureList[i].second )
		{
			assert( TextureList[i].second->GetHandle() );
			pFX->SetTexture(
				TextureList[i].first,
				TextureList[i].second->GetHandle()
			);
		}
	}
}

void ResMaterial::AttachTexture( ResBaseTexture *Texture, unsigned int SamplerNum )
{
	// Устанавливаем на текстурную переменную по счету SamplerNum в исходном файле шейдера.
	if( Texture )
	{
		if( TextureList.size() > SamplerNum )
		{
			if( TextureList[0].second )
				TextureList[0].second->Release();
			TextureList[0].second = Texture;
			pFX->SetTexture( TextureList[SamplerNum].first, Texture->GetHandle() );
			Texture->AddRef();
		}
		else
		{ // Переменная с таким номером не существует.
			assert( 0 );
		}
	}
}

void ResMaterial::GetParameter( const char *VarName, IShaderParam* ShaderParam ) const
{
	D3DXHANDLE hParam = pFX->GetParameterByName( NULL, VarName );
	if( !hParam )
		Error( "Paramter " << VarName << " is not found in " << Name );
	if( hParam )
	{
		D3DXPARAMETER_DESC ParamDesc;
		pFX->GetParameterDesc( hParam, &ParamDesc );
		ShaderParam->hParam = hParam;
		if( ShaderParam->GetSize() != ParamDesc.Bytes )
			Error( "Parameter size mismatch : " << VarName << " in " << Name );
	}
}

void ResMaterial::SetParameter( IShaderParam& ShaderParam )
{
	HRESULT HR = pFX->SetValue( ShaderParam.hParam, ShaderParam.GetData(), ShaderParam.GetSize() );
	assert( !FAILED(HR) );
}

//------------------------------------------------------------------------------------------------------------------

void IShaderParam::AttachTo( ResMaterial *Mat, const char *VarName )
{
	Mat->GetParameter( VarName, this );
}

//------------------------------------------------------------------------------------------------------------------

ResProcTexture::ResProcTexture( int Width, int Height, int MipLevels, TextureGenerator &TexGen )
{
	memset( &ImgInfo, 0, sizeof(ImgInfo) );
	ImgInfo.Width = Width;
	ImgInfo.Height = Height;
	ImgInfo.MipLevels = MipLevels;
	// Сохраняем контекст генератора текстур.
	LocalTexGen = TexGen.Replicate();
}

ResProcTexture::~ResProcTexture()
{
	delete LocalTexGen;
}

void ResProcTexture::Create( LPDIRECT3DDEVICE9 pDevice )
{
	HRESULT HR;
	LPDIRECT3DTEXTURE9 pTex = 0;
	HR = pDevice->CreateTexture( ImgInfo.Width,
								 ImgInfo.Height,
								 ImgInfo.MipLevels,
								 0,
								 D3DFMT_A8R8G8B8,
								 D3DPOOL_DEFAULT,
								 &pTex,
								 NULL );
	if( FAILED(HR) )
	{
		DXError(HR, "failed on IDirect3DDevice9::CreateTexture" );
	}
	pTexture = pTex;
	LocalTexGen->FillTexture( pTex );
}

void ResProcTexture::Destroy()
{
	if( pTexture )
	{
		pTexture->Release();
		pTexture = 0;
	}
}

ResProcVolumeTexture::ResProcVolumeTexture( int Width, int Height, int Depth, int MipLevels,
											TextureGenerator& TexGen, const char *CacheFilePath )
		: CacheFile(CacheFilePath)
{
	memset( &ImgInfo, 0, sizeof(ImgInfo) );
	ImgInfo.Width = Width;
	ImgInfo.Height = Height;
	ImgInfo.Depth = Depth;
	ImgInfo.MipLevels = MipLevels;
	LocalTexGen = TexGen.Replicate();
}

ResProcVolumeTexture::~ResProcVolumeTexture()
{
	delete LocalTexGen;
}

void ResProcVolumeTexture::Create( LPDIRECT3DDEVICE9 pDevice )
{
	HRESULT HR;
	LPDIRECT3DVOLUMETEXTURE9 pTex = 0;
	HR = pDevice->CreateVolumeTexture(
		ImgInfo.Width,
		ImgInfo.Height,
		ImgInfo.Depth,
		ImgInfo.MipLevels,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_SYSTEMMEM,
		&pTex,
		NULL );
	if( FAILED(HR) )
	{
		DXError(HR, "failed on IDirect3DDevice9::CreateVolumeTexture");
	}

	LocalTexGen->FillVolumeTexture( pTex );

	LPDIRECT3DVOLUMETEXTURE9 pTex1 = 0;
	HR = pDevice->CreateVolumeTexture(
		ImgInfo.Width,
		ImgInfo.Height,
		ImgInfo.Depth,
		ImgInfo.MipLevels,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&pTex1,
		NULL );
	if( FAILED(HR) )
	{
		DXError(HR, "failed on IDirect3DDevice9::CreateVolumeTexture");
	}
	if( FAILED(HR = pDevice->UpdateTexture( pTex, pTex1 )) )
	{
		DXError(HR, "failed on IDirect3DDevice9::UpdateTexture");
	}
	// Сохраняем копию в кэш.
	if( !CacheFile.empty() )
	{
		if( FAILED(HR=D3DXSaveTextureToFile( CacheFile.c_str(), D3DXIFF_DDS, pTex, NULL ) ) )
			DXError(HR, " failed on D3DXSaveVolumeToFile : " << CacheFile );
	}
	pTex->Release();
	pTexture = pTex1;
}

void ResProcVolumeTexture::Destroy()
{
	if( pTexture )
	{
		pTexture->Release();
		pTexture = 0;
	}
}

