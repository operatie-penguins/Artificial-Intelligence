//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#include "uMain.h"
#include "uAbout.h"
#include "uInfo.h"
#include "uShip.h"

//---------------------------------------------------------------------------

//Сообщение для обмена с СИМПР
#define USERMESSAGE "DockMessage"

#define tmrPasUnload 500
#define tmrCargoUnload 2000
//Константа для замедления времени (удобнго при отладке программы)
#define int_timeSleep 0
#define first 0
#define last 3

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMain *frmMain;
Ship *ShipMas[10];
UINT MsgSIMPR;
FILE *input;

int  bl_PasDock1 = 1,
     bl_PasDock2 = 1,
     bl_CargoDock1 = 1,
     bl_CargoDock2 = 1,
     flgOnOff = 1,
     flgPg = 0;

int int_NewMission,
    int_NewDirection,
    int_X,
    int_Y,
    int_i = first,
    int_ID = first;

//---------------------------------------------------------------------------

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
  ShipMas[0] = new Ship(0, 1, 1, 2, 77, 63, frmMain);
  ShipMas[0]->__ShpMove(1, 1);
  ShipMas[1] = new Ship(0, 1, 0, 3, 277, 63, frmMain);
  ShipMas[1]->__ShpMove(1, 1);
  ShipMas[2] = new Ship(0, 1, 0, 2, 77, 310, frmMain);
  ShipMas[2]->__ShpMove(1, 1);
  ShipMas[3] = new Ship(0, 1, 1, 3, 277, 310, frmMain);
  ShipMas[3]->__ShpMove(1, 1);

  MsgSIMPR = RegisterWindowMessage(USERMESSAGE);
  TfrmInfo *frmInfo = new TfrmInfo(frmMain);

  //Проверяем существует ли такой фаил
  if ((input = fopen("log", "w")) == NULL)
    MessageBox(NULL, "Невозможно создать лог-файл", "Ошибка", 0);	  
  
}

//---------------------------------------------------------------------------
//Создание корабля
int mkShp()
{
  int_NewDirection = RandomRange(0,3);

  if(int_ID == 0)
  {
    int_X = 77;
    int_Y = 63;
  }
  else if(int_ID == 1)
  {
    int_X = 277;
    int_Y = 63;
  }
  else if(int_ID == 2)
  {
    int_X = 77;
    int_Y = 310;
  }
  else if(int_ID == 3)
  {
    int_X = 277;
    int_Y = 310;
  }

  int_NewMission = RandomRange(0,2);

  ShipMas[int_ID]->~Ship();
  ShipMas[int_ID] = new Ship(0, 1, int_NewMission, int_NewDirection, int_X, int_Y, frmMain);
  ShipMas[int_ID]->__ShpMove(1,1);

  return 0;
}

//---------------------------------------------------------------------------

