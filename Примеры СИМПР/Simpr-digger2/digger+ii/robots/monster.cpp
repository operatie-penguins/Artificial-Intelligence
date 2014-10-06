#include "StdAfx.h"
#include "monster.h"
#include "mainfield.h"
#include "wall.h"
#include "funcs.h"
extern MainField* MyField;

Monster::Monster(void)
{
	CanGo[0].x=-1;
	CanGo[1].x=0;
	CanGo[2].x=0;
	CanGo[3].x=1;

	CanGo[4].x=0;

	CanGo[0].y=0;
	CanGo[1].y=1;
	CanGo[2].y=-1;
	CanGo[3].y=0;

	CanGo[4].y=0;

	SkinId=true_rand(3)+1;
	//SkinId=3;
	State=6;
}

Monster::~Monster(void)
{
}
void Monster::GoToPlayer()
{
	if(IsEnemyUp())
		MoveUp();
	else if(IsEnemyDown())
		MoveDown();
	else if(IsEnemyLeft())
		MoveLeft();
	else if(IsEnemyRight())
		MoveRight();
}


bool Monster::IfDie()
{
	return IfPossible(5);
}
bool Monster::IfEatWallNear()
{
	return IfPossible(10);
}
bool Monster::IfGoForPlayer()
{
	return IfPossible(20);
}
bool Monster::IfGoRandom()
{
	return IfPossible(50);
}

Player* Monster::FindClosePlayer()
{
	POINT dest,dest2;
	dest=this->GetMyCoords();
	for(int i=0;i<4;i++)
	{
		dest2=AddPoints(CanGo[i],dest);
		Player* p=MyField->IsPlayer(dest2);
		if(p!=NULL)
			return p;
	}
	//MessageBox(NULL,"Not found nearest","Error",MB_OK);
	return NULL;
}
Player* Monster::FindEnemy()
{
	return MyField->PlayerField->ContentsVec.at(0);
}
void Monster::EatWall()
{
	POINT dest,dest2;
	dest=this->GetMyCoords();
	for(int i=0;i<4;i++)
	{
		dest2=AddPoints(CanGo[i],dest);
		Wall* w=MyField->IsWall(dest2);
		if(w!=NULL)
		{
			EatThatWall(dest2);
			return;
		}
	}
}

void Monster::EatThatWall(POINT pos)
{
	Wall* w=MyField->IsWall(pos);
	if(w!=NULL)
	{
		w->Die();
		this->MoveTo(pos);
	}
}
void Monster::Kill(Player* pl)
{
	POINT z=pl->GetMyCoords();
	pl->LoseLife();
	this->MoveTo(z);
}
void Monster::HaveFun()
{
	return;
}

POINT Monster::GetMyCoords()
{
//find itself
	int i,n;
	POINT z;
	for(i=0;i<MyField->MonsterField->width;i++)
		for(n=0;n<MyField->MonsterField->height;n++)
		{
			z.x=i;
			z.y=n;
			if(MyField->IsMonster(z)==this)
				return z;
		}
	MessageBox(NULL,"Me, monster not found((","ERROR",MB_OK);
	z.x=0;
	z.y=0;
	return z;
}


void Monster::MakeRandMove()
{
	POINT me=GetMyCoords();
	//found. now - search free cells around from rando direction
	POINT dest;
	
	bool chosen=false;
	int direc;
	for(int i=0;i<20;i++)//20 attempts
	{
		direc=true_rand(3);
		dest.x=me.x+CanGo[direc].x;
		dest.y=me.y+CanGo[direc].y;
		if(MyField->IsEmpty(dest))
		{
			chosen=1;
			break;
		}
	}
	if(chosen)
	{
		MoveTo(dest);
	}
	return;
}

void Monster::MoveTo(POINT pos)
{
	POINT me=GetMyCoords();
	int x=pos.x-me.x;
	int y=pos.y-me.y;
	if(y>0)State=6;
	else if (y<0)State=5;
	else if(x>0)State=8;
	else if(x<0)State=7;
	MyField->MonsterField->cells[me.x][me.y]=NULL;
	MyField->MonsterField->cells[pos.x][pos.y]=this;
	return;
}



void Monster::Die()
{
	POINT z=this->GetMyCoords();
	MyField->MonsterField->cells[z.x][z.y]=NULL;
	//MessageBox(NULL,"DIEING","NFO",MB_OK);
	int n=MyField->MonsterField->FindInVector(this);
	MyField->MonsterField->ContentsVec.erase(MyField->MonsterField->ContentsVec.begin()+n);
	//MessageBox(NULL,"DIES","NFO",MB_OK);
	delete(this);
}

bool Monster::IsEnemyLeft()
{
	Player* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z.x-z1.x)>0)
		return 1;
	return 0;
}
bool Monster::IsEnemyRight()
{
	Player* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z1.x-z.x)>0)
		return 1;
	return 0;
}
bool Monster::IsEnemyDown()
{
	Player* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z1.y-z.y)>0)
		return 1;
	return 0;
}
bool Monster::IsEnemyUp()
{
	Player* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z.y-z1.y)>0)
		return 1;
	return 0;
}
void Monster::MoveUp()
{
	POINT z=this->GetMyCoords();
	z.y--;
	if(CanMove(z))
		this->MoveTo(z);
}
void Monster::MoveDown()
{
	POINT z=this->GetMyCoords();
	z.y++;
	if(CanMove(z))
		this->MoveTo(z);
}
void Monster::MoveLeft()
{
	POINT z=this->GetMyCoords();
	z.x--;
	if(CanMove(z))
		this->MoveTo(z);
}
void Monster::MoveRight()
{
	POINT z=this->GetMyCoords();
	z.x++;
	if(CanMove(z))
		this->MoveTo(z);
}
bool Monster::CanMove(POINT pos)
{
	if(MyField->IsFine(pos)&&(MyField->IsEmpty(pos)))
		return 1;
	return 0;
}