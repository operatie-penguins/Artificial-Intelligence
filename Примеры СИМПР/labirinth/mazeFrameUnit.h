//---------------------------------------------------------------------------


#ifndef mazeFrameUnitH
#define mazeFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TmazeFrame : public TFrame
{
__published:	// IDE-managed Components
    TPanel *mazePanel;
    TImage *Image;
private:	// User declarations
public:		// User declarations
  __fastcall TmazeFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmazeFrame *mazeFrame;
//---------------------------------------------------------------------------
#endif
