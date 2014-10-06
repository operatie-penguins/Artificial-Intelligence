#pragma once
#include "bonus.h"
class PlayerDirection
{
public:
	PlayerDirection();
	~PlayerDirection();
	void Reset();
	bool left;
	bool right;
	bool down;
	bool up;
};
class Player
{
public:
	Player(void);
	~Player(void);
	POINT GetMyCoords();
	POINT CanGo[5];
	void MoveTo(POINT pos);
	int lifes;
	int points;
	int State;
	void GetBonusHere();
	void HitWall(POINT z);
	void Die();
	void Rebirth();
	void LoseLife();
	bool IsBonusLeft(Bonus* b);
	bool IsBonusRight(Bonus* b);
	bool IsBonusDown(Bonus* b);
	bool IsBonusUp(Bonus* b);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	Bonus* FindNearestBonus();
	POINT NextStepToBonus(Bonus* b);
	bool IsDangerousArea(POINT pos);
	bool AmIInDanger();
	POINT FindSafeArea();
	void GoToSafeArea();
};
