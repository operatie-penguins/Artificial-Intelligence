//---------------------------------------------------------------------------

#ifndef TControlFormH
#define TControlFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TControlForm : public TForm
{
__published:	// IDE-managed Components
  TCheckBox *cbLog;
  TButton *Button1;
  TLabel *Label1;
  TEdit *tbHareCount;
  TLabel *Label2;
  TEdit *tbWolfCount;
  TLabel *Label3;
  TEdit *tbFoodCount;
  TLabel *Label4;
  TEdit *tbFoodLimit;
  TGroupBox *GroupBox1;
  TLabel *Label5;
  TLabel *Label6;
  TEdit *tbHareLifeLength;
  TEdit *tbWolfLifeLength;
  TGroupBox *GroupBox2;
  TLabel *Label7;
  TLabel *Label8;
  TEdit *tbHarePregnancyLength;
  TEdit *tbWolfPregnancyLength;
  TEdit *tbHareSpawnFactor;
  TEdit *tbWolfSpawnFactor;
  TGroupBox *GroupBox3;
  TLabel *Label9;
  TLabel *Label10;
  TEdit *tbFoodGenProbability;
  TEdit *tbFoodRespawnProbability;
  TGroupBox *GroupBox4;
  TLabel *Label11;
  TLabel *Label12;
  TEdit *tbHareSpeed;
  TEdit *tbWolfSpeed;
  void __fastcall cbLogClick(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TControlForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TControlForm *ControlForm;
//---------------------------------------------------------------------------
#endif
