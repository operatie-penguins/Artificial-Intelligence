//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include "Condition.h"
#include "SysAction.h"
#include "Model.h"
#include "Hare.h"
#include "Painter.h"
#include "Registry.h"
#include "TControlForm.h"
#include "TChartForm.h"
#include "TMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  this->DoubleBuffered = true;
  Panel1->DoubleBuffered = true;
  wndMsgId = RegisterWindowMessage(MESSAGE_IDENTIFIER);
  randomize();

  this->Caption = WINDOW_CAPTION;
  this->WindowProc = OwnWndProc;
  model = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OwnWndProc(Messages::TMessage &Message)
{
  if (Message.Msg == wndMsgId) {
    char buf[100];

    int tableNum = Message.WParamLo - 1;
    int condOrActNum = Message.LParam - 1;
    int isAction = Message.WParamHi;

    sprintf(buf, " %d %d %d ", tableNum, condOrActNum, isAction);

    AnsiString log = AnsiString(buf);
    if(!isAction)
    {
      Condition* cond = Registry::instance()->getCondition(tableNum, condOrActNum);
      if(cond) {
        bool condResult = cond->check(model);
        log += cond->getRuText();
        log += " ";
        log += condResult ? "Да" : "Нет";
        Message.Result = condResult;
      } else {
        log += "Condition not found.";
        Message.Result = true;
      }
    } else {
      SysAction* act = Registry::instance()->getAction(tableNum, condOrActNum);
      if(act) {
        act->doAction(model);
        log += act->getRuText();
        Message.Result = true;
      } else {
        log += "Action not found.";
        Message.Result = true;
      }
    }
    if(logging) {
      LogMemo->Lines->Add(log);
    }
  }
  else
    WndProc(Message);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormResize(TObject *Sender)
{
  pPainter->onResize(PaintBox1->Width, PaintBox1->Height);
}
//---------------------------------------------------------------------------


void TForm1::turnLogging(bool state) {
  logging = state;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
  pPainter = new Painter(PaintBox1->Canvas);
  pPainter->onResize(PaintBox1->Width, PaintBox1->Height);
  logging = true;
  Top = 0;
  Left = 0;
  ControlForm->Show();
  ChartForm->Show();
}
//---------------------------------------------------------------------------

void TForm1::start() {
  if(model) {
    delete model;
  }
  model = new Model();
  pPainter->setModel(model);
  model->paused = false;
}
//---------------------------------------------------------------------------






