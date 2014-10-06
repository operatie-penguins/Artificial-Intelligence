//---------------------------------------------------------------------------

#ifndef numberFormUnitH
#define numberFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TnumberForm : public TForm
{
__published:	// IDE-managed Components
    TEdit *editCop;
    TButton *Button1;
    TLabel *Label2;
    TLabel *Label1;
    TEdit *editCrime;
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TnumberForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TnumberForm *numberForm;
//---------------------------------------------------------------------------
#endif
