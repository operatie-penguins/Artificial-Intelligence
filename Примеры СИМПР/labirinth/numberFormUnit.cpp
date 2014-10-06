//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "numberFormUnit.h"
#include "mainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TnumberForm *numberForm;
//---------------------------------------------------------------------------
__fastcall TnumberForm::TnumberForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TnumberForm::Button1Click(TObject *Sender)
{
    mainForm->setNumbers(StrToInt(editCop->Text),StrToInt(editCrime->Text));
    this->Hide();
}
//---------------------------------------------------------------------------
