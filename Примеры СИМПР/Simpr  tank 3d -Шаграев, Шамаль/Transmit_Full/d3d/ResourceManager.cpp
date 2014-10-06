#include "Rendering.h"
#include "Material.h"

ResourceManager::ResourceManager() : pDevice(0), pD3D(0), pOldRT(0)
{}

void ResourceManager::Init( LPDIRECT3DDEVICE9 pDevice9, LPDIRECT3D9 pD3D9, const D3DPRESENT_PARAMETERS& PParams )
{
	pDevice = pDevice9;
	pD3D = pD3D9;
	PresentParams = PParams;
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager ResMgr;
	return ResMgr;
}

ResourceManager::~ResourceManager()
{
	// Если ResMap непусто - то какой-то ресурс забыли освободить.
	// TODO: при ошибке освобождать принудительно.
	SetRenderTarget( 0 );
	assert( ResMap.empty() );
	if( pDevice )
	{
		pDevice->Release();
		pDevice = 0;
	}
	if( pD3D )
	{
		pD3D->Release();
		pD3D = 0;
	}
}

void ResourceManager::Unregister( IResource *Resource )
{
	if( Resource->IsRegistered && Resource->RefCount == 0 )
	{
		Resource->Destroy();
		ResMap.erase( Resource->Where );
	}
}

ResRenderTarget* ResourceManager::CreateRenderTarget( D3DFORMAT Format )
{
	ResRenderTarget *RT = new ResRenderTarget(
		PresentParams.BackBufferWidth,
		PresentParams.BackBufferHeight,
		Format );

	std::stringstream StrStr;
	StrStr << "RenderTarget" << RT;
	RT = Register( RT, StrStr.str() );
	return RT;
}
// RT == NULL - восстановить прежнюю.
void ResourceManager::SetRenderTarget( ResRenderTarget *RT )
{
	HRESULT HR;
	if( !RT && pOldRT )
	{
		if( FAILED(HR = pDevice->SetRenderTarget( 0, pOldRT )) )
			DXError(HR, "Restore RT: IDirect3DDevice9::SetRenderTarget failed" );
		pOldRT->Release();
		pOldRT = 0;
	}
	if( RT && !pOldRT )
	{
		if( FAILED(HR = pDevice->GetRenderTarget( 0, &pOldRT )) )
			DXError(HR, "IDirect3DDevice9::GetRenderTarget failed" );
		LPDIRECT3DSURFACE9 pRTSurf = RT->GetSurface();
		if( FAILED(HR = pDevice->SetRenderTarget( 0, pRTSurf )) )
			DXError(HR, "IDirect3DDevice9::SetRenderTarget failed" );
		pRTSurf->Release();
	}
}
void ResourceManager::DrawFullScreenQuadF( int Dummy )
{
    // Ensure that we're directly mapping texels to pixels by offset by 0.5
    // For more info see the doc page titled "Directly Mapping Texels to Pixels"
    float fWidth5 = (FLOAT)PresentParams.BackBufferWidth - 0.5f;
    float fHeight5 = (FLOAT)PresentParams.BackBufferHeight - 0.5f;

    // Draw the quad
    ScreenVertex svQuad[4];

    svQuad[0].Pos = D3DXVECTOR4(-0.5f, -0.5f, 0.5f, 1.0f);
    svQuad[0].TexCoord = D3DXVECTOR2(0, 0);

    svQuad[1].Pos = D3DXVECTOR4(fWidth5, -0.5f, 0.5f, 1.0f);
    svQuad[1].TexCoord = D3DXVECTOR2(1, 0);

    svQuad[2].Pos = D3DXVECTOR4(-0.5f, fHeight5, 0.5f, 1.0f);
    svQuad[2].TexCoord = D3DXVECTOR2(0, 1);

    svQuad[3].Pos = D3DXVECTOR4(fWidth5, fHeight5, 0.5f, 1.0f);
    svQuad[3].TexCoord = D3DXVECTOR2(1, 1);

    pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
    pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 );
    pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, svQuad, sizeof(ScreenVertex) );
    pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
}

void ResourceManager::DrawFullScreenQuad( ResMaterial *Mat )
{
	DrawCallDelegate<int>	DrawQuad( boost::bind(rand), boost::bind( &ResourceManager::DrawFullScreenQuadF, this, _1 ) );

	Mat->Draw( DrawQuad, 123 );
}

LPDIRECT3DDEVICE9 ResourceManager::GetDevice()
{
	return pDevice;
}

void ResourceManager::OnDeviceLost( D3DPRESENT_PARAMETERS *PParams )
{
	if( pDevice )
	{
		ReleaseAll();
		Sleep( 1500 );
		HRESULT HR = pDevice->Reset( PParams );
		if( HR == D3DERR_DEVICELOST )
		{
			HR = pDevice->TestCooperativeLevel();
			if( FAILED(HR) )
				DXError(HR, "device is lost and cannot be restored" );

			pDevice->Reset( PParams );
			PresentParams = *PParams;
		}
		else if (FAILED(HR))
		{
			DXError(HR, "failed on IDirect3DDevice9::Reset" );
		}
		std::vector<IResource*> ResQueue;
		for( stdext::hash_map<std::string,IResource*>::iterator It = ResMap.begin();
			It != ResMap.end(); ++It )
		{
			ResQueue.push_back( It->second );
		}

		// Сортируем по приоритетам.
		std::sort( ResQueue.begin(), ResQueue.end(), boost::bind(&IResource::operator <, _1, _2) );

		std::for_each( ResQueue.begin(), ResQueue.end(), boost::bind(&IResource::Create,_1,pDevice) );

	}
}

// Освобождение всех ресурсов. Пересоздание возможно.
void ResourceManager::ReleaseAll()
{
	SetRenderTarget( 0 );
	for( stdext::hash_map<std::string,IResource*>::iterator It = ResMap.begin();
		It != ResMap.end(); ++It )
	{
		It->second->Destroy();
	}
}