int FreeDock()
{
  try
  {
    if(ShipMas[int_ID]->GetMission() == 0)
    {
      //Зоны 2 и 3. Переход в состояние разгрузка для пассажирского корабля.
      if((ShipMas[int_ID]->GetX() < 216) && (ShipMas[int_ID]->GetY() <= 155))
      {
        bl_PasDock1 = 0;
        fprintf(input, " PasDock1");
      }
      //Зоны 6 и 7. Переход в состояние разгрузка для пассажирского корабля.
      else if((ShipMas[int_ID]->GetX() > 155) && (ShipMas[int_ID]->GetY() >= 245))
      {
        bl_PasDock2 = 0;
        fprintf(input, " PasDock2");
      }
    }
    else if(ShipMas[int_ID]->GetMission() == 1)
    {
      //Зоны 4 и 5. Переход в состояние разгрузка для грузового корабля.
      if((ShipMas[int_ID]->GetX() <= 155) && (ShipMas[int_ID]->GetY() > 155))
      {
        bl_CargoDock1 = 0;
        fprintf(input, " CargoDock1");
      }
      //Зоны 1 и 8. Переход в состояние разгрузка для грузового корабля.
      else if((ShipMas[int_ID]->GetX() >= 216) && (ShipMas[int_ID]->GetY() < 245))
      {
        bl_CargoDock2 = 0;
        fprintf(input, " CargoDock2");
      }
    }
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------------

//Управление кораблями
void __fastcall TfrmMain::WndProc(Messages::TMessage &Message)
{
  if(Message.Msg == MsgSIMPR)
  {
    //Sleep(int_timeSleep);
    //Условия
    if(Message.WParamHi == 0)
      //Таблицы
      switch(Message.WParamLo)
      {
        //Первая tabl (выключатель)
        case 1:
        {
          if(flgPg != 0)
          {
            fprintf(input, "\n");
            fprintf(input, "----------------------------------------------------------------------------------------------------\n");
            fprintf(input, "\n");
          }
          fprintf(input, "X = %d, Y = %d\n", ShipMas[int_ID]->GetX(), ShipMas[int_ID]->GetY());
          flgPg++;
          fprintf(input, "condition tabl 1");
          //Номер условия
          switch(Message.LParam)
          {
            //Условие 1
            case 1:
            {
	      fprintf(input, " OnOff -");
              if(flgOnOff == 1)
              {
		fprintf(input, " 1");
                Message.Result = true;
              }
              else if(flgOnOff == 0)
              {
		fprintf(input, " 0");
                Message.Result = false;
              }
	      fprintf(input, "\n");
	      return;
              break;
            }
          }
        }
        //Вторая tabl (диспетчер)
        case 2:
        {
	  fprintf(input, "condition tabl 2");
          //Номер условия
          switch(Message.LParam)
          {
	    //Условие 1
	    case 1:
            {
              fprintf(input, " %d Last -", int_ID);
	      if(int_i == last)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 0;
                frmInfo->RadioButton1->Checked = true;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton1->Checked = false;
              }
              fprintf(input, "\n");
              int_ID = int_i;
              frmInfo->lbNum->Caption = int_ID + 1;
              Sleep(int_timeSleep);
	      return;
              break;
            }
            //Условие 2
	    case 2:
	    {
              fprintf(input, " %d MissionPas -", int_ID);
	      if(ShipMas[int_ID]->GetMission() == 0)
              {
                fprintf(input, " 1");
	        Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 1;
                frmInfo->RadioButton2->Checked = true;
              }
	      else if(ShipMas[int_ID]->GetMission() == 1)
              {
                fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton2->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

	    //Условие 3
	    case 3:
            {
              fprintf(input, " %d Load -", int_ID);
              if(ShipMas[int_ID]->GetLoad() == 1)
              {
                fprintf(input, " 1");
	        Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 2;
                frmInfo->RadioButton3->Checked = true;
              }
	      else if (ShipMas[int_ID]->GetLoad() == 0)
              {
                fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton3->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

	    //Условие 4
	    case 4:
	    {
              fprintf(input, " %d Move -", int_ID);
	      if(ShipMas[int_ID]->GetStatus() == 0)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 3;
                frmInfo->RadioButton4->Checked = true;
              }
              else if(ShipMas[int_ID]->GetStatus() != 0)
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton4->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

	    //Условие 5
	    case 5:
	    {
              fprintf(input, " %d Dock -", int_ID);
	      if(ShipMas[int_ID]->GetStatus() == 1)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 4;
                frmInfo->RadioButton5->Checked = true;
              }
	      else if(ShipMas[int_ID]->GetStatus() != 1)
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton5->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }

            //Условие 6
            case 6:
            {
              fprintf(input, " %d Unload -", int_ID);
              if(ShipMas[int_ID]->GetStatus() == 2)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 5;
                frmInfo->RadioButton6->Checked = true;
              }
	      else if(ShipMas[int_ID]->GetStatus() != 2)
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton6->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 7
            case 7:
            {
              fprintf(input, " %d PasDock1 area -", int_ID);
              //Зоны 2 и 3. Переход в состояние разгрузка для пассажирского корабля
	      if(ShipMas[int_ID]->GetX() < 216 && ShipMas[int_ID]->GetY() <= 155)
              {
		fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 6;
                frmInfo->RadioButton7->Checked = true;
              }
	      else
              {
		fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton7->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 8
            case 8:
            {
              fprintf(input, " %d PasDock1 -", int_ID);
              if(bl_PasDock1 == 1)
              {
	        fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 7;
                frmInfo->RadioButton8->Checked = true;
              }
	      else if(bl_PasDock1 == 0)
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton8->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 9
            case 9:
            {
              fprintf(input, " %d PasDock2 area -", int_ID);
              //Зоны 6 и 7. Переход в состояние разгрузка для пассажирского корабля
              if(ShipMas[int_ID]->GetX() > 155 && ShipMas[int_ID]->GetY() >= 245)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 8;
                frmInfo->RadioButton9->Checked = true;
              }
	      else
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton9->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 10
            case 10:
            {
              fprintf(input, " %d PasDock2 -", int_ID);
              if(bl_PasDock2 == 1)
              {
	        fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 9;
                frmInfo->RadioButton10->Checked = true;
              }
	      else if(bl_PasDock2 == 0)
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton10->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 11
            case 11:
            {
              fprintf(input, " %d CargoDock1 area -", int_ID);
              //Зоны 4 и 5. Переход в состояние разгрузка для грузового корабля
              if(ShipMas[int_ID]->GetX() <= 155 && ShipMas[int_ID]->GetY() > 155)
              {
	        fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 10;
                frmInfo->RadioButton11->Checked = true;
              }
	      else
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton11->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 12
            case 12:
            {
              fprintf(input, " %d CargoDock1 -", int_ID);
              if(bl_CargoDock1 == 1)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 11;
                frmInfo->RadioButton12->Checked = true;
              }
              else if(bl_CargoDock1 == 0)
              {
                fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton12->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }

            //Условие 13
            case 13:
            {
              fprintf(input, " %d CargoDock2 area -", int_ID);
              //Зоны 1 и 8. Переход в состояние разгрузка для грузового корабля
	      if(ShipMas[int_ID]->GetX() >= 216 && ShipMas[int_ID]->GetY() < 245)
	      {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 12;
                frmInfo->RadioButton13->Checked = true;
              }
	      else
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton13->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
	      return;
              break;
            }

            //Условие 14
            case 14:
            {
              fprintf(input, " %d CargoDock2 -", int_ID);
              if(bl_CargoDock2 == 1)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 13;
                frmInfo->RadioButton14->Checked = true;
              }
              else if(bl_CargoDock2 == 0)
              {
	        fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton14->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }

            //Условие 15
            case 15:
            {
              fprintf(input, " %d EndScreen area -", int_ID);
              if(ShipMas[int_ID]->GetX() <= -20 || ShipMas[int_ID]->GetX() >= 410|| ShipMas[int_ID]->GetY() <= -20|| ShipMas[int_ID]->GetY() >= 410)
              {
                fprintf(input, " 1");Message.Result = true;
                frmInfo->radgrp1->ItemIndex = 14;
                frmInfo->RadioButton15->Checked = true;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
                frmInfo->RadioButton15->Checked = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }
          }
          break;
        }

        //Третья tabl (движение по курсу)
        case 3:
        {
          fprintf(input, "condition tabl 3");
          //Номер условия
	  switch(Message.LParam)
	  {
	    //Условие 1
	    case 1:
	    {
              fprintf(input, " %d Step -", int_ID);
              if(ShipMas[int_ID]->GetFlgStep())
              {
	        fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp2->ItemIndex = 0;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }
          }
	  break;
        }

        //Четвертая tabl (швартовка)
        case 4:
        {
          fprintf(input, "condition tabl 4");
          //Номер условия
          switch(Message.LParam)
	  {
            //Условие 1
            case 1:
            {
              fprintf(input, " %d Dock -", int_ID);
              if(ShipMas[int_ID]->GetFlgDock())
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp3->ItemIndex = 0;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              break;
              return;
            }

	    //Условие 2
	    case 2:
            {
              fprintf(input, " %d DockStep -", int_ID);
              if(ShipMas[int_ID]->GetFlgStep())
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp3->ItemIndex = 1;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              break;
              return;
            }
          }
          break;
        }

        //Пятая tabl (разгрузка)
        case 5:
        {
          fprintf(input, "condition tabl 5");
          //Номер условия
          switch(Message.LParam)
      	  {
            //Условие 1
	    case 1:
	    {
              fprintf(input, " %d tmrEnbl -", int_ID);
              if(ShipMas[int_ID]->tmr_Time->Enabled)
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp4->ItemIndex = 0;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }
	    //Условие 2
            case 2:
            {
              fprintf(input, " %d flgTmr -", int_ID);
              if(ShipMas[int_ID]->GetFlgTmr())
              {
                fprintf(input, " 1");
                Message.Result = true;
                frmInfo->radgrp4->ItemIndex = 1;
              }
              else
              {
                fprintf(input, " 0");
                Message.Result = false;
              }
              fprintf(input, "\n");
              Sleep(int_timeSleep);
              return;
              break;
            }
          }
          break;
        }
      }

    //Действия
    else if(Message.WParamHi == 1)
      //Номер таблицы
      switch(Message.WParamLo)
      {
        //Первая tabl (выключатель)
        case 1:
        {
	  fprintf(input, "action - tabl 1");
          //Номер действия
          switch(Message.LParam)
          {
            case 0:
            {
              Message.Result = true;
              Close();
              return;
              break;
            }
            //Действие 1
            case 1:
            {
              MessageBox(NULL, "Приплыли!", "Сообщение", 0);
              Message.Result = true;
              return;
              break;
            }
          }
        }
        //Вторая tabl (диспетчер)
        case 2:
        {
          fprintf(input, "action - tabl 2");
          //Номер действия
          switch(Message.LParam)
          {
            case 0:
            {
              Message.Result = true;
              Close();
	      return;
              break;
            }

            //Действие 1
	    case 1:
	    {
	      int_i = first;
              fprintf(input, " %d GoToFirst -", int_ID);
	      fprintf(input, " 1\n");
              Message.Result = true;
	      return;
              break;
            }

	    //Действие 2
	    case 2:
	    {
	      int_i++;
              fprintf(input, " %d GoToNext -", int_ID);
	      fprintf(input, " 1\n");
              Message.Result = true;
	      return;
              break;
            }

	    //Действие 3
	    case 3:
	    {
              fprintf(input, " %d SetStatusDock -", int_ID);
	      ShipMas[int_ID]->SetStatus(1);
	      fprintf(input, " 1\n");
              Message.Result = true;
	      return;
              break;
            }

	    //Действие 4
	    case 4:
	    {
              fprintf(input, " %d DestroyShip -", int_ID);
	      mkShp();
              Repaint();
	      fprintf(input, " 1\n");
              Message.Result = true;
	      return;
              break;
            }

            //Действие 5
	    case 5:
	    {
              fprintf(input, " %d Error -", int_ID);
	      MessageBox(NULL, "Нарушение алгоритма выполнения задачи!", "Ошибка", 0);
	      fprintf(input, " 1\n");
              Message.Result = true;
	      return;
              break;
            }

            //Действие 6
            case 6:
	    {
              fprintf(input, " %d CaprtureDock -", int_ID);
              FreeDock();
	      fprintf(input, " 1\n");
              Message.Result = true;
	      return;
              break;
            }
          }
	  break;
        }

        //Тертья tabl (движение по курсу)
	case 3:
	{
	  fprintf(input, "action - tabl 3");
	  //Номер действия
	  switch(Message.LParam)
	  {
            //Выход
            case 0:
	    {
              Message.Result = true;
	      Close();
	      return;
              break;
            }

            //Шаг
	    case 1:
	    {
              fprintf(input, " %d Step -", int_ID);
              if(ShipMas[int_ID]->GetLoad() == 1)
              {
                //Пассажирский корабль
                if(ShipMas[int_ID]->GetMission() == 0)
                {
                  //Зоны 4 и 8
                  if(ShipMas[int_ID]->GetY() > 95 && ShipMas[int_ID]->GetY() < 245)
                  {
	           if(ShipMas[int_ID]->GetDirection() == 2 || ShipMas[int_ID]->GetDirection() == 3)
	             ShipMas[int_ID]->SetDirection(1);
                  }

                  //Зона 5
                  else if(ShipMas[int_ID]->GetX() <= 155 && ShipMas[int_ID]->GetY() >= 305)
	            ShipMas[int_ID]->SetDirection(2);

		  //Зона 1
		  else if(ShipMas[int_ID]->GetX() >= 276 && ShipMas[int_ID]->GetY() <= 95)
		    ShipMas[int_ID]->SetDirection(3);
                }

		//Грузовой корабль
                else if(ShipMas[int_ID]->GetMission() == 1)
                {
                  //Зоны 2 и 6
		  if(ShipMas[int_ID]->GetX() > 125 && ShipMas[int_ID]->GetX() < 216)
                  {
		    if(ShipMas[int_ID]->GetDirection() == 0 || ShipMas[int_ID]->GetDirection() == 1)
		      ShipMas[int_ID]->SetDirection(2);
                  }

                  //Зона 3
		  else if(ShipMas[int_ID]->GetX() < 125 && ShipMas[int_ID]->GetY() <= 125)
		    ShipMas[int_ID]->SetDirection(0);

		  //Зона 7
		  else if(ShipMas[int_ID]->GetX() > 276 && ShipMas[int_ID]->GetY() >= 305)
		    ShipMas[int_ID]->SetDirection(1);
                }
              }
              ShipMas[int_ID]->__ShpMove(1,1);
	      ShipMas[int_ID]->SetFlgStep(false);
              Repaint();
	      fprintf(input, " 1\n");
              Message.Result = true;
              return;
              break;
            }
          }
          break;
        }

        //Четвертая tabl (швартовка)
        case 4:
        {
	  fprintf(input, "action - tabl 4");
          //Номер действия
	  switch(Message.LParam)
	  {
            case 0:
            {
              Close();
	      return;
              break;
            }
            //Действие 1
            case 1:
            {
              fprintf(input, " %d Dock -", int_ID);
              ShipMas[int_ID]->__ShpDock(1, 1, 185, 155, 31, 90);
              ShipMas[int_ID]->SetFlgStep(false);
              Repaint();
              fprintf(input, " 1\n");
              Message.Result = true;
              break;
            }
            //Действие 2
            case 2:
            {
              fprintf(input, " %d SetStatusUnload -", int_ID);
              ShipMas[int_ID]->SetStatus(2);
              fprintf(input, " 1\n");
              Message.Result = true;
              break;
            }
          }
          break;
        }

	//Пятая tabl (разгрузка)
        case 5:
        {
	   fprintf(input, "action - tabl 5");
          //Номер действия
	  switch(Message.LParam)
	  {
            case 0:
            {
              Close();
	      return;
              break;
            }
            //Действие 1
            case 1:
            {
              fprintf(input, " %d Start&CheckTimer -", int_ID);
              if(ShipMas[int_ID]->GetMission() == 0)
                ShipMas[int_ID]->__ShpUnload(tmrPasUnload);
              else if(ShipMas[int_ID]->GetMission() == 1)
                ShipMas[int_ID]->__ShpUnload(tmrCargoUnload);

              fprintf(input, " 1\n");
              Message.Result = true;
              return;
              break;
            }
            //Действие 2
            case 2:
            {
              fprintf(input, " %d SetStatusMove -", int_ID);
              ShipMas[int_ID]->SetStatus(0);
              fprintf(input, " 1\n");
              Message.Result = true;
              return;
              break;
            }
            //Действие 3
            case 3:
            {
              fprintf(input, " %d SetLoad -", int_ID);
              ShipMas[int_ID]->SetLoad(0);
              fprintf(input, " 1\n");
              Message.Result = true;
              return;
              break;
            }
            //Действие 4
            case 4:
            {
              fprintf(input, " %d FreeDock -", int_ID);
              if(ShipMas[int_ID]->GetMission() == 0)
              {
                if(ShipMas[int_ID]->GetY() < 200)
                {
                  bl_PasDock1 = 1;
                  fprintf(input, " PasDock1");
                }
                else if(ShipMas[int_ID]->GetY() > 200)
                {
                  bl_PasDock2 = 1;
                  fprintf(input, " PasDock2");
                }
              }
              else if(ShipMas[int_ID]->GetMission() == 1)
              {
                if(ShipMas[int_ID]->GetX() < 200)
                {
                  bl_CargoDock1 = 1;
                  fprintf(input, " CargoDock1");
                }
                else if(ShipMas[int_ID]->GetX() > 200)
                {
                  bl_CargoDock2 = 1;
                  fprintf(input, " CargoDock2");
                }
              }

              fprintf(input, " 1\n");
              Message.Result = true;
              return;
              break;
            }
            //Действие 5
            case 5:
            {
              fprintf(input, " %d TimerError -", int_ID);
              MessageBox(NULL, "Ошибка таймера", "Ошибка", 0);
              fprintf(input, " 1\n");
              Message.Result = true;
              return;
              break;
            }
          }
          break;
        }
      }
  }
  else
    TCustomForm::WndProc(Message);
}

//---------------------------------------------------------------------------



void __fastcall TfrmMain::btnInfoClick(TObject *Sender)
{
  frmInfo->Visible = !frmInfo->Visible;
}
//---------------------------------------------------------------------------





void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
  fprintf(input,"\n");
  fprintf(input,"Iter = %d", flgPg);
  fclose(input);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCloseClick(TObject *Sender)
{
  flgOnOff = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnScndClick(TObject *Sender)
{
  frmAbout->Visible = !frmAbout->Visible;
}
//---------------------------------------------------------------------------

