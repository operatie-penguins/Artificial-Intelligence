//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CScene3D, source file
// Класс сцены. Осуществляет обработку объектов и их взаимодействие
//////////////////////////////////////////////////////////////////



#include "Scene3D.h"
#include "Object3D.h"
#include "Camera3D.h"



typedef struct 
{ 
	float normal[3]; // нормаль к плоскости (A, B, C) 
	float dist; // коэфициент D 
} plane_t;



plane_t frustum[6];



//Конструктор
CScene3D::CScene3D(CHardware3D* _Hardware3D, CCamera3D* _Camera3D)
{
	CurrState = 0;
	Hardware3D = _Hardware3D;
	Camera3D = _Camera3D;	
}



//Деструктор
CScene3D::~CScene3D()
{

}



//Рендеринг
bool CScene3D::Render()
{	
	Hardware3D->D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
                         D3DCOLOR_XRGB(0,0,155), 1.0f, 0 );

	//Начало сцены
    if( SUCCEEDED( Hardware3D->D3DDevice->BeginScene() ) )
    { 
		
		//Тут надо поставить камеру		
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
		
		D3DXMatrixLookAtLH( &MatView, &(Camera3D->Position), &(Camera3D->LookAtPoint), &vUpVec );
		Hardware3D->D3DDevice->SetTransform( D3DTS_VIEW, &MatView );
		
		
		D3DXMatrixPerspectiveFovLH( &MatProj, D3DX_PI/4, 1.0f, 1.0f, 4096.0f );
		Hardware3D->D3DDevice->SetTransform( D3DTS_PROJECTION, &MatProj );
		
		//Рендер объектов из списка
		if( ObjectList.size() != 0 )
			RecursRender(QTree);
		
		Hardware3D->D3DDevice->EndScene();
	
	}

	Hardware3D->D3DDevice->Present( NULL, NULL, NULL, NULL );

	return true;
}



void CScene3D::RecursRender(Node* _Node)
{
	if(_Node->Level == 6)
	{
		std::list<CObject3D*>::iterator it = _Node->ObjectList.begin();
		for( ; it != _Node->ObjectList.end(); ++it)
			(*it)->Render();
		return;
	}

	if(_Node->Children[0]->Visible)
		RecursRender(_Node->Children[0]);
	if(_Node->Children[1]->Visible)
		RecursRender(_Node->Children[1]);
	if(_Node->Children[2]->Visible)
		RecursRender(_Node->Children[2]);
	if(_Node->Children[3]->Visible)
		RecursRender(_Node->Children[3]);

	return;
}



float Length(float vec[3])
{
	return sqrt( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] );
}



