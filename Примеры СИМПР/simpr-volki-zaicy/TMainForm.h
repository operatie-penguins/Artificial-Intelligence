//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

class Model;
class Painter;

#define MESSAGE_IDENTIFIER ("RABBITS")
#define WINDOW_CAPTION ("RABBITS")

class TForm1 : public TForm
{
  __published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TMemo *LogMemo;
    TPaintBox *PaintBox1;
    void __fastcall FormResize(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  private:	// User declarations
    Model* model;
    Painter* pPainter;
    bool logging;
    unsigned int wndMsgId;
  public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    void __fastcall OwnWndProc(Messages::TMessage &Message);
    void turnLogging(bool state);
    void start();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
