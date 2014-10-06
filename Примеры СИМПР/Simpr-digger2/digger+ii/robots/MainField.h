#include "player.h"
#include "monster.h"
#include "bonus.h"
#include "wall.h"
#include "field.h"
#pragma once

class MainField
{
public:
	MainField(int width,int height);
	~MainField();
	//bool NeedRedraw;
	bool IsEmpty(POINT dest);
	bool IsBusy(POINT dest);
	bool IsFine(POINT dest);
	bool AddBonus();
	bool AddMonster();
	bool AddWall();
	Monster* IsMonster(POINT dest);
	Bonus* IsBonus(POINT dest);
	Player* IsPlayer(POINT dest);
	Wall* IsWall(POINT dest);
	Field <Monster>* MonsterField;
	Field <Bonus>* BonusField;
	Field <Player>* PlayerField;
	Field <Wall>* WallField;
};
