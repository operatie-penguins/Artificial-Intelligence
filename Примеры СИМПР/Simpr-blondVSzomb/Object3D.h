//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CObject3D, header file
//////////////////////////////////////////////////////////////////



#ifndef OBJECT3D_H
#define OBJECT3D_H



#include "Headers.h"

class CScene3D;



class CObject3D
{
public:
	int Type;								   //��� �������
	D3DXVECTOR3 Position;					   //�������	
	D3DXVECTOR3 Velocity;					   //��������
	int LOD;

	CObject3D(CScene3D* _Scene3D); 
	~CObject3D();                  

	bool SetType(int _Type);				   //��������� ���� �������
	bool SetPosition(D3DXVECTOR3 _Position);   //��������� �������	
	bool SetVelocity(D3DXVECTOR3 _Velocity);		   //��������� ��������

	virtual bool Render()=0;				   //���������
	virtual bool Update(float fElpasedTime)=0; //���������� ���������, ������� �� ���� � �.�.

protected:
	CScene3D* Scene3D;						   //�����, ������� ����������� ������
};




#endif
