#include "StdAfx.h"
#include "mainfield.h"
#include "funcs.h"
#include "player.h"
#include "bonus.h"

extern MainField* MyField;
//extern vector <Monster*> MonsterVec;
//extern vector <Bonus*> BonusVec;

void Player::GoToSafeArea()
{
	POINT pos=this->FindSafeArea();
	this->MoveTo(pos);
}
bool Player::IsDangerousArea(POINT pos)
{
	POINT m;
	for(int i=-1;i<2;i++)
		for(int n=-1;n<2;n++)
			if(n*i==0)//no diagonal
			{
				m=pos;
				m.x+=i;
				m.y+=n;
				if(MyField->IsMonster(m))
					return 1;
			}
	return 0;
}
bool Player::AmIInDanger()
{
	POINT pos,m;
	pos=this->GetMyCoords();
	return IsDangerousArea(pos);
}
POINT Player::FindSafeArea()
{
	POINT pos,m;
	pos=this->GetMyCoords();
	for(int i=-1;i<2;i++)
		for(int n=-1;n<2;n++)
		{
			if(n*i==0)//no diagonal
			{
				m=pos;
				m.x+=i;
				m.y+=n;
				if(!IsDangerousArea(m))
					return m;
			}
		}
		return pos;
}
bool Player::IsBonusLeft(Bonus* b)
{
	POINT z1=b->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z.x-z1.x)>0)
		return 1;
	return 0;
}
bool Player::IsBonusRight(Bonus* b)
{
	POINT z1=b->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z1.x-z.x)>0)
		return 1;
	return 0;
}
bool Player::IsBonusDown(Bonus* b)
{
	POINT z1=b->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z1.y-z.y)>0)
		return 1;
	return 0;
}
bool Player::IsBonusUp(Bonus* b)
{
	POINT z1=b->GetMyCoords();
	POINT z=this->GetMyCoords();
	if((z.y-z1.y)>0)
		return 1;
	return 0;
}

POINT Player::NextStepToBonus(Bonus* b)
{
	POINT pos=this->GetMyCoords();
	if(IsBonusUp(b))
		pos.y--;
	else if(IsBonusDown(b))
		pos.y++;
	else if(IsBonusLeft(b))
		pos.x--;
	else if(IsBonusRight(b))
		pos.x++;
	return pos;
}

Bonus* Player::FindNearestBonus()
{
	POINT pos,p;
	pos=this->GetMyCoords();
	for(int i=1;i<MyField->BonusField->width;i++)
		for(int n=1;n<MyField->BonusField->height;n++)
			for(int z=-1;z<2;z++)
				for(int f=-1;f<2;f++)
				{
					p=pos;
					p.x+=i*z;
					p.y+=n*f;
					//CString s;
					//s.Format("%d,%d",p.x,p.y);
					//MessageBox(NULL,s.GetBuffer(),"",MB_OK);
					Bonus* b=MyField->IsBonus(p);
					if(b!=NULL)
						return b;
				}
	return NULL;
}

PlayerDirection::PlayerDirection()
{
	left=0;
	right=0;
	down=0;
	up=0;
}
PlayerDirection::~PlayerDirection()
{
}
void PlayerDirection::Reset()
{
	left=0;
	right=0;
	down=0;
	up=0;
}
Player::Player(void)
{
	lifes=5;
	points=0;
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
	State=6;
}

Player::~Player(void)
{
}
void Player::LoseLife()
{
	State=0;
	lifes--;
}

void Player::HitWall(POINT z)
{
	MyField->WallField->cells[z.x][z.y]->Hit();
}
void Player::Die()
{
	POINT z=this->GetMyCoords();
	MyField->PlayerField->cells[z.x][z.y]=NULL;
	int n=MyField->PlayerField->FindInVector(this);
	MyField->PlayerField->ContentsVec.erase(MyField->PlayerField->ContentsVec.begin()+n);
	delete(this);
}

void Player::Rebirth()
{
	POINT z=this->GetMyCoords();
	MyField->PlayerField->cells[z.x][z.y]=NULL;
	for(int i=0;i<100;i++)//100 attempts to put - field may be full
	{
		z.x=true_rand(MyField->PlayerField->width-1);
		z.y=true_rand(MyField->PlayerField->height-1);
		if(MyField->IsEmpty(z))
		{
			MyField->PlayerField->cells[z.x][z.y]=this;
			this->State=6;
			return;
		}
	}
}

void Player::GetBonusHere()
{
	POINT z=this->GetMyCoords();
	if(MyField->IsBonus(z))
	{
		Bonus* bonus=MyField->IsBonus(z);//BonusField->cells[z.x][z.y];
		this->points+=bonus->points;
		bonus->Die();
	}
}
POINT Player::GetMyCoords()
{
//find itself
	int i,n;
	for(i=0;i<MyField->PlayerField->width;i++)
		for(n=0;n<MyField->PlayerField->height;n++)
			if(MyField->PlayerField->cells[i][n]==this)
			{
				POINT z;
				z.x=i;
				z.y=n;
				return z;
			}
	MessageBox(NULL,"Player not found((","ERROR",MB_OK);
	POINT z;
	z.x=0;
	z.y=0;
	return z;
}


void Player::MoveTo(POINT pos)
{
	if(MyField->IsFine(pos))
	{
		if(MyField->IsWall(pos)!=NULL)
			HitWall(pos);
		else if(MyField->IsMonster(pos))
			MessageBox(NULL,"WTF?! Player attacking monster?!","Error",MB_OK);
		else
		{
			POINT me=GetMyCoords();
			MyField->PlayerField->cells[me.x][me.y]=NULL;
			MyField->PlayerField->cells[pos.x][pos.y]=this;
			if(pos.x>me.x)
				this->State=8;
			else if(pos.x<me.x)
				this->State=7;
			else if(pos.y>me.y)
				this->State=6;
			else if(pos.y<me.y)
				this->State=5;
			this->GetBonusHere();
		}
	}
	return;
}

void Player::MoveUp()
{
	POINT z=this->GetMyCoords();
	z.y--;
	this->MoveTo(z);
}
void Player::MoveDown()
{
	POINT z=this->GetMyCoords();
	z.y++;
	this->MoveTo(z);
}
void Player::MoveLeft()
{
	POINT z=this->GetMyCoords();
	z.x--;
	this->MoveTo(z);
}
void Player::MoveRight()
{
	POINT z=this->GetMyCoords();
	z.x++;
	this->MoveTo(z);
}