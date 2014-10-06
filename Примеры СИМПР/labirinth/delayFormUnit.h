//---------------------------------------------------------------------------

#ifndef delayFormUnitH
#define delayFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TdelayForm : public TForm
{
__published:	// IDE-managed Components
    TEdit *delayEdit;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TdelayForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TdelayForm *delayForm;
//---------------------------------------------------------------------------
#endif
