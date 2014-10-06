//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Messages.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TShape *Table1;
        TShape *Table2;
        TShape *Table3;
        TImageList *GameImages;
        TTimer *Timer1;
	TLabel *GamePointsLabel;
	TLabel *GamePoints;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void __fastcall WndProc(Messages::TMessage &Message);
        int MainGameProc(Word WParamHi, Word WParamLo, int LParam);
		void DrawGameObjects();
		void UpdateGamePoints(int Sum);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
