//---------------------------------------------------------------------------

#ifndef uInfoH
#define uInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmInfo : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *radgrp1;
        TRadioGroup *radgrp2;
        TRadioGroup *radgrp3;
        TRadioGroup *radgrp4;
        TGroupBox *grbxNum;
        TLabel *lbNum;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
        TRadioButton *RadioButton7;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton9;
        TRadioButton *RadioButton10;
        TRadioButton *RadioButton11;
        TRadioButton *RadioButton12;
        TRadioButton *RadioButton13;
        TRadioButton *RadioButton14;
        TRadioButton *RadioButton15;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInfo *frmInfo;
//---------------------------------------------------------------------------
#endif
