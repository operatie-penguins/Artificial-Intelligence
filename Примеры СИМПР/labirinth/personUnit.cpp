//---------------------------------------------------------------------------
#pragma hdrstop
#include "personUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#include "mainFormUnit.h"
//---------------------------------------------------------------------------

Person::Person(bMaps bm,TImage * img) : dir(up), rotations(0)
{
    image = img;
    bitMaps[0]=bm[0];
    bitMaps[1]=bm[1];
    bitMaps[2]=bm[2];
    bitMaps[3]=bm[3];
    changePicture(dir);
    show();
    randomize();
}
//---------------------------------------------------------------------------

Person::~Person()
{
    delete image;
}
//---------------------------------------------------------------------------

bool Person::onEdge()
{
    return ((x==0)||(x==mainForm->getMazeWidth()-1)||(y==0)||(y==mainForm->getMazeHeight()-1));
}
//---------------------------------------------------------------------------

int Person::getX()
{
    return x;
}
//---------------------------------------------------------------------------

int Person::getRotations()
{
    return rotations;
}
//---------------------------------------------------------------------------

int Person::getY()
{
    return y;
}
//---------------------------------------------------------------------------

int Person::look()
{
    return dir;
}
//---------------------------------------------------------------------------

bool Person::canGo()
{
    int a,b;
    dis(a,b);
    return (mainForm->look(a,b,x,y)==0);
}
//---------------------------------------------------------------------------

void Person::turn(const int side)
{
    if(dir!=side)
    {
        dir=side;
        changePicture(side);
        rotations++;
    }
}
//---------------------------------------------------------------------------

void Person::changePicture(const int n)
{
    image->Picture->Assign(bitMaps[n]);
}
//---------------------------------------------------------------------------

void Person::go()
{
    int a,b;
    dis(a,b);
    gotoXY(a,b);
    freeRotation();
}
//---------------------------------------------------------------------------

void Person::show()
{
    image->Show();
}
//---------------------------------------------------------------------------

void Person::hide()
{
    image->Hide();
}
//---------------------------------------------------------------------------

void Person::gotoXY(const int xn, const int yn)
{
    x=xn;
    y=yn;
    mainForm->gotoXY(xn,yn,image);
}
//---------------------------------------------------------------------------

void Person::dis(int& a, int &b, const bool key)
{
    int X,Y;
    if(key)
    {
        X = a;
        Y = b;
    }
    else
    {
        X = x;
        Y = y;
    }

    switch(dir)
    {
        case up: { a = X; b = Y-1; } break;
        case right: { a = X+1; b = Y; } break;
        case down: { a = X; b = Y+1; } break;
        case left: { a = X-1; b = Y; } break;
        default: /* "Этого не должно произойти" */;
    }
}
//---------------------------------------------------------------------------

int Person::alert(const int p)
{
    int xl=x,
        yl=y,
        xn,yn;

    dis(xn,yn);

    int answer = mainForm->look(xn,yn,xl,yl);
    int count = 0;
    while(answer==0)
    {
        xl=xn;
        yl=yn;
        dis(xn,yn,true);
        answer = mainForm->look(xn,yn,xl,yl);
        count++;
    }
    if(answer==p) return count;
    return -1;
}
//---------------------------------------------------------------------------

void Person::freeRotation()
{
    rotations=0;
}
//---------------------------------------------------------------------------


Cop::Cop(bMaps bm,TImage *img) : Person(bm,img) {}
//---------------------------------------------------------------------------

void Cop::randomAction()
{
    int choise = random(5);
    if((choise==4)&&canGo()) go();
    else turn(choise);
    rotations=0;
}
//---------------------------------------------------------------------------

Crime::Crime(bMaps bm,TImage * img) : Person(bm,img) {}
//---------------------------------------------------------------------------

void Crime::randomAction()
{
    int choise = random(4);
    turn(choise);
}
//---------------------------------------------------------------------------


