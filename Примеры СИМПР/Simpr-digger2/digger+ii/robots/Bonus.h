#pragma once

class Bonus
{
public:
	Bonus();
	~Bonus();
	POINT GetMyCoords();
	int points;
	bool State;
	
	bool IfSmaller();
	bool IfTeleport();
	bool IfBigger();
	bool IfMonster();
	bool IfWall();
	bool IfDie();
	bool IfChangeStatus();

	void ToSmaller();
	void Teleport();
	void Bigger();
	void Monster();
	void Wall();
	void ChangeStatus();
	void Die();
};