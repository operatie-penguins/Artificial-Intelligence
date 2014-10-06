//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CMeshObject3D, source file
//////////////////////////////////////////////////////////////////



#include "MeshObject3D.h"



//Конструктор
CMeshObject3D::CMeshObject3D(CScene3D* _Scene3D)
:CObject3D(_Scene3D)
{

}



//Деструктор
CMeshObject3D::~CMeshObject3D()
{

}



//Загрузка меша из файла
bool CMeshObject3D::LoadMesh(char* _MeshFileNameLOD1,char* _MeshFileNameLOD2,char* _MeshFileNameLOD3)
{
	MeshFileNameLOD1 = _MeshFileNameLOD1;
	MeshFileNameLOD2 = _MeshFileNameLOD2;
	MeshFileNameLOD3 = _MeshFileNameLOD3;

	LPD3DXBUFFER pD3DXMtrlBuffer;

    // Загружаем меш из заданного файла
    if( FAILED( D3DXLoadMeshFromX( MeshFileNameLOD1, D3DXMESH_SYSTEMMEM, 
                                   Scene3D->Hardware3D->D3DDevice, NULL, 
                                   &pD3DXMtrlBuffer, NULL, &NumMaterialsLOD1, 
                                   &MeshLOD1 ) ) )
    
    {
        MessageBox(NULL, "Невозможно загрузить меш", "Ошибка!", MB_OK);
        return false;
    }
   

    // Достаем свойства материалов и имена текстур из
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    MeshMaterialsLOD1 = new D3DMATERIAL9[NumMaterialsLOD1];
    if( MeshMaterialsLOD1 == NULL )
        return false;
    MeshTexturesLOD1  = new LPDIRECT3DTEXTURE9[NumMaterialsLOD1];
    if( MeshTexturesLOD1 == NULL )
        return false;

    for( DWORD i=0; i<NumMaterialsLOD1; i++ )
    {
        // Копируем материал
        MeshMaterialsLOD1[i] = d3dxMaterials[i].MatD3D;

        // Ставим амбиенточку для материала
        MeshMaterialsLOD1[i].Ambient = MeshMaterialsLOD1[i].Diffuse;

        MeshTexturesLOD1[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
        {
            // Создаем текстуру
            if( FAILED( D3DXCreateTextureFromFile( Scene3D->Hardware3D->D3DDevice, 
                                                d3dxMaterials[i].pTextureFilename, 
                                                &MeshTexturesLOD1[i] ) ) )
            
            {
                MessageBox(NULL, "Невозможно найти тестуру", "Ошибка", MB_OK);
				return false;
            }
            
        }
    }

    // Освобождаем буффер материалов
    pD3DXMtrlBuffer->Release();  



	// Загружаем меш из заданного файла
    if( FAILED( D3DXLoadMeshFromX( MeshFileNameLOD2, D3DXMESH_SYSTEMMEM, 
                                   Scene3D->Hardware3D->D3DDevice, NULL, 
                                   &pD3DXMtrlBuffer, NULL, &NumMaterialsLOD2, 
                                   &MeshLOD2 ) ) )
    
    {
        MessageBox(NULL, "Невозможно загрузить меш", "Ошибка!", MB_OK);
        return false;
    }
   

    // Достаем свойства материалов и имена текстур из
    // pD3DXMtrlBuffer
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    MeshMaterialsLOD2 = new D3DMATERIAL9[NumMaterialsLOD2];
    if( MeshMaterialsLOD2 == NULL )
        return false;
    MeshTexturesLOD2  = new LPDIRECT3DTEXTURE9[NumMaterialsLOD2];
    if( MeshTexturesLOD2 == NULL )
        return false;

    for(int i=0; i<NumMaterialsLOD2; i++ )
    {
        // Копируем материал
        MeshMaterialsLOD2[i] = d3dxMaterials[i].MatD3D;

        // Ставим амбиенточку для материала
        MeshMaterialsLOD2[i].Ambient = MeshMaterialsLOD2[i].Diffuse;

        MeshTexturesLOD2[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
        {
            // Создаем текстуру
            if( FAILED( D3DXCreateTextureFromFile( Scene3D->Hardware3D->D3DDevice, 
                                                d3dxMaterials[i].pTextureFilename, 
                                                &MeshTexturesLOD2[i] ) ) )
            
            {
                MessageBox(NULL, "Невозможно найти тестуру", "Ошибка", MB_OK);
				return false;
            }
            
        }
    }

    // Освобождаем буффер материалов
    pD3DXMtrlBuffer->Release();  



	// Загружаем меш из заданного файла
    if( FAILED( D3DXLoadMeshFromX( MeshFileNameLOD3, D3DXMESH_SYSTEMMEM, 
                                   Scene3D->Hardware3D->D3DDevice, NULL, 
                                   &pD3DXMtrlBuffer, NULL, &NumMaterialsLOD3, 
                                   &MeshLOD3 ) ) )
    
    {
        MessageBox(NULL, "Невозможно загрузить меш", "Ошибка!", MB_OK);
        return false;
    }
   

    // Достаем свойства материалов и имена текстур из
    // pD3DXMtrlBuffer
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    MeshMaterialsLOD3 = new D3DMATERIAL9[NumMaterialsLOD3];
    if( MeshMaterialsLOD3 == NULL )
        return false;
    MeshTexturesLOD3  = new LPDIRECT3DTEXTURE9[NumMaterialsLOD3];
    if( MeshTexturesLOD3 == NULL )
        return false;

    for(int i=0; i<NumMaterialsLOD3; i++ )
    {
        // Копируем материал
        MeshMaterialsLOD3[i] = d3dxMaterials[i].MatD3D;

        // Ставим амбиенточку для материала
        MeshMaterialsLOD3[i].Ambient = MeshMaterialsLOD3[i].Diffuse;

        MeshTexturesLOD3[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
        {
            // Создаем текстуру
            if( FAILED( D3DXCreateTextureFromFile( Scene3D->Hardware3D->D3DDevice, 
                                                d3dxMaterials[i].pTextureFilename, 
                                                &MeshTexturesLOD3[i] ) ) )
            
            {
                MessageBox(NULL, "Невозможно найти тестуру", "Ошибка", MB_OK);
				return false;
            }
            
        }
    }

    // Освобождаем буффер материалов
    pD3DXMtrlBuffer->Release();  



	return true;
}