//Обновление
bool CScene3D::Update(float fElpasedTime)
{
	Camera3D->Update(fElpasedTime);

	D3DXMATRIXA16 clip;
	float t;

	D3DXMatrixMultiply( &clip, &MatView, &MatProj );

	// извлекаем уравнение правой плоскости 
	frustum[0].normal[0] = clip[ 3] - clip[ 0]; 
	frustum[0].normal[1] = clip[ 7] - clip[ 4]; 
	frustum[0].normal[2] = clip[11] - clip[ 8]; 
	frustum[0].dist = clip[15] - clip[12]; 

	// нормализуем результат 
	t = 1/Length(frustum[0].normal); 
	frustum[0].normal[0] *= t; 
	frustum[0].normal[1] *= t; 
	frustum[0].normal[2] *= t; 
	frustum[0].dist *= t; 

	// извлекаем левую плоскость 
	frustum[1].normal[0] = clip[ 3] + clip[ 0]; 
	frustum[1].normal[1] = clip[ 7] + clip[ 4]; 
	frustum[1].normal[2] = clip[11] + clip[ 8]; 
	frustum[1].dist = clip[15] + clip[12]; 

	// нормализуем результат 
	t = 1/Length(frustum[1].normal); 
	frustum[1].normal[0] *= t; 
	frustum[1].normal[1] *= t; 
	frustum[1].normal[2] *= t; 
	frustum[1].dist *= t; 

	// извлекаем нижнюю плоскость 
	frustum[2].normal[0] = clip[ 3] + clip[ 1]; 
	frustum[2].normal[1] = clip[ 7] + clip[ 5]; 
	frustum[2].normal[2] = clip[11] + clip[ 9]; 
	frustum[2].dist = clip[15] + clip[13]; 

	// нормализуем результат 
	t = 1/Length(frustum[2].normal); 
	frustum[2].normal[0] *= t; 
	frustum[2].normal[1] *= t; 
	frustum[2].normal[2] *= t; 
	frustum[2].dist *= t; 

	// извлекаем верхнюю плоскость 
	frustum[3].normal[0] = clip[ 3] - clip[ 1]; 
	frustum[3].normal[1] = clip[ 7] - clip[ 5]; 
	frustum[3].normal[2] = clip[11] - clip[ 9]; 
	frustum[3].dist = clip[15] - clip[13]; 

	// нормализуем результат 
	t = 1/Length(frustum[3].normal); 
	frustum[3].normal[0] *= t; 
	frustum[3].normal[1] *= t; 
	frustum[3].normal[2] *= t; 
	frustum[3].dist *= t; 

	// извлекаем уравнение дальней плоскости 
	frustum[4].normal[0] = clip[ 3] - clip[ 2]; 
	frustum[4].normal[1] = clip[ 7] - clip[ 6]; 
	frustum[4].normal[2] = clip[11] - clip[10]; 
	frustum[4].dist = clip[15] - clip[14]; 

	// нормализуем результат 
	t = 1/Length(frustum[4].normal); 
	frustum[4].normal[0] *= t; 
	frustum[4].normal[1] *= t; 
	frustum[4].normal[2] *= t; 
	frustum[4].dist *= t; 

	// извлекаем ближнюю плоскость 
	frustum[5].normal[0] = clip[ 3] + clip[ 2]; 
	frustum[5].normal[1] = clip[ 7] + clip[ 6]; 
	frustum[5].normal[2] = clip[11] + clip[10]; 
	frustum[5].dist = clip[15] + clip[14]; 

	// нормализуем результат 
	t = 1/Length(frustum[5].normal); 
	frustum[5].normal[0] *= t; 
	frustum[5].normal[1] *= t; 
	frustum[5].normal[2] *= t; 
	frustum[5].dist *= t;

	
	std::list<CObject3D*>::iterator it = ObjectList.begin();	
	if( ObjectList.size() == 0 ) return false;
	for( ; it != ObjectList.end(); ++it)
		(*it)->Update(fElpasedTime);
	
	QTree->ObjectList = ObjectList;
	UpdateQuadTree(QTree);

	return true;
}



//Добавление объекта
bool CScene3D::AddObject(CObject3D* _Object3D)
{
	std::list<CObject3D*>::iterator it = ObjectList.begin();
	ObjectList.insert( it, _Object3D);

	return true;
}



//Удаление объекта
bool CScene3D::DelObject(CObject3D* _Object3D)
{
	ObjectList.remove(_Object3D);

	return true;
}



//Очистка списка
bool CScene3D::ClearList()
{
	std::list<CObject3D*>::iterator it = ObjectList.begin();

	for( ; it != ObjectList.end(); ++it)
	{
		//ObjectList.remove( (*it) );
		delete (*it);
	}

	ObjectList.clear();

	return true;
}



