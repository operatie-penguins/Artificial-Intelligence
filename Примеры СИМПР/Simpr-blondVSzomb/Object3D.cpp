//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CObject3D, source file
// ����� ������������ ����������� �������
//////////////////////////////////////////////////////////////////



#include "Object3D.h"



//�����������
CObject3D::CObject3D(CScene3D* _Scene3D)
{
	Type = 0;
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	Scene3D = _Scene3D;
}



//����������
CObject3D::~CObject3D()
{

}



//��������� ����
bool CObject3D::SetType(int _Type)
{
	Type = _Type;
	return true;
}



//��������� �������
bool CObject3D::SetPosition(D3DXVECTOR3 _Position)
{
	Position = _Position;
	return true;
}



//��������� ������ ��������
bool CObject3D::SetVelocity(D3DXVECTOR3 _Velocity)
{
	Velocity = _Velocity;
	return true;
}
