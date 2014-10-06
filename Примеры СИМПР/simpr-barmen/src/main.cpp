//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#define  USERMESSAGE   "MyMessage"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	Game = new Situation(pb);
}
//---------------------------------------------------------------------------




void __fastcall TForm3::Button1Click(TObject *Sender)
{
  Game->turn();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
	OurMessage = RegisterWindowMessage("MyMessage");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::WndProc(Messages::TMessage &Message)
{
	if(Message.Msg == OurMessage)
	{
		Message.Result = DoPhone(Message.WParamHi, Message.WParamLo, Message.LParam);
	}
	else
	{
		TCustomForm::WndProc(Message);
	}
}
//---------------------------------------------------------------------------


int TForm3::DoPhone(Word WParamHi, Word WParamLo, int LParam)
{
	int Type = WParamHi;
	int Table = WParamLo;
	int Num = LParam;
	m->Lines->Add(AnsiString(Type) + " " + AnsiString(Table) + " " + AnsiString(Num));

	switch(Type)
	{
		case 0:
		switch(Table)
		{
		case 1:
			switch(Num)
			{
				case 1: return Game->isThere();
				case 2: return Game->areAll();
				case 3: return Game->looked();
				case 4: return Game->movedB();
			}
		case 2:
			switch(Num)
			{
				case 1: return Game->going();
				case 2: return Game->onChair();
				case 3: return Game->after();
			}
		case 3:
			switch(Num)
			{
				case 1: return Game->going2();
				case 2: return Game->n();
				case 3: return Game->free();
			}
		case 4:
			switch(Num)
			{
				case 1: return Game->sited();
			}
		case 5:
			switch(Num)
			{
				case 1: return Game->toR();
				case 2: return Game->goR();
				case 3: return Game->nB();
				case 4: return Game->serv();
			}
		}
		
		case 1:
		switch(Table)
		{
		case 1:
			switch(Num)
			{
				case 1: return Game->turn();
			}
		case 2:
			switch(Num)
			{
				case 1: return Game->del();
				case 2: return Game->next();
				case 3: return Game->move();
			}
		case 3:
			switch(Num)
			{
				case 1: return Game->move();
				case 2: return Game->sit();
				case 3: return Game->move();
				case 4: return Game->next();
			}
		case 4:
			switch(Num)
			{
				case 1: return Game->stand();
				case 2: return Game->next();
			}
		case 5:
			switch(Num)
			{
				case 1: return Game->dirc();
				case 2: return Game->moveB();
				case 3: return Game->give();
			}
    }
	}

	return 0;
}
//---------------------------------------------------------------------------



