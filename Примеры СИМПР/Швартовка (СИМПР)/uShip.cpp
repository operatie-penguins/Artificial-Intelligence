//---------------------------------------------------------------------------

#pragma hdrstop
#include <vcl.h>
#include "uShip.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

//�����������
Ship :: Ship(int int_NewStatus, int int_NewLoad, int int_NewMission, int int_NewDirection, int int_NewCordX, int int_NewCordY, TWinControl* AOwner) : TImage(AOwner)
{
  this->int_Status = int_NewStatus;
  this->int_Load = int_NewLoad;
  this->int_Mission = int_NewMission;
  this->int_Direction = int_NewDirection;
  this->Left = int_NewCordX;
  this->Top = int_NewCordY;
  this->Width = 30;
  this->Height = 30;
  this->Parent = AOwner;
  this->Stretch = true;
  this->tmr_Time = new TTimer(this);
  this->tmr_Time->Enabled = false;
  this->tmr_Time->OnTimer = this->tmr_TimeTimer;
  this->flgTmr = false;
  this->flgStep = false;
  this->flgDock = false;

  if(this->int_Mission == 0)
  {
    this->Picture->LoadFromFile("ArPos3.bmp");
  }
  else if(this->int_Mission == 1)
  {
    this->Picture->LoadFromFile("ArPosRed3.bmp");
  }
}

//---------------------------------------------------------------------------

//������� "���"
int Ship :: __ShpStep(int int_StepX, int int_StepY)
{
  try
  {
    if(this->int_Mission == 0)
    {
      if(int_StepX < 0)
      {
        //�������� �����
        if(int_StepY == 0)
        {
          this->Picture->LoadFromFile("ArPos1.bmp");
        }
        //�������� ����� � �����
        else if(int_StepY < 0)
        {
          this->Picture->LoadFromFile("ArPos2.bmp");
        }
        //�������� ����� � ����
        else if(int_StepY > 0)
        {
          this->Picture->LoadFromFile("ArPos8.bmp");
        }
      }
      else if(int_StepX == 0)
      {
        //�������� �����
        if(int_StepY < 0)
        {
          this->Picture->LoadFromFile("ArPos3.bmp");
        }
        //�������� ����
        else if(int_StepY > 0)
        {
          this->Picture->LoadFromFile("ArPos7.bmp");
        }
      }
      else if(int_StepX > 0)
      {
        //�������� ������
        if(int_StepY == 0)
        {
          this->Picture->LoadFromFile("ArPos5.bmp");
        }
        //�������� ������ � �����
        else if(int_StepY < 0)
        {
          this->Picture->LoadFromFile("ArPos4.bmp");
        }
        //�������� ������ � ����
        else if(int_StepY > 0)
        {
          this->Picture->LoadFromFile("ArPos6.bmp");
        }
      }
    }
    else if(this->int_Mission == 1)
    {
      if(int_StepX < 0)
      {
        //�������� �����
        if(int_StepY == 0)
        {
          this->Picture->LoadFromFile("ArPosRed1.bmp");
        }
        //�������� ����� � �����
        else if(int_StepY < 0)
        {
          this->Picture->LoadFromFile("ArPosRed2.bmp");
        }
        //�������� ����� � ����
        else if(int_StepY > 0)
        {
          this->Picture->LoadFromFile("ArPosRed8.bmp");
        }
      }
      else if(int_StepX == 0)
      {
        //�������� �����
        if(int_StepY < 0)
        {
          this->Picture->LoadFromFile("ArPosRed3.bmp");
        }
        //�������� ����
        else if(int_StepY > 0)
        {
          this->Picture->LoadFromFile("ArPosRed7.bmp");
        }
      }
      else if(int_StepX > 0)
      {
        //�������� ������
        if(int_StepY == 0)
        {
          this->Picture->LoadFromFile("ArPosRed5.bmp");
        }
        //�������� ������ � �����
        else if(int_StepY < 0)
        {
          this->Picture->LoadFromFile("ArPosRed4.bmp");
        }
        //�������� ������ � ����
        else if(int_StepY > 0)
        {
          this->Picture->LoadFromFile("ArPosRed6.bmp");
        }
      }
    }
    this->Left += int_StepX;
    this->Top += int_StepY;
  }
  catch(...)
  {
    return 1;
  }
//  this->flgStep = true;
  return 0;
}

//---------------------------------------------------------------------------

//������� "�������� �� �����"
int Ship :: __ShpMove(int int_StepX, int int_StepY)
{
  if(this->int_Status != 0)
    return 1;

  switch(int_Direction)
  {
    case 0:
    {
      this->__ShpStep(0,int_StepY);
      break;
    }
    case 1:
    {
      this->__ShpStep(0,-int_StepY);
      break;
    }
    case 2:
    {
      this->__ShpStep(int_StepX,0);
      break;
    }
    case 3:
    {
      this->__ShpStep(-int_StepX,0);
      break;
    }
  }

  return 0;
}

