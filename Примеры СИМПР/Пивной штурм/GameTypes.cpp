//---------------------------------------------------------------------------


#pragma hdrstop

#include "GameTypes.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Visitor *CreateNewVisitor(int TableNum)
{
        Visitor *Vis = new Visitor;
        ZeroMemory(Vis,sizeof(Visitor));
        Vis->TableNum = TableNum;
        Vis->AlreadyTurn = true;
        return Vis;
}

void SetVisitorDrinkingState(Visitor *Vis)
{
        Vis->Drinking = true;
        Vis->DrinkTime = 1;
}

void SetVisitorWrangleState(Visitor *Vis)
{
        Vis->Wrangle = true;
        Vis->WrangleTime = 1;
}

void UpdateVisitor(Visitor *Vis)
{
        if (Vis->Drinking)
        {
                if (Vis->DrinkTime > DRINK_TIME)
                {
                        Vis->Drinking = false;
                        Vis->AlreadyDrink = true;
                        return;
                }
                else
                {
                        Vis->DrinkTime++;
                        return;
                }
        }

        if (Vis->Wrangle)
        {
                if (Vis->WrangleTime > WRANGLE_TIME)
                {
                        Vis->Wrangle = false;
                        Vis->ToLongWrangle = true;
                        return;
                }
                else
                {
                        Vis->WrangleTime++;
                        return;
                }
        }

        Vis->Position++;
}

Jar* CreateNewJar(int TableNum, int Position, bool Reverse)
{
	Jar *jar = new Jar;
	jar->TableNum = TableNum;
	jar->Position = Position;
	jar->Reverse = Reverse;

	return jar;
}

