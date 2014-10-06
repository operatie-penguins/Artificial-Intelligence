#include "StdAfx.h"
#include "Field.h"
#include "funcs.h"

Field::Field(int width, int height)
{
	this->height=height;
	this->width=width;
	cells=new robot**[width];
	for(int i=0;i<width;i++)
		cells[i]=new robot*[height];
	ClearField();
	NeedRedraw=0;
	Teams=3;
	TeamColors=new COLORREF[Teams];
	for (int i=0;i<Teams;i++)
		TeamColors[i]=RGB(true_rand(255),true_rand(255),true_rand(255));
}

Field::~Field(void)
{
	//for(int i=0;i<width;i++)
	//	for(int n=0;n<height;n++)
	//		delete(cells[i][n]);
//DOES NOT KILL ROBOTS!
	for(int i=0;i<width;i++)
		delete[] cells[i];
	
	delete[]cells;
	delete []TeamColors;
}

bool Field::IsFine(POINT coord)
{
	if((coord.x<this->width)&&(coord.y<this->height)&&(coord.x>=0)&&(coord.y>=0))
		return 1;
	return 0;
}
bool Field::IsEmpty(POINT coord)
{
	if(IsFine(coord))
		if(cells[coord.x][coord.y]==NULL)
			return 1;
	return 0;
}
bool Field::IsBusy(POINT coord)
{
	if(IsEmpty(coord))
		return 0;
	return 1;
}


void Field::ClearField()
{
	for(int i=0;i<width;i++)
		for(int n=0;n<height;n++)
			cells[i][n]=NULL;
}

robot* Field::PutRandomRobot()
{
	unsigned int number;
	robot* k=new robot();
	POINT dest;
	for(int i=0;i<100;i++)//100 attempts to put robot - field may be full
	{
		dest.x=true_rand(this->width-1);
		dest.y=true_rand(this->height-1);
		if(this->IsEmpty(dest))
		{
			this->cells[dest.x][dest.y]=k;
			NeedRedraw=1;
			return k;
		}
	}
	return NULL;
}