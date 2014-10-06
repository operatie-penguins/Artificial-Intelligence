//---------------------------------------------------------------------------

#ifndef ufmMainH
#define ufmMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "arkcl.h"
//---------------------------------------------------------------------------
class TufmArk : public TForm
{
__published:	// IDE-managed Components
	TPaintBox *PaintBox1;
	TMemo *Memo1;
	TLabel *Lifes;
	TLabel *Score;
	TButton *Start;
	TCheckBox *Loging;
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TLabel *Label1;
	TLabel *Label2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall StartClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TufmArk(TComponent* Owner);

	void __fastcall WndProc(Messages::TMessage &Message);
	int DoPhone(Word WParamHi, Word WParamLo, int LParam);


	Situation* mpGame;

	UINT OurMessage;

	bool fLog;
};
//---------------------------------------------------------------------------
extern PACKAGE TufmArk *ufmArk;
//---------------------------------------------------------------------------
#endif
