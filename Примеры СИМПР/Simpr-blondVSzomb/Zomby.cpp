#include "Zomby.h"
#include "Scene3D.h"

CZomby::CZomby(CScene3D* _Scene3D) : CMeshObject3D(_Scene3D)
{
	Hod_z=false;
}

CZomby::~CZomby()
{
}
bool CZomby::Render()
{
	
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 temp;

	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixIdentity( &temp );	
	D3DXMatrixScaling( &temp, 0.3f, 0.3f, 0.3f);
	D3DXMatrixMultiply( &matWorld, &matWorld, &temp);

	D3DXMatrixTranslation( &temp, Position.x, Position.y, Position.z );
	D3DXMatrixMultiply( &matWorld, &matWorld, &temp );

	Scene3D->Hardware3D->D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for( DWORD i=0; i<NumMaterialsLOD3; i++ )
        {
            
			Scene3D->Hardware3D->D3DDevice->SetMaterial( &MeshMaterialsLOD3[i] );
            Scene3D->Hardware3D->D3DDevice->SetTexture( 0, MeshTexturesLOD3[i] );
        
            
            MeshLOD3->DrawSubset( i );
        }

	return true;
}

bool CZomby::Update(float  fElpasedTime)
{	
	return true;
}
/*
void CZomby::MoveForward()
{
	Position.x += 5.0f;

	return;
}
void CZomby::MoveBack()
{
	Position.x -= 5.0f;

	return;
}
void CZomby::MoveRight()
{
	Position.z += 5.0f;

	return;
}
void CZomby::MoveLeft()
{
	Position.z -= 5.0f;

	return;
}
*/