//---------------------------------------------------------------------------

//������� "���������"
int Ship :: __ShpDock(int int_StepX, int int_StepY, int int_DestinationX, int int_DestinationY, int int_DestinationW, int int_DestinationH)
{
  int int_x1 = int_DestinationX - 30;
  int int_y1 = int_DestinationY - 30;
  int int_x2 = int_DestinationX + int_DestinationW;
  int int_y2 = int_DestinationY + int_DestinationH;
  int int_DockX;
  int int_DockY;

  if(this->int_Status != 1)
    return 1;

  //������ ��������
  if(this->GetX() >= int_x2 && this->GetY() < int_y2)
  {
    int_DockX = int_x2;
    int_DockY = int_DestinationY + (int_DestinationH - this->Height)/2;
    //x > X, y < Y
    if(this->GetX() > int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(-int_StepX, int_StepY);
      return 0;
    }
    //x = X, y < Y
    else if(this->GetX() == int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(0, int_StepY);
      return 0;
    }
    //x > X, y = Y
    else if(this->GetX() > int_DockX && this->GetY() == int_DockY)
    {
      this->__ShpStep(-int_StepX, 0);
      return 0;
    }
    //x > X, y > Y
    else if(this->GetX() > int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(-int_StepX, -int_StepY);
      return 0;
    }
    //x = X, y > Y
    else if(this->GetX() == int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(0, -int_StepY);
      return 0;
    }
    //x = X, y = Y
    else if(this->GetX() == int_DockX && this->GetY() == int_DockY)
    {
      this->flgDock = true;
      this->int_Direction = 0;

      if(this->int_Mission == 0)
        this->Picture->LoadFromFile("ArPos7.bmp");
      else if(this->int_Mission == 1)
        this->Picture->LoadFromFile("ArPosRed7.bmp");

      return 1;
    }
  }
  //������ ��������
  else if(this->GetX() < int_x2 && this->GetY() <= int_y1)
  {
    int_DockX = int_DestinationX + (int_DestinationW - this->Width)/2;
    int_DockY = int_y1;
    //x < X, y < Y
    if(this->GetX() < int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(int_StepX, int_StepY);
      return 0;
    }
    //x = X, y < Y
    else if(this->GetX() == int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(0, int_StepY);
      return 0;
    }
    //x < X, y = Y
    else if(this->GetX() < int_DockX && this->GetY() == int_DockY)
    {
      this->__ShpStep(int_StepX, 0);
      return 0;
    }
    //x > X, y < Y
    else if(this->GetX() > int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(-int_StepX, int_StepY);
      return 0;
    }
    //x > X, y = Y
    else if(this->GetX() > int_DockX && this->GetY() == int_DockY)
    {
      this->__ShpStep(-int_StepX, 0);
      return 0;
    }
    //x = X, y = Y
    else if(this->GetX() == int_DockX && this->GetY() == int_DockY)
    {
      this->flgDock = true;
      this->int_Direction = 2;

      if(this->int_Mission == 0)
        this->Picture->LoadFromFile("ArPos5.bmp");
      else if(this->int_Mission == 1)
        this->Picture->LoadFromFile("ArPosRed5.bmp");

      return 1;
    }
  }
  //������ ��������
  else if(this->GetX() <= int_x1 && this->GetY() > int_y1)
  {
    int_DockX = int_x1;
    int_DockY = int_DestinationY + (int_DestinationH - this->Height)/2;
    //x < X, y > y
    if(this->GetX() < int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(int_StepX, -int_StepY);
      return 0;
    }
    //x = X, y > Y
    else if(this->GetX() == int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(0, -int_StepY);
      return 0;
    }
    //x < X, y = Y
    else if(this->GetX() < int_DockX && this->GetY() == int_DockY)
    {
      this->__ShpStep(int_StepX, 0);
      return 0;
    }
    //x < X, y < Y
    else if(this->GetX() < int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(int_StepX, int_StepY);
      return 0;
    }
    //x = X, y < Y
    else if(this->GetX() == int_DockX && this->GetY() < int_DockY)
    {
      this->__ShpStep(0, int_StepY);
      return 0;
    }
    //x = X, y = Y
    else if(this->GetX() == int_DockX && this->GetY() == int_DockY)
    {
      this->flgDock = true;
      this->int_Direction = 1;

      if(this->int_Mission == 0)
        this->Picture->LoadFromFile("ArPos3.bmp");
      else if(this->int_Mission == 1)
        this->Picture->LoadFromFile("ArPosRed3.bmp");

      return 1;
    }
  }
  //��������� ��������
  else if(this->GetX() > int_x1 && this->GetY() >= int_y2)
  {
    int_DockX = int_DestinationX + (int_DestinationW - this->Width)/2;
    int_DockY = int_y2;
    //x > X, y > Y
    if(this->GetX() > int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(-int_StepX, -int_StepY);
      return 0;
    }
    //x = X, y > Y
    else if(this->GetX() == int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(0, -int_StepY);
      return 0;
    }
    //x > X, y = Y
    else if(this->GetX() > int_DockX && this->GetY() == int_DockY)
    {
      this->__ShpStep(-int_StepX, 0);
      return 0;
    }
    //x < X, y > Y
    else if(this->GetX() < int_DockX && this->GetY() > int_DockY)
    {
      this->__ShpStep(int_StepX, -int_StepY);
      return 0;
    }
    //x < X, y = Y
    else if(this->GetX() < int_DockX && this->GetY() == int_DockY)
    {
      this->__ShpStep(int_StepY, 0);
      return 0;
    }
    //x = X, y = Y
    else if(this->GetX() == int_DockX && this->GetY() == int_DockY)
    {
      this->flgDock = true;
      this->int_Direction = 3;

      if(this->int_Mission == 0)
        this->Picture->LoadFromFile("ArPos1.bmp");
      else if(this->int_Mission == 1)
        this->Picture->LoadFromFile("ArPosRed1.bmp");

      return 1;
    }
  }

  return 0;
}

