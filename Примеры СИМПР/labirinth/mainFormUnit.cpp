//#define debug
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "mainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mazeFrameUnit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

//Адрес файла для сохранения настроек
const AnsiString strOptionsFile = "Options";

//Адреса картинок
const AnsiString strCopUp = "pic\\cop-up.bmp",
                 strCopRight = "pic\\cop-right.bmp",
                 strCopDown = "pic\\cop-down.bmp",
                 strCopLeft = "pic\\cop-left.bmp",

                 strCrimeUp = "pic\\criminal-up.bmp",
                 strCrimeRight = "pic\\criminal-right.bmp",
                 strCrimeDown = "pic\\criminal-down.bmp",
                 strCrimeLeft = "pic\\criminal-left.bmp";

//Соединение с СИМПРом
const AnsiString simprUserMessage = "MyMessage";
const int Yes                = 3,
          No                 = 2,
          Actions            = 1,
          Conditions         = 0;

const int pictureSize  = 30,
          pictureSpace = 3,
          pictureWall  = 1;

//---------------------------------------------------------------------------

TmainForm *mainForm;
//---------------------------------------------------------------------------

__fastcall TmainForm::TmainForm(TComponent* Owner)
  : TForm(Owner), mazeHeight(3), mazeWidth(3), numberCop(0), numberCrime(0),
    mazeThickness(1), delayTime(50)

