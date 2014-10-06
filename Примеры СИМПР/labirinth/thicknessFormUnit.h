//---------------------------------------------------------------------------

#ifndef thicknessFormUnitH
#define thicknessFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TthicknessForm : public TForm
{
__published:	// IDE-managed Components
    TEdit *editThickness;
    TLabel *Label1;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TthicknessForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TthicknessForm *thicknessForm;
//---------------------------------------------------------------------------
#endif
