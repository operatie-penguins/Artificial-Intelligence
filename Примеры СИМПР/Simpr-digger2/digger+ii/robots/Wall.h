#pragma once
#include "player.h"
#include "monster.h"
#include "resource.h"
#include "robotsDlg.h"
#include "funcs.h"



class Wall
{
public:
	Wall();
	~Wall();
	void MoveTo(POINT pos);
	void Die();
	void Hit();
	POINT GetMyCoords();
	int health;
};