#include "StdAfx.h"
#include "mainfield.h"
#include "field.h"
MainField::MainField(int width,int height)
{
	this->PlayerField=new Field <Player>(width,height);
	this->BonusField=new Field <Bonus>(width,height);
	this->WallField=new Field <Wall>(width,height);
	this->MonsterField=new Field <Monster>(width,height);
	return;
}
MainField::~MainField()
{
	delete(this->PlayerField);
	delete(this->BonusField);
	delete(this->WallField);
	delete(this->MonsterField);
	return;
}
bool MainField::IsEmpty(POINT dest)
{
	return this->MonsterField->IsEmpty(dest)&&this->BonusField->IsEmpty(dest)&&this->PlayerField->IsEmpty(dest)&&this->WallField->IsEmpty(dest);
}
bool MainField::IsBusy(POINT dest)
{
	return !IsEmpty(dest);
}
Player* MainField::IsPlayer(POINT dest)
{
	if(this->PlayerField->IsFine(dest))
		if(this->PlayerField->cells[dest.x][dest.y]!=NULL)
			return this->PlayerField->cells[dest.x][dest.y];
	return NULL;
}
Wall* MainField::IsWall(POINT dest)
{
	if(this->WallField->IsFine(dest))
		if(this->WallField->cells[dest.x][dest.y]!=NULL)
			return this->WallField->cells[dest.x][dest.y];
	return NULL;
}
Monster* MainField::IsMonster(POINT dest)
{
	if(this->MonsterField->IsFine(dest))
		if(this->MonsterField->cells[dest.x][dest.y]!=NULL)
			return this->MonsterField->cells[dest.x][dest.y];
	return NULL;
}
Bonus* MainField::IsBonus(POINT dest)
{
	if(this->BonusField->IsFine(dest))
		if(this->BonusField->cells[dest.x][dest.y]!=NULL)
			return this->BonusField->cells[dest.x][dest.y];
	return NULL;
}

bool MainField::IsFine(POINT dest)
{
	return this->PlayerField->IsFine(dest);
}
bool MainField::AddBonus()
{
	return IfPossible(10);
}
bool MainField::AddMonster()
{
	return IfPossible(10);
}
bool MainField::AddWall()
{
	return IfPossible(8);
}