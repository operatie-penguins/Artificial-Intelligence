#pragma once
#include "robot.h"
class rates
{
public:
	void AddDead(robot* Dead);
	bool IsEmpty();

	bool IfSinner();
	bool IfKiller();
	bool IfDevil();
	bool IfGood();
	bool IfSaint();

	void MakeSinner();
	void MakeKiller();
	void MakeDevil();
	void MakeGood();
	void MakeSaint();

	void Kick();
	int sinner,good,saint,devil,killer;
	rates(void);
	~rates(void);
};