void CScene3D::Build(Node* _Node)
{
	if(_Node->Level == 6)
		return;	
		
	_Node->Children[0] = new Node;
	_Node->Children[0]->Parent = _Node;
	_Node->Children[0]->x1 = _Node->x1;
	_Node->Children[0]->x2 = (_Node->x2 + _Node->x1)/2.0;
	_Node->Children[0]->z1 = (_Node->z2 + _Node->z1)/2.0;
	_Node->Children[0]->z2 = _Node->z2;
	_Node->Children[0]->y1 = _Node->y1;
	_Node->Children[0]->y2 = _Node->y2;
	_Node->Children[0]->Level = _Node->Level + 1;
	_Node->Children[0]->LOD = 3;
	_Node->Children[0]->Visible = true;

	Build(_Node->Children[0]);

	_Node->Children[1] = new Node;
	_Node->Children[1]->Parent = _Node;
	_Node->Children[1]->x2 = _Node->x2;
	_Node->Children[1]->x1 = (_Node->x2 + _Node->x1)/2.0;
	_Node->Children[1]->z1 = (_Node->z2 + _Node->z1)/2.0;
	_Node->Children[1]->z2 = _Node->z2;
	_Node->Children[1]->y1 = _Node->y1;
	_Node->Children[1]->y2 = _Node->y2;
	_Node->Children[1]->Level = _Node->Level + 1;
	_Node->Children[1]->LOD = 3;
	_Node->Children[1]->Visible = true;

	Build(_Node->Children[1]);

	_Node->Children[2] = new Node;
	_Node->Children[2]->Parent = _Node;
	_Node->Children[2]->x1 = _Node->x1;
	_Node->Children[2]->x2 = (_Node->x2 + _Node->x1)/2.0;
	_Node->Children[2]->z2 = (_Node->z2 + _Node->z1)/2.0;
	_Node->Children[2]->z1 = _Node->z1;
	_Node->Children[2]->y1 = _Node->y1;
	_Node->Children[2]->y2 = _Node->y2;
	_Node->Children[2]->Level = _Node->Level + 1;
	_Node->Children[2]->LOD = 3;
	_Node->Children[2]->Visible = true;

	Build(_Node->Children[2]);

	_Node->Children[3] = new Node;
	_Node->Children[3]->Parent = _Node;
	_Node->Children[3]->x2 = _Node->x2;
	_Node->Children[3]->x1 = (_Node->x2 + _Node->x1)/2.0;
	_Node->Children[3]->z2 = (_Node->z2 + _Node->z1)/2.0;
	_Node->Children[3]->z1 = _Node->z1;
	_Node->Children[3]->y1 = _Node->y1;
	_Node->Children[3]->y2 = _Node->y2;
	_Node->Children[3]->Level = _Node->Level + 1;
	_Node->Children[3]->LOD = 3;
	_Node->Children[3]->Visible = true;

	Build(_Node->Children[3]);

	return;
}



//Построение quad-дерева
bool CScene3D::BuildQuadTree()
{
	QTree = new Node;
	QTree->Parent = NULL;
	QTree->x1 = 0.0f;
	QTree->x2 = 4096.0f;
	QTree->y1 = 0.0f;
	QTree->y2 = 512.0f;
	QTree->z1 = 0.0f;
	QTree->z2 = 4096.0f;
	QTree->Visible = true;
	QTree->LOD = 1;
	QTree->Level = 0;

	Build(QTree);
	
    return true;
}



