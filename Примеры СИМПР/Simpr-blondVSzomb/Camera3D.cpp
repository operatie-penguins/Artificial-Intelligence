//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CCamera3D, source file
// Класс осуществляет работу с камерой
//////////////////////////////////////////////////////////////////



#include "Camera3D.h"
#include "Hardware3D.h"



//Конструктор
CCamera3D::CCamera3D(CHardware3D* _Hardware3D)
{
	Position = D3DXVECTOR3(100, 120, -200.0f);
	LookAtPoint = D3DXVECTOR3(50, 0, 50);
	Hardware3D = _Hardware3D;
	g_bMousing = false;
	g_fMoveSpeed = 25.0f;
	g_vUp=D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_vRight=D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}



//Деструктор
CCamera3D::~CCamera3D()
{

}



//Обновление
bool CCamera3D::Update(float g_fElpasedTime)
{

	D3DXVECTOR3 temp;
	D3DXVECTOR2 temp2D;
	D3DXMATRIX  rotMat;

	if( KEYDOWN(VK_UP) )
	{
		D3DXVec3Normalize(&temp,&(LookAtPoint - Position));
		Position += 5.5f*temp;
	}
	if( KEYDOWN(VK_DOWN) )
	{
		D3DXVec3Normalize(&temp,&(LookAtPoint - Position));
		Position -= 5.5f*temp;
	}
	if( KEYDOWN(VK_LEFT) )
	{
		temp = LookAtPoint - Position;
		D3DXMatrixRotationY( &rotMat, D3DX_PI/2.0f);
		D3DXVec3TransformCoord(&temp, &temp, &rotMat);
		temp2D.x = temp.x;
		temp2D.y = temp.z;
		D3DXVec2Normalize(&temp2D, &temp2D);
		temp2D *= 5.4f;
		Position.x -= temp2D.x;
		Position.z -= temp2D.y;
		LookAtPoint.x -= temp2D.x;
		LookAtPoint.z -= temp2D.y;
	}
	if( KEYDOWN(VK_RIGHT) )
	{
		temp = LookAtPoint - Position;
		D3DXMatrixRotationY( &rotMat, D3DX_PI/2.0f);
		D3DXVec3TransformCoord(&temp, &temp, &rotMat);
		temp2D.x = temp.x;
		temp2D.y = temp.z;
		D3DXVec2Normalize(&temp2D, &temp2D);
		temp2D *= 5.4f;
		Position.x += temp2D.x;
		Position.z += temp2D.y;
		LookAtPoint.x += temp2D.x;
		LookAtPoint.z += temp2D.y;
	}
	if( KEYDOWN(0x41) )    //A
	{
		temp = LookAtPoint - Position;
		D3DXMatrixRotationY( &rotMat, -D3DX_PI/360.0f );
		D3DXVec3TransformCoord( &temp, &temp, &rotMat );
		LookAtPoint = Position + temp;		
	}
	if( KEYDOWN(0x44) )    //D
	{
		temp = LookAtPoint - Position;
		D3DXMatrixRotationY( &rotMat, D3DX_PI/360.0f );
		D3DXVec3TransformCoord( &temp, &temp, &rotMat );
		LookAtPoint = Position + temp;	
	}
	if( KEYDOWN(0x57) )    //W
	{
		temp = LookAtPoint - Position;
		D3DXMatrixRotationY( &rotMat, D3DX_PI/2.0f );
		D3DXVec3TransformCoord( &temp, &temp, &rotMat );
		temp.y = 0.0f;
		D3DXMatrixRotationAxis( &rotMat, &temp, -D3DX_PI/360.0f );
		temp = LookAtPoint - Position;		
		D3DXVec3TransformCoord( &temp, &temp, &rotMat );
		LookAtPoint = Position + temp;	
	}
	if( KEYDOWN(0x53) )    //S
	{
		temp = LookAtPoint - Position;		
		D3DXMatrixRotationY( &rotMat, D3DX_PI/2.0f );
		D3DXVec3TransformCoord( &temp, &temp, &rotMat );
		temp.y = 0.0f;
		D3DXMatrixRotationAxis( &rotMat, &temp, D3DX_PI/360.0f );
		temp = LookAtPoint - Position;				
		D3DXVec3TransformCoord( &temp, &temp, &rotMat );
		LookAtPoint = Position + temp;	
	}
	if( KEYDOWN(VK_END) )
	{		
		Position.y -= 1.5f;
		LookAtPoint.y -= 1.5f;
	}
	if( KEYDOWN(VK_HOME) )
	{
		Position.y += 1.5f;
		LookAtPoint.y += 1.5f;
	}

	return true;
}
