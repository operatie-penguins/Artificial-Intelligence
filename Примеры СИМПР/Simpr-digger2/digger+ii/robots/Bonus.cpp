#include "StdAfx.h"
#include "mainfield.h"
#include "bonus.h"
#include "funcs.h"
extern MainField* MyField;
Bonus::Bonus()
{
	points=true_rand(7)+1;
	State=0;
	return;
}

POINT Bonus::GetMyCoords()
{
//find itself
	int i,n;
	for(i=0;i<MyField->BonusField->width;i++)
		for(n=0;n<MyField->BonusField->height;n++)
			if(MyField->BonusField->cells[i][n]==this)
			{
				POINT z;
				z.x=i;
				z.y=n;
				return z;
			}
	MessageBox(NULL,"Bonus not found((","ERROR",MB_OK);
	POINT z;
	z.x=0;
	z.y=0;
	return z;
}
Bonus::~Bonus()
{
	return;
}
void Bonus::Die()
{
	POINT z=this->GetMyCoords();
	MyField->BonusField->cells[z.x][z.y]=NULL;
	MyField->BonusField->ContentsVec.erase(MyField->BonusField->ContentsVec.begin()+MyField->BonusField->FindInVector(this));
	delete(this);
}
bool Bonus::IfSmaller()
{
	return IfPossible(20);
}
bool Bonus::IfDie()
{
	return IfPossible(4);
}
bool Bonus::IfTeleport()
{
	return IfPossible(5);
}
bool Bonus::IfBigger()
{
	return IfPossible(10);
}
bool Bonus::IfMonster()
{
	return IfPossible(1);
}
bool Bonus::IfWall()
{
	return IfPossible(1);
}
void Bonus::ToSmaller()
{
	this->points--;
}
void Bonus::Teleport()
{
	POINT dest=this->GetMyCoords();
	POINT dest2;
	for(int i=0;i<100;i++)//100 attempts to put - field may be full
	{
		dest2.x=true_rand(MyField->BonusField->width-1);
		dest2.y=true_rand(MyField->BonusField->height-1);
		if(MyField->IsEmpty(dest2))
		{
			MyField->BonusField->cells[dest2.x][dest2.y]=this;
			MyField->BonusField->cells[dest.x][dest.y]=NULL;
		}
	}
}
void Bonus::Bigger()
{
	this->points++;
}
void Bonus::Monster()
{
	POINT dest=this->GetMyCoords();
	this->Die();
	MyField->MonsterField->PutRandomThing()->MoveTo(dest);
}
void Bonus::Wall()
{
	POINT dest=this->GetMyCoords();
	this->Die();
	MyField->WallField->PutRandomThing()->MoveTo(dest);
}


bool Bonus::IfChangeStatus()
{
	return IfPossible(20);
}

void Bonus::ChangeStatus()
{
	State=1;
}
