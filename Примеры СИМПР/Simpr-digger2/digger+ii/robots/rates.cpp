#include "StdAfx.h"
#include "rates.h"
#include "robot.h"

vector <robot*> DeadRobots;
rates::rates(void)
{
	sinner=good=saint=devil=killer=0;
}

rates::~rates(void)
{
}

void rates::AddDead(robot* Dead)
{
	DeadRobots.push_back(Dead);
}

void rates::Kick()
{
	robot* Robot=DeadRobots.at(0);
	DeadRobots.erase(DeadRobots.begin());
	delete(Robot);
}
void rates::MakeSinner()
{
	Kick();
	sinner++;
}
void rates::MakeGood()
{
	Kick();
	good++;
}
void rates::MakeSaint()
{
	Kick();
	saint++;
}
void rates::MakeDevil()
{
	Kick();
	devil++;
}
void rates::MakeKiller()
{
	Kick();
	killer++;
}


bool rates::IfSinner()
{
	if(DeadRobots.size())
		if(DeadRobots.at(0)->kills==2)
			return 1;
	return 0;
}
bool rates::IfKiller()
{
	if(DeadRobots.size())
		if(DeadRobots.at(0)->kills==3)
			return 1;
	return 0;
}
bool rates::IfDevil()
{
	if(DeadRobots.size())
		if(DeadRobots.at(0)->kills>3)
			return 1;
	return 0;
}
bool rates::IfGood()
{
	if(DeadRobots.size())
		if(DeadRobots.at(0)->kills==1)
			return 1;
	return 0;
}
bool rates::IfSaint()
{
	if(DeadRobots.size())
		if(DeadRobots.at(0)->kills==0)
			return 1;
	return 0;
}
bool rates::IsEmpty()
{
	if(DeadRobots.size()>0)
		return 0;
	return 1;
}