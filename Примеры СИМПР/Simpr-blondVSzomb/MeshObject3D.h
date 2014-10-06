//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CMeshObject3D, header file
//////////////////////////////////////////////////////////////////



#ifndef MESHOBJECT3D_H
#define MESHOBJECT3D_H



#include "Object3D.h"
#include "Scene3D.h"



class CMeshObject3D : public CObject3D
{
protected:
	//LOD 1
	LPD3DXMESH              MeshLOD1         ; //Меш
	D3DMATERIAL9*           MeshMaterialsLOD1; //Материалы для меша
	LPDIRECT3DTEXTURE9*     MeshTexturesLOD1 ; //Тексуты меша
	DWORD                   NumMaterialsLOD1 ; //Число материалов
	//LOD 2
	LPD3DXMESH              MeshLOD2         ; //Меш
	D3DMATERIAL9*           MeshMaterialsLOD2; //Материалы для меша
	LPDIRECT3DTEXTURE9*     MeshTexturesLOD2 ; //Тексуты меша
	DWORD                   NumMaterialsLOD2 ; //Число материалов
	//LOD 3
	LPD3DXMESH              MeshLOD3         ; //Меш
	D3DMATERIAL9*           MeshMaterialsLOD3; //Материалы для меша
	LPDIRECT3DTEXTURE9*     MeshTexturesLOD3 ; //Тексуты меша
	DWORD                   NumMaterialsLOD3 ; //Число материалов

	char*                   MeshFileNameLOD1 ; //Имя файла с мешем
	char*                   MeshFileNameLOD2 ;
	char*                   MeshFileNameLOD3 ;

public:

	CMeshObject3D(CScene3D* _Scene3D);
	~CMeshObject3D();
	
	bool LoadMesh(char* _MeshFileNameLOD1,char* _MeshFileNameLOD2,char* _MeshFileNameLOD3);
	virtual bool Render()=0;
	virtual bool Update(float fElpasedTime)=0;

};



#endif
