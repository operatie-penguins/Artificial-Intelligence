#include "Blondes.h"
#include "Scene3D.h"

CBlondes::CBlondes(CScene3D* _Scene3D) : CMeshObject3D(_Scene3D)
{
	Hod_b=false;
}

CBlondes::~CBlondes()
{
}
bool CBlondes::Render()
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

		for( DWORD i=0; i<NumMaterialsLOD2; i++ )
        {
            		
            Scene3D->Hardware3D->D3DDevice->SetMaterial( &MeshMaterialsLOD2[i] );
            Scene3D->Hardware3D->D3DDevice->SetTexture( 0, MeshTexturesLOD2[i] );
        
            
            MeshLOD2->DrawSubset( i );
        }

	return true;
}

bool CBlondes::Update(float  fElpasedTime)
{	
	return true;
}
/*
void CBlondes::MoveForward()
{
	Position.x += 5.0f;

	return;
}
void CBlondes::MoveBack()
{
	Position.x -= 5.0f;

	return;
}
void CBlondes::MoveRight()
{
	Position.z += 5.0f;

	return;
}
void CBlondes::MoveLeft()
{
	Position.z -= 5.0f;

	return;
}
*/