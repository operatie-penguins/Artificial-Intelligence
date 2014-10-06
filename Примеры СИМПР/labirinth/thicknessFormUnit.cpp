//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "thicknessFormUnit.h"
#include "mainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TthicknessForm *thicknessForm;
//---------------------------------------------------------------------------
__fastcall TthicknessForm::TthicknessForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TthicknessForm::Button1Click(TObject *Sender)
{
    mainForm->setThickness(StrToFloat(editThickness->Text));
    this->Hide();
        
}
//---------------------------------------------------------------------------
