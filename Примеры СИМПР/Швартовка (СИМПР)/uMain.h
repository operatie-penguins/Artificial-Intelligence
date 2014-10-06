//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <Math.hpp>
#include <System.hpp>

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnlDock;
        TTimer *tmr_Main;
        TGroupBox *grbxCtrl;
        TButton *btnInfo;
        TButton *btnScnd;
        TButton *btnClose;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnInfoClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnCloseClick(TObject *Sender);
        void __fastcall btnScndClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
        void __fastcall WndProc(Messages::TMessage &Message);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

