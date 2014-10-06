//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Main header file
//////////////////////////////////////////////////////////////////



#ifndef MAIN_H
#define MAIN_H


#include "Resource.h"
#include "Hardware3D.h"
#include "Scene3D.h"
#include "Camera3D.h"
#include "Player.h"
#include "Blondes.h"
#include "Human.h"
#include "Zomby.h"
#include "Pole.h"



#pragma comment(lib, "Winmm")



#define TITLE_STRING	"BlondsvsZombys"

//Размеры окна
#define Width  800
#define Height 600



HWND    hWnd;
HINSTANCE	hInstance;
HACCEL Accelerators;

CHardware3D* Hardware3D;
CScene3D* Scene3D;
CCamera3D* Camera3D;
CPlayer* Players[5];
CZomby* Zombies[9];
CBlondes* Blondees[9];
CHuman* Humans[9];
CPole* Pole[1];

float  g_fElpasedTime;
double g_dCurTime;
double g_dLastTime;



LPDIRECT3DVERTEXBUFFER9 g_pVB1        = NULL; // Buffer to hold vertices
LPDIRECT3DVERTEXBUFFER9 g_pVB2        = NULL; // Buffer to hold vertices

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z; // The transformed position for the vertex
    DWORD color;        // The vertex color
};



#endif
