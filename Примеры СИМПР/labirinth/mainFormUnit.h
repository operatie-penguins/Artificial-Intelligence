//---------------------------------------------------------------------------

#ifndef mainFormUnitH
#define mainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "sizeFormUnit.h"
#include "numberFormUnit.h"
#include "thicknessFormUnit.h"
#include "mazeFrameUnit.h"
#include "personUnit.h"
//---------------------------------------------------------------------------
#include <vector>
#include <fstream>
//---------------------------------------------------------------------------


class TmainForm : public TForm
{
__published:	// IDE-managed Components
  TmazeFrame *mazeFrame;
  TMainMenu *mainMenu;
  TMenuItem *N1;
  TBevel *mazeBevel;
  TMenuItem *N2;
  TMenuItem *N3;
  TMenuItem *N4;
  TMenuItem *N5;
  TMenuItem *N6;
  TMenuItem *N7;
  TMenuItem *N8;
  TMenuItem *N9;
    TMenuItem *N11;
    TMenuItem *N12;
    TMemo *memoLog;
    TMenuItem *N13;
    TMenuItem *N10;
  void __fastcall N2Click(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall N5Click(TObject *Sender);
    void __fastcall N6Click(TObject *Sender);
    void __fastcall N8Click(TObject *Sender);
    void __fastcall N9Click(TObject *Sender);
    void __fastcall N12Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall N11Click(TObject *Sender);
    void __fastcall N13Click(TObject *Sender);
private:	// User declarations
    //Картинки
    Graphics::TBitmap * bmCopUp;
    Graphics::TBitmap * bmCopRight;
    Graphics::TBitmap * bmCopDown;
    Graphics::TBitmap * bmCopLeft;
    Graphics::TBitmap * bmCrimeUp;
    Graphics::TBitmap * bmCrimeRight;
    Graphics::TBitmap * bmCrimeDown;
    Graphics::TBitmap * bmCrimeLeft;

    Graphics::TBitmap * bmNULL; //Ухищрение

    typedef std::vector<int> vint;
    typedef std::vector<vint> intMatrix;
    typedef intMatrix positionMatrix;
    typedef intMatrix wallMatrix;
    typedef std::vector<Person*> personsLine;

    int mazeHeight, mazeWidth,
        numberCop,numberCrime;

    float mazeThickness;

    wallMatrix verticalWalls,horizontalWalls;

    personsLine queue;
    std::vector<bool> qAvaible;

    int delayTime;

    TImage * standartImage();
    void makeNewMaze();
    bool randomTry();
    bool avaibleWall(const int type,const int x,const int y);
    bool edgeWall(const int type, const int x, const int y);
    bool wall(const int type, const int x, const int y);

    bool edgeBarrier(const int type, const int x, const int y,
                     const bool start = false);
    bool loopBarrier(const int type, const int x, const int y, const int step,
                     const bool start = false);

    void markWall(const int type, const int x, const int y,
                  const int marktype = 2);

    void unmarkWalls();

    int checkMark(const int type, const int x, const int y);
    void setWall(const int type, const int x, const int y);
    void unsetWall(const int type, const int x, const int y);
    void setWallsDefault();
    void drawWalls();
    void personRandom();
    void saveToFile(const AnsiString);
    void loadFromFile(const AnsiString);
    void say(const AnsiString line);
    bool work(Word WParamHi, Word WParamLo, int LParam);
    bool ifCop(const int x,const int y);
    bool qFree();
    int positions(const int x, const int y);

    //Отладка
    void ShowAll();


public:		// User declarations
    UINT msgSimpr;
    void __fastcall WndProc(Messages::TMessage &Message);

    void setMazeSize(const int w,const int h);
    void setNumbers(const int cop,const int crime);
    void setThickness(const float t);
    int getMazeHeight();
    int getMazeWidth();

    //Посмотреть на x,y из a,b. Если стена или некуда идти, то -1;
    //если свободно, то 0, если коп, то 1, если преступник, то 2
    int look(const int a, const int b, const int x, const int y);

    //Переместить объект в позицию x,y
    void gotoXY(const int x, const int y, TImage * pImage);

  __fastcall TmainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
