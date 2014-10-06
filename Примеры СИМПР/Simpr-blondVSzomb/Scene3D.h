//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CScene3D, header file
//////////////////////////////////////////////////////////////////



#ifndef SCENE3D_H
#define SCENE3D_H



#include "Hardware3D.h"
#include <list>

class CObject3D;
class CCamera3D;




	typedef struct Node
	{
		int Level;
		bool Visible;
		float x1, x2, y1, y2, z1, z2;        //B-Box
		int LOD;
		std::list<CObject3D*> ObjectList;

		Node* Parent;
		Node* Children[4];

		bool AddObject(CObject3D* _Object3D)
		{
			std::list<CObject3D*>::iterator it = ObjectList.begin();
			ObjectList.insert( it, _Object3D);

			return true;
		}

		bool DelObject(CObject3D* _Object3D)
		{
			ObjectList.remove(_Object3D);

			return true;
		}

	} Node;



class CScene3D
{
public:

	CHardware3D* Hardware3D;
	int CurrState;
	CCamera3D* Camera3D;

	CScene3D(CHardware3D* _Hardware3D, CCamera3D* _Camera3D);
	~CScene3D();
	
	bool Render();
	bool Update(float fElpasedTime);
	bool AddObject(CObject3D* _Object3D);
	bool DelObject(CObject3D* _Object3D);
	bool ClearList();

	bool BuildQuadTree();
	bool UpdateQuadTree(Node* _Node);

	bool ChangeState(int _NewState);

private:
	std::list<CObject3D*> ObjectList;
	Node* QTree;
	D3DXMATRIXA16 MatView;
	D3DXMATRIXA16 MatProj;

	void Build(Node* _Node);
	bool NodeVisible(Node* _Node);
	void RecursRender(Node* _Node);
};




#endif
