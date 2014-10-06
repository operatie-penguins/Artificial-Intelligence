#include "StdAfx.h"
#include "mainfield.h"
#include "funcs.h"
#include "player.h"
#include "monster.h"
extern MainField* MyField;
Wall::Wall()
{
	health=100;
}
Wall::~Wall()
{
	return;
}

void Wall::MoveTo(POINT pos)
{
	POINT me=GetMyCoords();
	MyField->WallField->cells[me.x][me.y]=NULL;
	MyField->WallField->cells[pos.x][pos.y]=this;
	return;
}
POINT Wall::GetMyCoords()
{
//find itself
	int i,n;
	for(i=0;i<MyField->WallField->width;i++)
		for(n=0;n<MyField->WallField->height;n++)
			if(MyField->WallField->cells[i][n]==this)
			{
				POINT z;
				z.x=i;
				z.y=n;
				return z;
			}
	MessageBox(NULL,"Me not found((","ERROR",MB_OK);
	POINT z;
	z.x=0;
	z.y=0;
	return z;
}
void Wall::Hit()
{
	this->health-=50;
	if(this->health<=0)
		this->Die();
}
void Wall::Die()
{
	int p=MyField->WallField->FindInVector(this);
	POINT z=this->GetMyCoords();
	MyField->WallField->cells[z.x][z.y]=NULL;
	MyField->WallField->ContentsVec.erase(MyField->WallField->ContentsVec.begin()+p);
	delete(this);
}