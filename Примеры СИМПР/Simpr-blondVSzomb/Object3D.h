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
	int Type;								   //Тип объекта
	D3DXVECTOR3 Position;					   //Позиция	
	D3DXVECTOR3 Velocity;					   //Скорость
	int LOD;

	CObject3D(CScene3D* _Scene3D); 
	~CObject3D();                  

	bool SetType(int _Type);				   //Установка типа объекта
	bool SetPosition(D3DXVECTOR3 _Position);   //Установка позиции	
	bool SetVelocity(D3DXVECTOR3 _Velocity);		   //Установка скорости

	virtual bool Render()=0;				   //Рендеринг
	virtual bool Update(float fElpasedTime)=0; //Обновление положения, реакция на ввод и т.д.

protected:
	CScene3D* Scene3D;						   //Сцена, которой принадлежит объект
};




#endif