{
    bmCopUp = new Graphics::TBitmap();
    bmCopUp->LoadFromFile(strCopUp);

    bmCopRight = new Graphics::TBitmap();
    bmCopRight->LoadFromFile(strCopRight);

    bmCopDown = new Graphics::TBitmap();
    bmCopDown->LoadFromFile(strCopDown);

    bmCopLeft = new Graphics::TBitmap();
    bmCopLeft->LoadFromFile(strCopLeft);

    bmCrimeUp = new Graphics::TBitmap();
    bmCrimeUp->LoadFromFile(strCrimeUp);

    bmCrimeRight = new Graphics::TBitmap();
    bmCrimeRight->LoadFromFile(strCrimeRight);

    bmCrimeDown = new Graphics::TBitmap();
    bmCrimeDown->LoadFromFile(strCrimeDown);

    bmCrimeLeft = new Graphics::TBitmap();
    bmCrimeLeft->LoadFromFile(strCrimeLeft);

    randomize();
    setMazeSize(mazeWidth,mazeHeight);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::WndProc(Messages::TMessage &Message)
{
    if(Message.Msg == msgSimpr)
    {
        Message.Result=work(Message.WParamHi, Message.WParamLo, Message.LParam);
        //задержка

        #ifdef debug
        ShowMessage("Message.Result = " + IntToStr(Message.Result));
        #endif

        if((Message.WParamHi==Actions)&&N10->Checked) Sleep(delayTime);
    }
    else TCustomForm::WndProc(Message);
}
//---------------------------------------------------------------------------

bool TmainForm::qFree()
{
    bool key = true;
    int i=0;
    while(key&&(i<qAvaible.size()))
    {
        if(qAvaible[i]) key=false;
        i++;
    }
    return key;
}
//---------------------------------------------------------------------------

bool TmainForm::work(Word WParamHi, Word WParamLo, int LParam)
{
    static int position = 0,
               criminals = numberCrime,
               catched = 0,
               disappeard = 0;

    #ifdef debug
    ShowMessage("position = " + IntToStr(position) + "\n" +
                "criminals = " + IntToStr(criminals) + "\n" +
                "catched = " + IntToStr(catched) + "\n" +
                "disappeard = " + IntToStr(disappeard) + "\n" +
                "WParamHi = " + WParamHi + "\n" +
                "WParamLo = " + WParamLo + "\n" +
                "LParam = " + LParam + "\n");
    #endif


    switch(WParamHi)
    {
            case Conditions :
            {
                switch(WParamLo)
                {
                    case 1 :
                    {
                        switch(LParam)
                        {
                            case 1: return (position < numberCop);
                            case 2: return (position >= numberCop);
                            case 3: return (criminals == 0);
                            case 4: return (catched > disappeard);
                            case 5: return (catched==numberCrime);
                            case 6: return (disappeard==numberCrime);
                        }
                    }
                    case 2 :
                    {
                        switch(LParam)
                        {
                            case 1: return (queue[position]->alert(1)!=-1);
                            case 2: return (queue[position]->look()==up);
                            case 3: return (queue[position]->look()==right);
                            case 4: return (queue[position]->look()==down);
                            case 5: return (queue[position]->look()==left);
                            case 6: return queue[position]->canGo();
                            case 7: return queue[position]->onEdge();
                            case 8: return ifCop(queue[position]->getX(),queue[position]->getY());
                        }
                    }
                    case 3 :
                    {
                        switch(LParam)
                        {
                            case 1: return (queue[position]->alert(2)!=-1);
                            case 2: return (queue[position]->look()==up);
                            case 3: return (queue[position]->look()==right);
                            case 4: return (queue[position]->look()==down);
                            case 5: return (queue[position]->look()==left);
                            case 6: return queue[position]->canGo();
                            case 7: return (queue[position]->getRotations()>=4);
                        }
                    }
                }
            }
            case Actions :
            {
                switch(WParamLo)
                {
                    case 1 :
                    {
                        switch(LParam)
                        {
                            case 1:
                            {
                                say("Все преступники переловлены!");
                                return true;
                            }
                            case 2:
                            {
                                say("Все преступники ушли!");
                                return true;
                            }
                            case 3:
                            {
                                say("Больше половины преступников поймано, копы - молодцы.");
                                return true;
                            }
                            case 4:
                            {
                                say("Больше половины преступников сбежало, копы плохо работают.");
                                return true;
                            }
                        }
                    }
                    case 2 :
                    {
                        switch(LParam)
                        {
                            case 1:
                            {
                                queue[position]->go();
                                return true;
                            }
                            case 2:
                            {
                                queue[position]->turn(up);
                                return true;
                            }
                            case 3:
                            {
                                queue[position]->turn(right);
                                return true;
                            }
                            case 4:
                            {
                                queue[position]->turn(down);
                                return true;
                            }
                            case 5:
                            {
                                queue[position]->turn(left);
                                return true;
                            }
                            case 6:
                            {
                                queue[position]->hide();
                                return true;
                            }
                            case 7:
                            {
                                catched++;
                                criminals--;
                                qAvaible[position-numberCop]=false;
                                return true;
                            }
                            case 8:
                            {
                                disappeard++;
                                criminals--;
                                qAvaible[position-numberCop]=false;
                                return true;
                            }
                            case 9: return true;
                            case 10:
                            {
                                queue[position]->turn(random(4));
                                return true;
                            }
                            case 11:
                            {
                                if(!qFree())
                                {
                                    do
                                    {
                                        if(position<numberCop+numberCrime-1) position++;
                                        else position=0;
                                    }
                                    while((position>=numberCop)&&!qAvaible[position-numberCop]);
                                }

                                return true;
                            }
                        }
                    }
                    case 3 :
                    {
                        switch(LParam)
                        {
                            case 1:
                            {
                                queue[position]->go();
                                return true;
                            }
                            case 2:
                            {
                                queue[position]->turn(up);
                                return true;
                            }
                            case 3:
                            {
                                queue[position]->turn(right);
                                return true;
                            }
                            case 4:
                            {
                                queue[position]->turn(down);
                                return true;
                            }
                            case 5:
                            {
                                queue[position]->turn(left);
                                return true;
                            }
                            case 6:
                            {
                                queue[position]->turn(random(4));
                                return true;
                            }
                            case 7: return true;
                            case 8:
                            {
                                if(!qFree())
                                {
                                    do
                                    {
                                        if(position<numberCop+numberCrime-1) position++;
                                        else position=0;
                                    }
                                    while((position>=numberCop)&&!qAvaible[position-numberCop]);
                                }
                                return true;
                            }
                        }
                    }
                }
            }
    }

    //до суда при нормальной работе не доберётся
    return false;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N2Click(TObject *Sender)
{
    say("пока,пока");
    if(N11->Checked) saveToFile(strOptionsFile);
    exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N4Click(TObject *Sender)
{
    sizeForm->Show();
}
//---------------------------------------------------------------------------

void TmainForm::setMazeSize(const int w = 3,const int h = 3)
{
    mazeWidth = w;
    mazeHeight = h;

    this->mazeFrame->mazePanel->Width=w*pictureSize+(w-1)*pictureSpace+2;
    this->mazeFrame->mazePanel->Height=h*pictureSize+(h-1)*pictureSpace+2;

    delete this->mazeFrame->Image;
    this->mazeFrame->Image = new TImage(mainForm->mazeFrame->mazePanel);
    this->mazeFrame->Image->Parent = mainForm->mazeFrame->mazePanel;
    this->mazeFrame->Image->Show();
    this->mazeFrame->Image->Height=this->mazeFrame->mazePanel->Height-1;
    this->mazeFrame->Image->Width=this->mazeFrame->mazePanel->Width-1;
    this->mazeFrame->Image->Transparent=true;

    say("Размеры поля изменены: ("+IntToStr(w)+","+IntToStr(w)+")");
}
//---------------------------------------------------------------------------

void TmainForm::setNumbers(const int cop = 0,const int crime = 0)
{
    const int maxCrime = (mazeWidth-2)*(mazeHeight-2);
    const int maxCop = 2*mazeWidth+2*mazeHeight-4;

    if(crime>maxCrime)
    {
        ShowMessage("Слишком много преступников. "+IntToStr(maxCrime)+" - максимум");
        numberCrime = maxCrime;
    }
    else
    {
        numberCrime = crime;
    }
    if(cop>maxCop)
    {
        ShowMessage("Слишком много полицейских. "+IntToStr(maxCop)+" - максимум");
        numberCop = maxCop;
    }
    else
    {
        numberCop = cop;
    }
    say("Количество объектов изменено: ("+IntToStr(numberCop)+","+IntToStr(numberCrime)+")");
}
//---------------------------------------------------------------------------

void TmainForm::setThickness(const float t)
{
    mazeThickness = t;
    say("Плотность лабиринта изменена");
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N5Click(TObject *Sender)
{
    numberForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N6Click(TObject *Sender)
{
    thicknessForm->Show();
}
//---------------------------------------------------------------------------

void TmainForm::makeNewMaze()
{
    setWallsDefault();
    intMatrix line;
    vint three;
    for(int i=0; i<mazeWidth-1; i++)
        for(int j=0; j<mazeHeight; j++)
        {
            three.clear();
            three.push_back(0);
            three.push_back(i);
            three.push_back(j);
            line.push_back(three);
        }
    for(int i=0; i<mazeHeight-1; i++)
        for(int j=0; j<mazeWidth; j++)
        {
            three.clear();
            three.push_back(1);
            three.push_back(i);
            three.push_back(j);
            line.push_back(three);
        }
    vint *temp;
    while(line.size())
    {
        temp=&line[random(line.size())];
        if(randomTry()&&avaibleWall((*temp)[0],(*temp)[1],(*temp)[2]))
        {
            setWall((*temp)[0],(*temp)[1],(*temp)[2]);
        }
        line.erase(temp);
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N8Click(TObject *Sender)
{
    say("Создаётся новый лабиринт с плотностью: "+FloatToStr(mazeThickness));
    makeNewMaze();
    drawWalls();
}
//---------------------------------------------------------------------------

bool TmainForm::randomTry()
{
    float a =(rand()/(float)RAND_MAX);
    if(mazeThickness>=a) return true;
    return false;
}
//---------------------------------------------------------------------------

void TmainForm::setWallsDefault()
{
    vint temp;
    for(int i=0; i<mazeHeight; i++)
    {
        temp.push_back(0);
    }
    verticalWalls.clear();
    for(int i=0; i<mazeWidth-1; i++)
    {
        verticalWalls.push_back(temp);
    }
    temp.clear();
    for(int i=0; i<mazeWidth; i++)
    {
        temp.push_back(0);
    }
    horizontalWalls.clear();
    for(int i=0; i<mazeHeight-1; i++)
    {
        horizontalWalls.push_back(temp);
    }
}
//---------------------------------------------------------------------------

bool TmainForm::avaibleWall(const int type,const int x,const int y)
{
    return (!edgeBarrier(type,x,y,true)&&!loopBarrier(type,x,y,0,true));
}
//---------------------------------------------------------------------------

bool TmainForm::edgeWall(const int type, const int x, const int y)
{
    bool key=false;
    if(type==0)
    {
        if((y==0)||(y==mazeHeight-1)) key=true;
    }
    else
    {
        if((y==0)||(y==mazeWidth-1)) key=true;
    }
    return key;
}
//---------------------------------------------------------------------------

bool TmainForm::edgeBarrier(const int type, const int x, const int y, const bool start)
{
    bool key=false;

    static int counter = 0;
    if(start)
    {
       counter=0;
       setWall(type,x,y);
    }
    if(wall(type,x,y))
    {
        if(edgeWall(type,x,y)&&(++counter>1))
            key=true;
        markWall(type,x,y);
        if(!key)
        {
            if(type==0)
            {
                if(y>0)
                {
                    if(!key)
                    {
                        if(edgeBarrier(0,x,y-1)||
                           edgeBarrier(1,y-1,x)||
                           edgeBarrier(1,y-1,x+1)) key=true;
                    }
                }
                if(y<mazeHeight-1)
                {
                    if(!key)
                    {
                        if(edgeBarrier(0,x,y+1)||
                           edgeBarrier(1,y,x)||
                           edgeBarrier(1,y,x+1)) key=true;
                    }
                }
            }
            else
            {
                if(y>0)
                {
                    if(!key)
                    {
                        if(edgeBarrier(1,x,y-1)||
                           edgeBarrier(0,y-1,x)||
                           edgeBarrier(0,y-1,x+1)) key=true;
                    }
                }
                if(y<mazeWidth-1)
                {
                    if(!key)
                    {
                        if(edgeBarrier(1,x,y+1)||
                           edgeBarrier(0,y,x)||
                           edgeBarrier(0,y,x+1)) key=true;
                    }
                }
            }
        }
    }
    if(start)
    {
        unmarkWalls();
        unsetWall(type,x,y);
    }
    return key;
}
//---------------------------------------------------------------------------

bool TmainForm::loopBarrier(const int type, const int x, const int y,const int step=0,
                            const bool start)
{
    bool key=false;

    if((checkMark(type,x,y)==3)&&(step>4))
        key=true;
    if(start)
    {
        setWall(type,x,y);
        //Исключения из правила поиска циклов

        if((type==0)&&(y>0)&&(y<mazeHeight-1))
        {
            if(x>0)
            {
                if(wall(1,y-1,x)&&wall(1,y,x)&&wall(0,x-1,y)) key = true;
            }
            if(x<mazeWidth-1)
            {
                if(wall(1,y-1,x+1)&&wall(1,y,x+1)&&wall(0,x+1,y)) key = true;
            }
        }
        if((type==1)&&(y>0)&&(y<mazeWidth-1))
        {
            if(x>0)
            {
                if(wall(0,y-1,x)&&wall(0,y,x)&&wall(1,x-1,y)) key = true;
            }
            if(x<mazeHeight-1)
            {
                if(wall(0,y-1,x+1)&&wall(0,y,x+1)&&wall(1,x+1,y)) key = true;
            }
        }

    }

    if(!key&&wall(type,x,y))
    {
        if(start) markWall(type,x,y,3);
        else markWall(type,x,y);
        if(!key)
        {
            if(type==0)
            {
                if(y>0)
                {
                    if(!key)
                    {
                        if(loopBarrier(0,x,y-1,step+1)||
                           loopBarrier(1,y-1,x,step+1)||
                           loopBarrier(1,y-1,x+1,step+1)) key=true;
                    }
                }
                if(y<mazeHeight-1)
                {
                    if(!key)
                    {
                        if(loopBarrier(0,x,y+1,step+1)||
                           loopBarrier(1,y,x,step+1)||
                           loopBarrier(1,y,x+1,step+1)) key=true;
                    }
                }
            }
            else
            {
                if(y>0)
                {
                    if(!key)
                    {
                        if(loopBarrier(1,x,y-1,step+1)||
                           loopBarrier(0,y-1,x,step+1)||
                           loopBarrier(0,y-1,x+1,step+1)) key=true;
                    }
                }
                if(y<mazeWidth-1)
                {
                    if(!key)
                    {
                        if(loopBarrier(1,x,y+1,step+1)||
                           loopBarrier(0,y,x,step+1)||
                           loopBarrier(0,y,x+1,step+1)) key=true;
                    }
                }
            }
        }
    }
    if(start)
    {
        unmarkWalls();
        unsetWall(type,x,y);
    }

    return key;

}
//---------------------------------------------------------------------------

void TmainForm::markWall(const int type, const int x, const int y,
                         const int marktype)
{
    if(type==0) verticalWalls[x][y]=marktype;
    else horizontalWalls[x][y]=marktype;
}
//---------------------------------------------------------------------------

void TmainForm::unmarkWalls()
{
    for(int i=0; i<mazeWidth-1; i++)
        for(int j=0; j<mazeHeight; j++)
        {
            if(checkMark(0,i,j)>=2)
            {
                markWall(0,i,j,1);
            }
        }
    for(int i=0; i<mazeHeight-1; i++)
        for(int j=0; j<mazeWidth; j++)
        {
            if(checkMark(1,i,j)>=2)
            {
                markWall(1,i,j,1);
            }
        }
}
//---------------------------------------------------------------------------

bool TmainForm::wall(const int type, const int x, const int y)
{
    return (((type==0)&&(verticalWalls[x][y]==1))||
           ((type==1)&&(horizontalWalls[x][y]==1)));
}
//---------------------------------------------------------------------------

int TmainForm::checkMark(const int type, const int x, const int y)
{
    if(type==0) return verticalWalls[x][y];
    return horizontalWalls[x][y];
}
//---------------------------------------------------------------------------

void TmainForm::drawWalls()
{
    this->mazeFrame->Image->Canvas->FillRect(TRect(0,0,this->mazeFrame->Image->Width,
                                                       this->mazeFrame->Image->Height));

    this->mazeFrame->Image->Canvas->Pen->Width=pictureWall;
    this->mazeFrame->Image->Canvas->Pen->Color=clBlack;
    for(int i=0; i<mazeWidth-1; i++)
        for(int j=0; j<mazeHeight; j++)
        {

            if(verticalWalls[i][j]==1)
            {
                this->mazeFrame->Image->Canvas->MoveTo(pictureSize*(i+1)+pictureSpace*i+2,
                                                       pictureSize*j+pictureSpace*j);
                this->mazeFrame->Image->Canvas->LineTo(pictureSize*(i+1)+pictureSpace*i+2,
                                                       pictureSize*(j+1)+pictureSpace*(j+1));
            }
        }
    for(int i=0; i<mazeHeight-1; i++)
        for(int j=0; j<mazeWidth; j++)
        {
            if(horizontalWalls[i][j]==1)
            {
                this->mazeFrame->Image->Canvas->MoveTo(pictureSize*j+pictureSpace*j,
                                                       pictureSize*(i+1)+pictureSpace*i+2);
                this->mazeFrame->Image->Canvas->LineTo(pictureSize*(j+1)+pictureSpace*(j+1),
                                                       pictureSize*(i+1)+pictureSpace*i+2);
            }
        }
}
//---------------------------------------------------------------------------

void TmainForm::setWall(const int type, const int x, const int y)
{
     if(type==1) horizontalWalls[x][y]=1;
     else verticalWalls[x][y]=1;
}
//---------------------------------------------------------------------------

void TmainForm::unsetWall(const int type, const int x, const int y)
{
    if(type==1) horizontalWalls[x][y]=0;
    else verticalWalls[x][y]=0;
}
//---------------------------------------------------------------------------

void TmainForm::ShowAll()
{
    AnsiString message = "";
    for(int i=0; i<mazeWidth-1; i++)
        for(int j=0; j<mazeHeight; j++)
        {
            message += "verticalWalls[" + IntToStr(i) + "][" + IntToStr(j) +
                       "]=" + IntToStr(verticalWalls[i][j])+"\n";
        }
    for(int i=0; i<mazeHeight-1; i++)
        for(int j=0; j<mazeWidth; j++)
        {
            message += "horizontalWalls[" + IntToStr(i) + "][" + IntToStr(j) +
                       "]=" + IntToStr(horizontalWalls[i][j])+"\n";
        }

    ShowMessage(message);

}
//---------------------------------------------------------------------------

int TmainForm::look(const int a, const int b, const int x, const int y)
{
    int answer = -1;
    if(a==x)
    {
        if(((b<y)&&(b>=0)&&(horizontalWalls[b][x]==0))||
           ((b>y)&&(b<mazeHeight)&&(horizontalWalls[y][x]==0)))
        {
           answer = positions(a,b);
        }
    }
    else //if(b==y)
    {
        if(((a<x)&&(a>=0)&&(verticalWalls[a][y]==0))||
           ((a>x)&&(a<mazeWidth)&&(verticalWalls[x][y]==0)))
        {
           answer = positions(a,b);
        }
    }
    return answer;
}
//---------------------------------------------------------------------------
                                                                                  //не отлажено
void TmainForm::gotoXY(const int x, const int y, TImage * pImage)
{
    pImage->Left=x*(pictureSize+pictureSpace)+1;
    pImage->Top=y*(pictureSize+pictureSpace)+1;
}
//---------------------------------------------------------------------------

TImage * TmainForm::standartImage()
{
    TImage * image = new TImage(mainForm->mazeFrame->mazePanel);
    image->Parent = mainForm->mazeFrame->mazePanel;
    image->Picture->Assign(bmCrimeUp);
    image->Hide();
    image->Height=30;
    image->Width=30;
    image->Transparent=true;
    return image;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N9Click(TObject *Sender)
{
    say("Объекты распределяются случайным образом");
    personRandom();
}
//---------------------------------------------------------------------------

void TmainForm::personRandom()
{
    for(int i=0; i<queue.size(); i++)
        delete queue[i];
    queue.clear();

    bMaps bCop   = { bmCopUp, bmCopRight, bmCopDown, bmCopLeft },
          bCrime = { bmCrimeUp, bmCrimeRight, bmCrimeDown, bmCrimeLeft };

    for(int i=0; i<numberCop; i++)
    {
        Cop * newCop = new Cop(bCop,standartImage());
        queue.push_back(newCop);
    }
    for(int i=0; i<numberCrime; i++)
    {
        Crime * newCrime = new Crime(bCrime,standartImage());
        queue.push_back(newCrime);
    }

    intMatrix line;
    vint two;
    for(int i=0; i<mazeWidth; i++)
    {
        two.clear();
        two.push_back(i);
        two.push_back(0);
        line.push_back(two);

        two.clear();
        two.push_back(i);
        two.push_back(mazeHeight-1);
        line.push_back(two);
    }
    for(int j=1; j<mazeHeight-1; j++)
    {
        two.clear();
        two.push_back(0);
        two.push_back(j);
        line.push_back(two);

        two.clear();
        two.push_back(mazeWidth-1);
        two.push_back(j);
        line.push_back(two);
    }

    vint *temp;
    for(int i=0; i<numberCop; i++)
    {
        temp=&line[random(line.size())];
        queue[i]->gotoXY((*temp)[0],(*temp)[1]);
        queue[i]->turn(random(4));
        queue[i]->freeRotation();
        line.erase(temp);
    }

    line.clear();
    for(int i=1; i<mazeWidth-1; i++)
        for(int j=1; j<mazeHeight-1; j++)
            {
                two.clear();
                two.push_back(i);
                two.push_back(j);
                line.push_back(two);
            }

    for(int i=0; i<numberCrime; i++)
    {
        temp=&line[random(line.size())];
        queue[i+numberCop]->gotoXY((*temp)[0],(*temp)[1]);
        queue[i+numberCop]->turn(random(4));
        queue[i+numberCop]->freeRotation();
        line.erase(temp);
    }
}
//---------------------------------------------------------------------------

void TmainForm::saveToFile(const AnsiString fileName)
{
    using namespace std;
    ofstream out(fileName.c_str());
    if(N13->Checked) out << "1" << endl;
    else out << "0" << endl;
    if(N10->Checked) out << "1" << endl;
    else out << "0" << endl;
    if(N11->Checked) out << "1" << endl;
    else out << "0" << endl;
    out << mazeWidth << endl << mazeHeight << endl
        << numberCop << endl << numberCrime << endl
        << mazeThickness << endl;
    for(int i=0; i<queue.size(); i++)
    out << queue[i]->getX() << endl << queue[i]->getY() << endl
        << queue[i]->look() << endl;

     for(int i=0; i<mazeWidth-1; i++)
        for(int j=0; j<mazeHeight; j++)
        {
            out << verticalWalls[i][j] << endl;
        }
    for(int i=0; i<mazeHeight-1; i++)
        for(int j=0; j<mazeWidth; j++)
        {
            out << horizontalWalls[i][j] << endl;
        }
    out.close();
    say("Ситуация сохранена в файле: "+strOptionsFile);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N12Click(TObject *Sender)
{
    saveToFile(strOptionsFile);
}
//---------------------------------------------------------------------------

void TmainForm::loadFromFile(const AnsiString fileName)
{
    using namespace std;
    ifstream in(fileName.c_str());
    string temp;
    in >> temp;
    if(temp=="1")
    {
        N13->Checked=true;
        in >> temp;
        if(temp=="1") N10->Checked=true;
        in >> temp;
        if(temp=="1") N11->Checked=true;
        in >> mazeWidth;
        in >> mazeHeight;
        in >> numberCop;
        in >> numberCrime;
        in >> mazeThickness;
        mainForm->setMazeSize(mazeWidth,mazeHeight);
        mainForm->setNumbers(numberCop,numberCrime);
        mainForm->setThickness(mazeThickness);

        bMaps bCop   = { bmCopUp, bmCopRight, bmCopDown, bmCopLeft },
        bCrime = { bmCrimeUp, bmCrimeRight, bmCrimeDown, bmCrimeLeft };

        int tx,ty;
        for(int i=0; i<numberCop; i++)
        {
            Cop * newCop = new Cop(bCop,standartImage());
            queue.push_back(newCop);
            in >> tx;
            in >> ty;
            queue[queue.size()-1]->gotoXY(tx,ty);
            in >> tx;
            queue[queue.size()-1]->turn(tx);
            queue[queue.size()-1]->freeRotation();
        }
        for(int i=0; i<numberCrime; i++)
        {
            Crime * newCrime = new Crime(bCrime,standartImage());
            queue.push_back(newCrime);
            in >> tx;
            in >> ty;
            queue[queue.size()-1]->gotoXY(tx,ty);
            in >> tx;
            queue[queue.size()-1]->turn(tx);
            queue[queue.size()-1]->freeRotation();
        }

        vint vtemp;
        verticalWalls.clear();
        for(int i=0; i<mazeWidth-1; i++)
        {
            vtemp.clear();
            for(int j=0; j<mazeHeight; j++)
            {
                in >> tx;
                vtemp.push_back(tx);
            }
            verticalWalls.push_back(vtemp);
        }
        horizontalWalls.clear();
        for(int i=0; i<mazeHeight-1; i++)
        {
            vtemp.clear();
            for(int j=0; j<mazeWidth; j++)
            {
                in >> tx;
                vtemp.push_back(tx);
            }
            horizontalWalls.push_back(vtemp);
        }
        drawWalls();
    }
    in.close();
    say("Ситуация полностью загружена из файла");
    for(int i=0; i<numberCrime; i++)
    {
        qAvaible.push_back(true);
    }
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::FormCreate(TObject *Sender)
{
    msgSimpr=RegisterWindowMessage(simprUserMessage.c_str());
    loadFromFile(strOptionsFile);
}
//---------------------------------------------------------------------------


void TmainForm::say(const AnsiString line)
{
    memoLog->Lines->Add(line);
    memoLog->Lines->Add("");
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::N11Click(TObject *Sender)
{
    if(N11->Checked)
        say("Автосохранение включено (только при нажатии exit)");
    else
        say("Автосохрание отключено");
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::N13Click(TObject *Sender)
{
    if(N13->Checked)
        say("Автозагрузка ситуации включена");
    else
        say("Автозагрузка ситуации отключена");
}
//---------------------------------------------------------------------------

int TmainForm::getMazeHeight()
{
    return mazeHeight;
}
//---------------------------------------------------------------------------

int TmainForm::getMazeWidth()
{
    return mazeWidth;
}
//---------------------------------------------------------------------------

bool TmainForm::ifCop(const int x,const int y)
{
    bool key = false;
    int i=0;
    while(!key&&(i<numberCop))
    {
        if((queue[i]->getX()==x)&&(queue[i]->getY()==y)) key=true;
        i++;
    }
    return key;
}
//---------------------------------------------------------------------------

int TmainForm::positions(const int x, const int y)
{
    for(int i=0;i<numberCop;i++)
    {
        if((queue[i]->getX()==x)&&(queue[i]->getY()==y)) return 1;
    }
    for(int i=0;i<numberCrime;i++)
    {
        if((queue[i+numberCop]->getX()==x)&&(queue[i+numberCop]->getY()==y)&&qAvaible[i]) return 2;
    }
    return 0;
}
//---------------------------------------------------------------------------



