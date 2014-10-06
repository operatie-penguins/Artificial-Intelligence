#pragma once
class robot
{
public:
	robot(void);
	~robot(void);
	void MakeRandMove();
	POINT GetMyCoords();
	POINT CanGo[5];
	void MoveTo(POINT pos);
	int health;
	int command;
	int kills;
	robot* FindNearest();
	void Kill(robot* Second);
	void Join(robot* Second);
	bool CmpHealth(robot* Second);
	void RunFromDangerousEnemy();
	bool IsFriend(robot*);
	robot* FindJoinableFriend();
	robot* FindDangerousEnemy();
	robot* FindWeakEnemy();
	int FindInVector();
	void Die();
	bool IsJoinable(robot* Second);
	bool IsEnemyLeft();
	bool IsEnemyRight();
	bool IsEnemyDown();
	bool IsEnemyUp();
	robot* FindEnemy();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};
