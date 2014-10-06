//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CCamera3D, header file
//////////////////////////////////////////////////////////////////



#ifndef CAMERA3D_H
#define CAMERA3D_H



#include "Headers.h"



class CHardware3D;



class CCamera3D
{
public:
	CCamera3D(CHardware3D* _Hardware3D);
	~CCamera3D();

	bool Update(float g_fElpasedTime);

	D3DXVECTOR3 Position;
	D3DXVECTOR3 LookAtPoint;

	CHardware3D* Hardware3D;

	POINT  g_ptLastMousePosit;
	POINT  g_ptCurrentMousePosit;
	bool   g_bMousing;
	float  g_fMoveSpeed;
	D3DXVECTOR3	g_vUp;    // Up Vector
	D3DXVECTOR3	g_vRight; // Right Vector

};



#endif
