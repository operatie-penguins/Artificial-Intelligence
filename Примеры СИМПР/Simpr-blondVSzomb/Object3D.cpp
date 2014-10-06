//////////////////////////////////////////////////////////////////
// Project FMfan for SIMPR
// Copyright by Ampleev A., 2007/08
//////////////////////////////////////////////////////////////////
// Class CObject3D, source file
// Класс абстрактного трехмерного объекта
//////////////////////////////////////////////////////////////////



#include "Object3D.h"



//Конструктор
CObject3D::CObject3D(CScene3D* _Scene3D)
{
	Type = 0;
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	Scene3D = _Scene3D;
}



//Деструктор
CObject3D::~CObject3D()
{

}



//Установка типа
bool CObject3D::SetType(int _Type)
{
	Type = _Type;
	return true;
}



//Установка позиции
bool CObject3D::SetPosition(D3DXVECTOR3 _Position)
{
	Position = _Position;
	return true;
}



//Установка модуля скорости
bool CObject3D::SetVelocity(D3DXVECTOR3 _Velocity)
{
	Velocity = _Velocity;
	return true;
}
