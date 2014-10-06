//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"
#include "TChartForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChartForm *ChartForm;
//---------------------------------------------------------------------------
__fastcall TChartForm::TChartForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TChartForm::FormShow(TObject *Sender)
{
  Top = Form1->Top + Form1->Height;
}
//---------------------------------------------------------------------------
