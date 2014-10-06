//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StartConfig.h"
#include "TMainForm.h"
#include "TControlForm.h"
#include "TChartForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TControlForm *ControlForm;
//---------------------------------------------------------------------------
__fastcall TControlForm::TControlForm(TComponent* Owner)
  : TForm(Owner)
{
  DecimalSeparator = '.';
  Left = Screen->Width - Width;
  StartConfig* config = StartConfig::instance();
  tbWolfCount->Text = config->wolfCount;
  tbHareCount->Text = config->hareCount;
  tbFoodCount->Text = config->foodCount;
  tbFoodLimit->Text = config->foodLimit;

  tbHareLifeLength->Text = config->hareLifeLength;
  tbWolfLifeLength->Text = config->wolfLifeLength;

  tbHarePregnancyLength->Text = config->harePregnancyLength;
  tbWolfPregnancyLength->Text = config->wolfPregnancyLength;
  tbHareSpawnFactor->Text = config->hareSpawnFactor;
  tbWolfSpawnFactor->Text = config->wolfSpawnFactor;

  tbFoodGenProbability->Text = config->foodGenProbabilityX1000;
  tbFoodRespawnProbability->Text = config->foodRespawnProbabilityX1000;

  tbHareSpeed->Text = config->hareSpeed;
  tbWolfSpeed->Text = config->wolfSpeed;
}
//---------------------------------------------------------------------------
void __fastcall TControlForm::cbLogClick(TObject *Sender)
{
  Form1->turnLogging(cbLog->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TControlForm::Button1Click(TObject *Sender)
{
  DecimalSeparator = '.';
  StartConfig* config = StartConfig::instance();
  config->wolfCount = tbWolfCount->Text.ToInt();
  config->hareCount = tbHareCount->Text.ToInt();
  config->foodCount = tbFoodCount->Text.ToInt();
  config->foodLimit = tbFoodLimit->Text.ToInt();

  config->hareLifeLength = tbHareLifeLength->Text.ToInt();
  config->wolfLifeLength = tbWolfLifeLength->Text.ToInt();

  config->harePregnancyLength = tbHarePregnancyLength->Text.ToInt();
  config->wolfPregnancyLength = tbWolfPregnancyLength->Text.ToInt();
  config->hareSpawnFactor = tbHareSpawnFactor->Text.ToInt();
  config->wolfSpawnFactor = tbWolfSpawnFactor->Text.ToInt();

  config->foodGenProbabilityX1000 = tbFoodGenProbability->Text.ToInt();
  config->foodRespawnProbabilityX1000 = tbFoodRespawnProbability->Text.ToInt();

  config->hareSpeed = tbHareSpeed->Text.ToDouble();
  config->wolfSpeed = tbWolfSpeed->Text.ToDouble();
  ChartForm->Series1->Clear();
  ChartForm->Series2->Clear();
  ChartForm->Series3->Clear();
  Form1->start();
}
//---------------------------------------------------------------------------

