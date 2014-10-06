//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "delayFormUnit.h"
#include "mainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdelayForm *delayForm;
//---------------------------------------------------------------------------
__fastcall TdelayForm::TdelayForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TdelayForm::Button1Click(TObject *Sender)
{
    mainForm->setDelay(StrToInt(delayEdit->Text));
    delayForm->Hide();
}
//---------------------------------------------------------------------------
