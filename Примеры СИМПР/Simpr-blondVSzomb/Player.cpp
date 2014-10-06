//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Shibarshin A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CPlayer, realization
//////////////////////////////////////////////////////////////////



#include "Player.h"
#include "Scene3D.h"



CPlayer::CPlayer(CScene3D* _Scene3D) : CMeshObject3D(_Scene3D)
{
	Team = 0;
	HaveBall = false;
}



CPlayer::~CPlayer()
{

}



bool CPlayer::Render()
{
	
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 temp;

	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixIdentity( &temp );	
	D3DXMatrixScaling( &temp, 0.3f, 0.3f, 0.3f);
	D3DXMatrixMultiply( &matWorld, &matWorld, &temp);

	if(Team == 0)
	{
		D3DXMatrixRotationY( &temp, -D3DX_PI/2.0f);
		D3DXMatrixMultiply( &matWorld, &matWorld, &temp);
	}

	if(Team == 1)
	{
		D3DXMatrixRotationY( &temp, D3DX_PI/2.0f);
		D3DXMatrixMultiply( &matWorld, &matWorld, &temp);
	}

	D3DXMatrixTranslation( &temp, Position.x, Position.y, Position.z );
	D3DXMatrixMultiply( &matWorld, &matWorld, &temp );
	

	Scene3D->Hardware3D->D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);	
	
	if( Team==0 && HaveBall )
		for( DWORD i=0; i<NumMaterialsLOD1; i++ )
        {
            
			Scene3D->Hardware3D->D3DDevice->SetMaterial( &MeshMaterialsLOD1[i] );
            Scene3D->Hardware3D->D3DDevice->SetTexture( 0, MeshTexturesLOD1[i] );
        
            
            MeshLOD1->DrawSubset( i );
        }
	if( Team==0 && (!HaveBall) )
		for( DWORD i=0; i<NumMaterialsLOD2; i++ )
        {
            		
            Scene3D->Hardware3D->D3DDevice->SetMaterial( &MeshMaterialsLOD2[i] );
            Scene3D->Hardware3D->D3DDevice->SetTexture( 0, MeshTexturesLOD2[i] );
        
            
            MeshLOD2->DrawSubset( i );
        }
	if( Team==1 )
		for( DWORD i=0; i<NumMaterialsLOD3; i++ )
        {
            		
            Scene3D->Hardware3D->D3DDevice->SetMaterial( &MeshMaterialsLOD3[i] );
            Scene3D->Hardware3D->D3DDevice->SetTexture( 0, MeshTexturesLOD3[i] );
        
            
            MeshLOD3->DrawSubset( i );
        }


	return true;


}



bool CPlayer::Update(float  fElpasedTime)
{	
	return true;
}



void CPlayer::MoveForward()
{
	Position.x += 1.0f;

	return;
}



void CPlayer::MakePass(CPlayer* _CPlayer)
{
	HaveBall = false;
	_CPlayer->HaveBall = true;

	return;
}