#include "StdAfx.h"
#include "robot.h"
#include "rates.h"
#include "funcs.h"
#include "Field.h"

extern Field* MyField;
extern rates purgatory;
extern vector <robot*> RobotVec;
POINT AddPoints(POINT point1,POINT point2)
{
	POINT res;
	res.x=point1.x+point2.x;
	res.y=point1.y+point2.y;
	return res;
}
bool CmpPoints(POINT point1,POINT point2)
{
	if((point1.x==point2.x)&&(point1.y==point2.y))
		return 1;
	return 0;
}
robot::robot(void)
{
	health=true_rand(100);
	command=true_rand(MyField->Teams-1);
	kills=0;
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
}

robot::~robot(void)
{
}

POINT robot::GetMyCoords()
{
//find itself
	int i,n;
	for(i=0;i<MyField->width;i++)
		for(n=0;n<MyField->height;n++)
			if(MyField->cells[i][n]==this)
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


void robot::MakeRandMove()
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
			chosen=1;
		break;
	}
	if(chosen)
	{
		MoveTo(dest);
		MyField->NeedRedraw=1;
	}
	return;
}

void robot::MoveTo(POINT pos)
{
	POINT me=GetMyCoords();
	MyField->cells[me.x][me.y]=NULL;
	MyField->cells[pos.x][pos.y]=this;
	return;
}


robot* robot::FindNearest()
{
	POINT dest;
	dest=this->GetMyCoords();
	for(int i=0;i<4;i++)
	{
		POINT dest2=AddPoints(CanGo[i],dest);
		if(MyField->IsFine(dest2))
			if(MyField->IsBusy(dest2))
				return MyField->cells[dest2.x][dest2.y];
	}
	//MessageBox(NULL,"Not found nearest","Error",MB_OK);
	return NULL;
}
void robot::Kill(robot* Second)
{
	POINT z=Second->GetMyCoords();
	int temp=this->health;
	this->health=this->health-Second->health;
	Second->health=Second->health-temp;
	if(Second->health<=0)
	{
		this->kills++;
		Second->Die();
		this->MoveTo(z);
	}
	if(this->health<=0)
		this->Die();
}

int robot::FindInVector()
{
	for(int i=0;i<RobotVec.size();i++)
		if(RobotVec.at(i)==this)
			return i;
	MessageBox(NULL,"Not found in RobotVec","Error",MB_OK);
	return -1;
}
void robot::Die()
{
	POINT z=this->GetMyCoords();
	MyField->cells[z.x][z.y]=NULL;
	RobotVec.erase(RobotVec.begin()+FindInVector());
	purgatory.AddDead(this);
	//delete(this);
}

void robot::Join(robot* Second)
{
	POINT z=Second->GetMyCoords();
	this->health+=Second->health;
	this->kills+=Second->kills;
	this->MoveTo(z);
	RobotVec.erase(RobotVec.begin()+Second->FindInVector());
	delete(Second);
}

bool robot::IsJoinable(robot* Second)
{
	if(this->health+Second->health<=100)
		return 1;
	return 0;
}
bool robot::CmpHealth(robot* Second)
{
	if(this->health>=Second->health)
		return 1;
	else
		return 0;
}
void robot::RunFromDangerousEnemy()
{
	robot* enemy=FindDangerousEnemy();
	POINT z1=this->GetMyCoords();
	POINT z2=enemy->GetMyCoords();
	bool danger;
	for(int x=0;x<5;x++)
	{
		danger=0;
		POINT dest=AddPoints(z1,CanGo[x]);
		if(MyField->IsFine(dest)&&MyField->IsEmpty(dest))
		{
			for(int y=0;y<5;y++)
			{
				if(CmpPoints(dest,AddPoints(z2,CanGo[y])))
					danger=1;
			}
			if(!danger)
				MoveTo(dest);
		}
	}
}


robot* robot::FindJoinableFriend()
{
	robot* r;
	POINT z1=this->GetMyCoords();
	for(int i=0;i<4;i++)
	{
		POINT dest=AddPoints(z1,CanGo[i]);
		if(MyField->IsFine(dest)&&MyField->IsBusy(dest))
		{
			r=MyField->cells[dest.x][dest.y];
			if(IsJoinable(r)&&IsFriend(r))
				return r;
		}
	}
	return NULL;
}

robot* robot::FindDangerousEnemy()
{
	robot* r;
	POINT z1=this->GetMyCoords();
	for(int i=0;i<4;i++)
	{
		POINT dest=AddPoints(z1,CanGo[i]);
		if(MyField->IsFine(dest)&&MyField->IsBusy(dest))
		{
			r=MyField->cells[dest.x][dest.y];
			if(!CmpHealth(r)&&!IsFriend(r))
				return r;
		}
	}
	return NULL;
}

robot* robot::FindWeakEnemy()
{
	robot* r;
	POINT z1=this->GetMyCoords();
	for(int i=0;i<4;i++)
	{
		POINT dest=AddPoints(z1,CanGo[i]);
		if(MyField->IsFine(dest)&&MyField->IsBusy(dest))
		{
			r=MyField->cells[dest.x][dest.y];
			if(CmpHealth(r)&&!IsFriend(r))
				return r;
		}
	}
	return NULL;
}
bool robot::IsFriend(robot* Second)
{
	if(this->command==Second->command)
		return 1;
	return 0;
}


robot* robot::FindEnemy()
{
	for(int i=0;i<RobotVec.size();i++)
		if(RobotVec.at(i)!=this)
			return RobotVec.at(i);
	return NULL;
}
bool robot::IsEnemyLeft()
{
	robot* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z.x-z1.x)>0)
		return 1;
	return 0;
}
bool robot::IsEnemyRight()
{
	robot* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z1.x-z.x)>0)
		return 1;
	return 0;
}
bool robot::IsEnemyDown()
{
	robot* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z1.y-z.y)>0)
		return 1;
	return 0;
}
bool robot::IsEnemyUp()
{
	robot* enemy=FindEnemy();
	POINT z1=enemy->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z.y-z1.y)>0)
		return 1;
	return 0;
}
void robot::MoveUp()
{
	POINT z=this->GetMyCoords();
	if(z.y>0)
		z.y--;
	this->MoveTo(z);
}
void robot::MoveDown()
{
	POINT z=this->GetMyCoords();
	if(z.y<MyField->height-1)
		z.y++;
	this->MoveTo(z);
}
void robot::MoveLeft()
{
	POINT z=this->GetMyCoords();
	if(z.x>0)
		z.x--;
	this->MoveTo(z);
}
void robot::MoveRight()
{
	POINT z=this->GetMyCoords();
	if(z.x<MyField->width-1)
		z.x++;
	this->MoveTo(z);
}