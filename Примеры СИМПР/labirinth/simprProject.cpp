//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("mainFormUnit.cpp", mainForm);
USEFORM("mazeFrameUnit.cpp", mazeFrame); /* TFrame: File Type */
USEFORM("sizeFormUnit.cpp", sizeForm);
USEFORM("numberFormUnit.cpp", numberForm);
USEFORM("thicknessFormUnit.cpp", thicknessForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TmainForm), &mainForm);
         Application->CreateForm(__classid(TsizeForm), &sizeForm);
         Application->CreateForm(__classid(TnumberForm), &numberForm);
         Application->CreateForm(__classid(TthicknessForm), &thicknessForm);
         Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
