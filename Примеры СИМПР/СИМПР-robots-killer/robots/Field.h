#pragma once
#include "robot.h"
#include "resource.h"
#include "robotsDlg.h"
class Field
{
public:
	Field(int width, int height);
	~Field(void);
	void ClearField();
	robot*** cells;
	robot* PutRandomRobot();
	bool IsEmpty(POINT coord);
	bool IsBusy(POINT coord);
	bool IsFine(POINT coord);
	int width;
	int height;
	bool NeedRedraw;
	COLORREF* TeamColors;
	int Teams;
	//CPictureBox Pic;
};
