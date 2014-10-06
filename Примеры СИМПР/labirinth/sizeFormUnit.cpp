//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "sizeFormUnit.h"
#include "mainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TsizeForm *sizeForm;
//---------------------------------------------------------------------------
__fastcall TsizeForm::TsizeForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TsizeForm::Button1Click(TObject *Sender)
{
    mainForm->setMazeSize(StrToInt(editWidth->Text),StrToInt(editHeight->Text));
    this->Hide();
}
//---------------------------------------------------------------------------
