//---------------------------------------------------------------------------

#ifndef sizeFormUnitH
#define sizeFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TsizeForm : public TForm
{
__published:	// IDE-managed Components
    TEdit *editWidth;
    TEdit *editHeight;
    TLabel *Label1;
    TLabel *Label2;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TsizeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TsizeForm *sizeForm;
//---------------------------------------------------------------------------
#endif
