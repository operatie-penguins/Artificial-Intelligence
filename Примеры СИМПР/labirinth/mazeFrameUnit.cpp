//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mazeFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TmazeFrame *mazeFrame;
//---------------------------------------------------------------------------
__fastcall TmazeFrame::TmazeFrame(TComponent* Owner)
  : TFrame(Owner)
{
}
//---------------------------------------------------------------------------