//Обновление quad-дерева
bool CScene3D::UpdateQuadTree(Node* _Node)
{
	//Заполняем объекты	
	_Node->Children[0]->ObjectList.clear();
	_Node->Children[1]->ObjectList.clear();
	_Node->Children[2]->ObjectList.clear();
	_Node->Children[3]->ObjectList.clear();
	std::list<CObject3D*>::iterator it = _Node->ObjectList.begin();
	for( ; it != _Node->ObjectList.end(); ++it)
	{
		if( (*it)->Position.x >= _Node->Children[0]->x1 &&
			(*it)->Position.x <= _Node->Children[0]->x2 &&
			(*it)->Position.y >= _Node->Children[0]->y1 &&
			(*it)->Position.y <= _Node->Children[0]->y2 &&
			(*it)->Position.z >= _Node->Children[0]->z1 &&
			(*it)->Position.z <= _Node->Children[0]->z2 )
			_Node->Children[0]->AddObject( (*it) );
		if( (*it)->Position.x >= _Node->Children[1]->x1 &&
			(*it)->Position.x <= _Node->Children[1]->x2 &&
			(*it)->Position.y >= _Node->Children[1]->y1 &&
			(*it)->Position.y <= _Node->Children[1]->y2 &&
			(*it)->Position.z >= _Node->Children[1]->z1 &&
			(*it)->Position.z <= _Node->Children[1]->z2 )
			_Node->Children[1]->AddObject( (*it) );
		if( (*it)->Position.x >= _Node->Children[2]->x1 &&
			(*it)->Position.x <= _Node->Children[2]->x2 &&
			(*it)->Position.y >= _Node->Children[2]->y1 &&
			(*it)->Position.y <= _Node->Children[2]->y2 &&
			(*it)->Position.z >= _Node->Children[2]->z1 &&
			(*it)->Position.z <= _Node->Children[2]->z2 )
			_Node->Children[2]->AddObject( (*it) );
		if( (*it)->Position.x >= _Node->Children[3]->x1 &&
			(*it)->Position.x <= _Node->Children[3]->x2 &&
			(*it)->Position.y >= _Node->Children[3]->y1 &&
			(*it)->Position.y <= _Node->Children[3]->y2 &&
			(*it)->Position.z >= _Node->Children[3]->z1 &&
			(*it)->Position.z <= _Node->Children[3]->z2 )
			_Node->Children[3]->AddObject( (*it) );
	}


	if( NodeVisible(_Node->Children[0]) )
	{
		_Node->Children[0]->Visible = true;

		//Определяем ЛОД
		D3DXVECTOR3 BboxCenter = D3DXVECTOR3( (_Node->Children[0]->x1 + _Node->Children[0]->x2)/2.0,
			(_Node->Children[0]->y1 + _Node->Children[0]->y2)/2.0, 
			(_Node->Children[0]->z1 + _Node->Children[0]->z2)/2.0 );
		
		D3DXVECTOR3 BoxLodVector = Camera3D->Position - BboxCenter;
		if( D3DXVec3Length(&BoxLodVector) <= 228.0 ) 
				_Node->Children[0]->LOD = 1;
		if( D3DXVec3Length(&BoxLodVector) < 512.0 &&
			D3DXVec3Length(&BoxLodVector) > 228.0 ) 
				_Node->Children[0]->LOD = 2;
		if( D3DXVec3Length(&BoxLodVector) >= 512.0 ) 
				_Node->Children[0]->LOD = 3;

		std::list<CObject3D*>::iterator it = _Node->Children[0]->ObjectList.begin();
		for( ; it != _Node->Children[0]->ObjectList.end(); ++it)
			(*it)->LOD = _Node->Children[0]->LOD;
				
		if( _Node->Children[0]->Level != 6)
			UpdateQuadTree(_Node->Children[0]);
	}
	else
		_Node->Children[0]->Visible = false;

	if( NodeVisible(_Node->Children[1]) )
	{
		_Node->Children[1]->Visible = true;
		//Определяем ЛОД
		D3DXVECTOR3 BboxCenter = D3DXVECTOR3( (_Node->Children[1]->x1 + _Node->Children[1]->x2)/2.0,
			(_Node->Children[1]->y1 + _Node->Children[1]->y2)/2.0, 
			(_Node->Children[1]->z1 + _Node->Children[1]->z2)/2.0 );
		
		D3DXVECTOR3 BoxLodVector = Camera3D->Position - BboxCenter;
		if( D3DXVec3Length(&BoxLodVector) <= 228.0 ) 
				_Node->Children[1]->LOD = 1;
		if( D3DXVec3Length(&BoxLodVector) < 512.0 &&
			D3DXVec3Length(&BoxLodVector) > 228.0 ) 
				_Node->Children[1]->LOD = 2;
		if( D3DXVec3Length(&BoxLodVector) >= 512.0 ) 
				_Node->Children[1]->LOD = 3;

		std::list<CObject3D*>::iterator it = _Node->Children[1]->ObjectList.begin();
		for( ; it != _Node->Children[1]->ObjectList.end(); ++it)
			(*it)->LOD = _Node->Children[1]->LOD;
		
		if( _Node->Children[1]->Level != 6)
			UpdateQuadTree(_Node->Children[1]);
	}
	else
		_Node->Children[1]->Visible = false;

	if( NodeVisible(_Node->Children[2]) )
	{
		_Node->Children[2]->Visible = true;
		//Определяем ЛОД
		D3DXVECTOR3 BboxCenter = D3DXVECTOR3( (_Node->Children[2]->x1 + _Node->Children[2]->x2)/2.0,
			(_Node->Children[2]->y1 + _Node->Children[2]->y2)/2.0, 
			(_Node->Children[2]->z1 + _Node->Children[2]->z2)/2.0 );
		
		D3DXVECTOR3 BoxLodVector = Camera3D->Position - BboxCenter;
		if( D3DXVec3Length(&BoxLodVector) <= 228.0 ) 
				_Node->Children[2]->LOD = 1;
		if( D3DXVec3Length(&BoxLodVector) < 512.0 &&
			D3DXVec3Length(&BoxLodVector) > 228.0 ) 
				_Node->Children[2]->LOD = 2;
		if( D3DXVec3Length(&BoxLodVector) >= 512.0 ) 
				_Node->Children[2]->LOD = 3;

		std::list<CObject3D*>::iterator it = _Node->Children[2]->ObjectList.begin();
		for( ; it != _Node->Children[2]->ObjectList.end(); ++it)
			(*it)->LOD = _Node->Children[2]->LOD;
		
		if( _Node->Children[2]->Level != 6)
			UpdateQuadTree(_Node->Children[2]);
	}
	else
		_Node->Children[2]->Visible = false;

	if( NodeVisible(_Node->Children[3]) )
	{
		_Node->Children[3]->Visible = true;
		//Определяем ЛОД
		D3DXVECTOR3 BboxCenter = D3DXVECTOR3( (_Node->Children[3]->x1 + _Node->Children[3]->x2)/2.0,
			(_Node->Children[3]->y1 + _Node->Children[3]->y2)/2.0, 
			(_Node->Children[3]->z1 + _Node->Children[3]->z2)/2.0 );
		
		D3DXVECTOR3 BoxLodVector = Camera3D->Position - BboxCenter;
		if( D3DXVec3Length(&BoxLodVector) <= 228.0 ) 
				_Node->Children[3]->LOD = 1;
		if( D3DXVec3Length(&BoxLodVector) < 512.0 &&
			D3DXVec3Length(&BoxLodVector) > 228.0 ) 
				_Node->Children[3]->LOD = 2;
		if( D3DXVec3Length(&BoxLodVector) >= 512.0 ) 
				_Node->Children[3]->LOD = 3;

		std::list<CObject3D*>::iterator it = _Node->Children[3]->ObjectList.begin();
		for( ; it != _Node->Children[3]->ObjectList.end(); ++it)
			(*it)->LOD = _Node->Children[3]->LOD;
		
		if( _Node->Children[3]->Level != 6)
			UpdateQuadTree(_Node->Children[3]);
	}
	else
		_Node->Children[3]->Visible = false;



    return true;
}




