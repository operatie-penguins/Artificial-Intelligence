//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------

struct fish
{
  int x;
  int y;
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TPanel *Panel1;
        TButton *B1;
        TButton *B2;
        TButton *B3;
        TButton *B4;
        TButton *B5;
        TButton *B6;
        TButton *B7;
        TButton *B8;
        TMenuItem *N2;
        TMenuItem *N3;
        TImage *Image1;
        void __fastcall N2Click(TObject *Sender);
        void __fastcall B1Click(TObject *Sender);
        void __fastcall B2Click(TObject *Sender);
        void __fastcall B3Click(TObject *Sender);
        void __fastcall B4Click(TObject *Sender);
        void __fastcall B5Click(TObject *Sender);
        void __fastcall B6Click(TObject *Sender);
        void __fastcall B7Click(TObject *Sender);
        void __fastcall B8Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        fish Top1[9];       //������������1, � ������� ����� ������� �� ������� ������������, �
        int Rang1; int T1;  // ������������� ������ � ����� �������������� ������ � arrayButtons
        fish Top2[9];       //������������2
        int Rang2; int T2;
        fish Top3[9];       //������������3
        int Rang3; int T3;
        fish Top4[9];       //������������4
        int Rang4; int T4;
        TButton *arrayButtons[9]; //������ ���������� �� ������-�����
        __int64 *allConfigs;        //������ ������ ��� ����������� ������������
        int countConfigs;         //���������� ����������� ������������
        void __fastcall EddConf(fish *Versh);
        bool __fastcall FindConf(fish *Versh);
        void __fastcall ClearConfs();
        bool bChange;             //���� �������������, false �� ������� �������������
        Cardinal OurMessage;
        void __fastcall WndProc(Messages::TMessage &Message);
        int DoSomeThing(Word WParamHi, Word WParamLo, int LParam);
        void __fastcall GetReadyMove(TButton *B, int Num); //����������� ������-�����
        int _fastcall Dostig();   //���������� ����� ���������� �� ������ ������������
        void __fastcall Init();   //����������� ��������� ������-����� � ������������� NowList
        int __fastcall Evristic(fish *Versh); //��������� ��������� �� ������ ������� ������������
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
