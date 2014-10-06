#include "Human.h"
#include "Scene3D.h"

CHuman::CHuman(CScene3D* _Scene3D) : CMeshObject3D(_Scene3D)
{
	Hod_h= false;
}

CHuman::~CHuman()
{
}
bool CHuman::Render()
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

		for( DWORD i=0; i<NumMaterialsLOD1; i++ )
        {
            		
            Scene3D->Hardware3D->D3DDevice->SetMaterial( &MeshMaterialsLOD1[i] );
            Scene3D->Hardware3D->D3DDevice->SetTexture( 0, MeshTexturesLOD1[i] );
        
            
            MeshLOD1->DrawSubset( i );
        }

	return true;

}

bool CHuman::Update(float  fElpasedTime)
{	
	return true;
}
/*
void CHuman::MoveForward()
{
	Position.x += 5.0f;

	return;
}
void CHuman::MoveBack()
{
	Position.x -= 5.0f;

	return;
}
void CHuman::MoveRight()
{
	Position.z += 5.0f;

	return;
}
void CHuman::MoveLeft()
{
	Position.z -= 5.0f;

	return;
}
*/