//Изменение состояния
bool CScene3D::ChangeState(int _NewState)
{

	return true;
}


typedef float vertex[3];
#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])



//Определение видимости Би-Бокса
bool CScene3D::NodeVisible(Node* _Node)
{
	vertex verts[8];

	verts[0][0]=_Node->x1;
	verts[0][1]=_Node->y1;
	verts[0][2]=_Node->z1;
	verts[1][0]=_Node->x2;
	verts[1][1]=_Node->y1;
	verts[1][2]=_Node->z1;
	verts[2][0]=_Node->x2;
	verts[2][1]=_Node->y1;
	verts[2][2]=_Node->z2;
	verts[3][0]=_Node->x1;
	verts[3][1]=_Node->y1;
	verts[3][2]=_Node->z2;

	verts[4][0]=_Node->x1;
	verts[4][1]=_Node->y2;
	verts[4][2]=_Node->z1;
	verts[5][0]=_Node->x2;
	verts[5][1]=_Node->y2;
	verts[5][2]=_Node->z1;
	verts[6][0]=_Node->x2;
	verts[6][1]=_Node->y2;
	verts[6][2]=_Node->z2;
	verts[7][0]=_Node->x1;
	verts[7][1]=_Node->y2;
	verts[7][2]=_Node->z2;

	for (int i=0 ; i<6 ; i++) 
	{ 
		for (int j=0 ; j<8 ; j++) 
		{ 
			// если расстояние от вершины до плоскости >= 0, то 
			// переходим к следующей плоскости 
			if (DotProduct(frustum[i].normal, verts[j]) + frustum[i].dist >= 0) 
				break; 
		

		// если расстояния от всех вершин до плоскости были < 0, 
		// то значит параллепипед невидим, возвращаем false 
		if (j == 8) 
			return false; 
		}
	} 

	// все тесты прошли успешно, возвращаем true 
	return true; 
} 