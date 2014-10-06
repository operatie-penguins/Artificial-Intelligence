#pragma once
#include "player.h"
class Monster
{
public:
	Monster(void);
	~Monster(void);
	int SkinId;
	int State;
	void MakeRandMove();
	POINT GetMyCoords();
	POINT CanGo[5];
	void MoveTo(POINT pos);
	void Die();
	bool IsEnemyLeft();
	bool IsEnemyRight();
	bool IsEnemyDown();
	bool IsEnemyUp();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void GoToPlayer();
	Player* FindClosePlayer();
	Player* FindEnemy();
	void EatWall();
	void EatThatWall(POINT pos);
	bool CanMove(POINT pos);
	void Kill(Player* pl);
	void HaveFun();

	bool IfDie();
	bool IfEatWallNear();
	bool IfGoForPlayer();
	bool IfGoRandom();
};
