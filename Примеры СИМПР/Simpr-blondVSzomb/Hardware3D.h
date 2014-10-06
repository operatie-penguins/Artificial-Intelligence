//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CHardware3D, header file
//////////////////////////////////////////////////////////////////



#ifndef HARDWARE3D_H
#define HARDWARE3D_H



#include "Headers.h"



class CHardware3D
{
public:
	HWND hWnd;                   //Handle ����
	LPDIRECT3D9 D3D;             //��������� Direct3D
	LPDIRECT3DDEVICE9 D3DDevice; //���������� Direct3D

	CHardware3D(HWND _hWnd);
	~CHardware3D();
};



#endif