//---------------------------------------------------------------------------

//������� "���������"
int Ship :: __ShpUnload(int int_Time)
{
  if(this->int_Status != 2)
    return 1;

  if(!tmr_Time->Enabled && !flgTmr)
  {
    this->tmr_Time->Interval = int_Time;
    this->tmr_Time->Enabled = true;
    return 1;
  }
  else if(!tmr_Time->Enabled && flgTmr)
  {
    this->SetStatus(0);
    flgTmr = false;
    return 0;
  }
  else if(tmr_Time->Enabled)
  {
    return 1;
  }

  return 1;
}

//---------------------------------------------------------------------------

//������� ���������� ��������� �������� �������
int Ship :: GetStatus()
{
  return this->int_Status;
}

//---------------------------------------------------------------------------

//�������������� ��������� ��������� �������� �������
int Ship :: SetStatus(int int_NewStatus)
{
  try
  {
    this->int_Status = int_NewStatus;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//������� ���������� ��������� ����� �������
int Ship :: GetLoad()
{
  return this->int_Load;
}

//---------------------------------------------------------------------------

//�������������� ��������� ��������� ����� �������
int Ship :: SetLoad(int int_NewLoad)
{
  try
  {
    this->int_Load = int_NewLoad;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//������� ���������� ���������� �������
int Ship :: GetMission()
{
  return this->int_Mission;
}

//---------------------------------------------------------------------------

//������� ���������� ����������� �������� �������
int Ship :: GetDirection()
{
  return this->int_Direction;
}

//---------------------------------------------------------------------------

//�������������� ��������� ����������� �������� �������
int Ship :: SetDirection(int int_NewDirectin)
{
  try
  {
    this->int_Direction = int_NewDirectin;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//�������������� ��������� ������������� �������
int Ship :: SetOwner(TWinControl* AOwner)
{ 
  try
  {
    this->Parent = AOwner;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//������� ���������� ���������� X
int Ship :: GetX()
{
  return Left;
}

//---------------------------------------------------------------------------

//������� ���������� ���������� Y
int Ship :: GetY()
{
  return Top;
}

//---------------------------------------------------------------------------

//������� �������������� ���������� X
int Ship :: SetX(int int_NewX)
{
  try
  {
    this->Left = int_NewX;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//������� �������������� ���������� Y
int Ship :: SetY(int int_NewY)
{
  try
  {
    this->Top = int_NewY;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//���������� ������� ������
void __fastcall Ship :: tmr_TimeTimer(TObject *Sender)
{
  this->tmr_Time->Enabled = false;
  this->flgTmr = true;
}

//---------------------------------------------------------------------------

//������� ���������� ���� ����
bool Ship :: GetFlgStep()
{
  return this->flgStep;
}

//---------------------------------------------------------------------------

//�������������� ��������� ����� ����
bool Ship :: SetFlgStep(bool NewFlgStep)
{
  try
  {
    this->flgStep = NewFlgStep;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//������� ���������� ���� ����
bool Ship :: GetFlgDock()
{
  return this->flgDock;
}

//---------------------------------------------------------------------------

//�������������� ��������� ����� ����
bool Ship :: SetFlgDock(bool NewFlgDock)
{
  try
  {
    this->flgDock = NewFlgDock;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//������� ���������� ���� �������
bool Ship :: GetFlgTmr()
{
  return this->flgTmr;
}

//---------------------------------------------------------------------------

//�������������� ��������� ����� �������
bool Ship :: SetFlgTmr(bool NewFlgTmr)
{
  try
  {
    this->flgTmr = NewFlgTmr;
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}
