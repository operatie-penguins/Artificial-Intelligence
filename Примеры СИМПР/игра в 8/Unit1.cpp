//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define USERMESSAGE "OurMessage"
#define YES 1
#define NO 0
#define CONDITIONS 0
#define ACTIONS 1
//---------------------------------------------------------------------------
TForm1 *Form1;
TButton *Fishka; //Указатель на фишку, которую надо переместить в потоке move
//int *FishX;
//int *FishY;
int PustX;       //Координата  по X, на которую надо переместить фишку в потоке move
int PustY;       //Координата  по Y, на которую надо переместить фишку в потоке move

fish EndList[9] =          //Целевая конфигурация
                 {{2,2},{1,3},{2,3},{3,3},{3,2},{3,1},{2,1},{1,1},{1,2}};
fish NowList[9];           //Текущая конфигурация
HANDLE hMove;              //Хэндл потока перемещения
bool ItIsBorrow;           //Флаг Паузы. true => пауза
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{                                       //Заполняем массив кнопок-фишек
   arrayButtons[0] = B1;  arrayButtons[1] = B2;
   arrayButtons[2] = B3;  arrayButtons[3] = B4;
   arrayButtons[4] = B5;  arrayButtons[5] = B6;
   arrayButtons[6] = B7;  arrayButtons[7] = B8;
   for(int i=0; i<9;i++)                //Уставить целевую конфигурацию текущей
   {
     NowList[i] = EndList[i];
   }
   countConfigs = 0;
   allConfigs = new __int64[countConfigs];
   Init();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WndProc(Messages::TMessage &Message)
{
  if(Message.Msg == OurMessage)
    Message.Result = DoSomeThing(Message.WParamHi, Message.WParamLo, Message.LParam);
  else TCustomForm::WndProc(Message);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  OurMessage = RegisterWindowMessage(USERMESSAGE);
  bChange = false;     //Не пермешивалось
  ItIsBorrow = false;  //Пауза = нет
}
//---------------------------------------------------------------------------

int TForm1::DoSomeThing(Word WParamHi, Word WParamLo, int LParam)
{
  switch(WParamHi)
  {
    case CONDITIONS: // Условия
      switch(WParamLo)
      {
        case 1: // Таблица 1
          switch(LParam) // Номер условия
          {
            case 1: // Условие 1
              if(Evristic(&NowList[0])==0)
              {
                //ShowMessage("Таблица 1; Условие 1; Конечное состояние достигнуто? = YES" +IntToStr(Evristic(&NowList[0])));
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 1; Условие 1; Конечное состояние достигнуто? = NO" +IntToStr(Evristic(&NowList[0])));
                return NO;
              }
            case 2: // Условие 2
              if (bChange)
              {
                //ShowMessage("Таблица 1; Условие 2; Перемешано = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 1; Условие 2; Перемешано = NO");
                return NO;
              }
            case 3: // Условие 3
              if(ItIsBorrow)
              {
                //ShowMessage("Таблица 1; Условие 2; Ждать = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 1; Условие 2; Ждать = NO");
                return NO;
              }
            case 4: // Условие 4
              if (Dostig()==2)
              {
                //ShowMessage("Таблица 1; Условие 4;Достигаемо "+IntToStr(Dostig())+"; Достигаемо две вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 1; Условие 4;Достигаемо "+IntToStr(Dostig())+"; Достигаемо две вершины = NO");
                return NO;
              }
            case 5: // Условие 5
              if (Dostig()==3)
              {
                //ShowMessage("Таблица 1; Условие 5; Достигаемо три вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 1; Условие 5; Достигаемо три вершины = NO");
                return NO;
              }
          }
        break;
        case 2: // Таблица 2
          switch(LParam) // Номер условия
          {
            case 1: // Условие 1
              if (Rang1 < Rang2)
              {
                //ShowMessage("Таблица 2; Условие 1; Первая вершина выгоднее = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 2; Условие 1; Первая вершина выгоднее = NO");
                return NO;
              }
          }
        break;
        case 3: // Таблица 3
          switch(LParam) // Номер условия
          {
            case 1: // Условие 1
              if ((Rang1 < Rang2) && (Rang1 < Rang3))
              {
                //ShowMessage("Таблица 3; Условие 1; Самая высокая оценка у первой вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 3; Условие 1; Самая высокая оценка у первой вершины = NO");
                return NO;
              }
            case 2: // Условие 2
              if ((Rang2 < Rang1) && (Rang2 < Rang3))
              {
                //ShowMessage("Таблица 3; Условие 2; Самая высокая оценка у второй вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 3; Условие 2; Самая высокая оценка у второй вершины = NO");
                return NO;
              }
          }
        break;
        case 4: // Таблица 4
          switch(LParam) // Номер условия
          {
            case 1: // Условие 1
              if ((Rang1 < Rang2) && (Rang1 < Rang3) && (Rang1 < Rang4))
              {
                //ShowMessage("Таблица 4; Условие 1; Самая высокая оценка у первой вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 4; Условие 1; Самая высокая оценка у первой вершины = NO");
                return NO;
              }
            case 2: // Условие 2
              if ((Rang2 < Rang1) && (Rang2 < Rang3) && (Rang2 < Rang4))
              {
                //ShowMessage("Таблица 4; Условие 2; Самая высокая оценка у второй вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 4; Условие 2; Самая высокая оценка у второй вершины = NO");
                return NO;
              }
            case 3: // Условие 3
              if ((Rang3 < Rang1) && (Rang3 < Rang2) && (Rang3<Rang4))
              {
                //ShowMessage("Таблица 4; Условие 3; Самая высокая оценка у третьей вершины = YES");
                return YES;
              }
              else
              {
                //ShowMessage("Таблица 4; Условие 3; Самая высокая оценка у третьей вершины = NO");
                return NO;
              }
          }
        break;
      }
      ////////////
  case ACTIONS: // Действия
    switch(WParamLo)
    {
      case 1: // Таблица 1
        switch(LParam) // Номер действия
        {
          case 1: // Действие 1
            //ShowMessage("Таблица 1; Действие 1; Перемешать;");
            N2Click(this);
            return YES;
          case 2: // Действие 2
            //ShowMessage("Таблица 1; Действие 2; Ждать;");
            return YES;
          case 3: // Действие 3
            //ShowMessage("Таблица 1; Действие 3; Посчитать оценки для двух возможных вершин;");
            Rang1 = Evristic(&Top1[0]);
            Rang2 = Evristic(&Top2[0]);
            return YES;
          case 4: // Действие 4
            //ShowMessage("Таблица 1; Действие 4; Посчитать оценки для трех возможных вершин;");
            Rang1 = Evristic(&Top1[0]);
            Rang2 = Evristic(&Top2[0]);
            Rang3 = Evristic(&Top3[0]);
            return YES;
          case 5: // Действие 5
            //ShowMessage("Таблица 1; Действие 5; Посчитать оценки для четырех возможных вершин;");
            Rang1 = Evristic(&Top1[0]);
            Rang2 = Evristic(&Top2[0]);
            Rang3 = Evristic(&Top3[0]);
            Rang4 = Evristic(&Top4[0]);
            return YES;
        }
      case 2: // Таблица 2
        switch(LParam) // Номер действия
        {
          case 1: // Действие 1
            //ShowMessage("Таблица 2; Действие 1; Перейти в первую; Переместить "+IntToStr(T1)+"ю");
            arrayButtons[T1-1]->Click();
            return YES;
          case 2: // Действие 2
            //ShowMessage("Таблица 2; Действие 2; Перейти во вторую; Переместить "+IntToStr(T2)+"ю");
            arrayButtons[T2-1]->Click();
            return YES;
        }
      case 3: // Таблица 3
        switch(LParam) // Номер действия
        {
          case 1: // Действие 1
            //ShowMessage("Таблица 3; Действие 1; Перейти в первую; Переместить "+IntToStr(T1)+"ю");
            arrayButtons[T1-1]->Click();
            return YES;
          case 2: // Действие 2
            //ShowMessage("Таблица 3; Действие 2; Перейти во вторую; Переместить "+IntToStr(T2)+"ю");
            arrayButtons[T2-1]->Click();
            return YES;
          case 3: // Действие 3
            //ShowMessage("Таблица 3; Действие 3; Перейти в третью; Переместить "+IntToStr(T3)+"ю");
            arrayButtons[T3-1]->Click();
            return YES;
        }
      case 4: // Таблица 4
        switch(LParam) // Номер действия
        {
          case 1: // Действие 1
            //ShowMessage("Таблица 4; Действие 1; Перейти в первую; Переместить "+IntToStr(T1)+"ю");
            arrayButtons[T1-1]->Click();
            return YES;
          case 2: // Действие 2
            //ShowMessage("Таблица 4; Действие 2; Перейти во вторую; Переместить "+IntToStr(T2)+"ю");
            arrayButtons[T2-1]->Click();
            return YES;
          case 3: // Действие 3
            //ShowMessage("Таблица 4; Действие 3; Перейти в третью; Переместить "+IntToStr(T3)+"ю");
            arrayButtons[T3-1]->Click();
            return YES;
          case 4: // Действие 4
            //ShowMessage("Таблица 4; Действие 4; Перейти в четвертую; Переместить "+IntToStr(T4)+"ю");
            arrayButtons[T4-1]->Click();
            return YES;
        }
        break;
    }
  }
  return 0;
}
//---------------------------------------------------------------------------

bool __fastcall Near(fish f1, fish pust)  //Фишки рядом(можно поменять местами)?
{
  if((f1.x==pust.x) && (abs(f1.y-pust.y)<=1))
    return true;
  if((f1.y==pust.y) && (abs(f1.x-pust.x)<=1))
    return true;
  return false;
}
//---------------------------------------------------------------------------

int _fastcall TForm1::Dostig()            //Найти достижимые конфигурации
{
  fish List[9];            //Массив, для временных конфигураций
  int result=0;
  for(int i=1; i<9; i++)
  {
    if(Near(NowList[i],NowList[0]))
      {
        List[0] = NowList[i];
        for(int j=1; j<9; j++)
        {
          List[j] = NowList[j];
        }
        List[i] = NowList[0];
        switch(result)
        {
          case 0:
            for(int j=0; j<9; j++)
              Top1[j] = List[j];
            T1 = i;
            break;
          case 1:
            for(int j=0; j<9; j++)
              Top2[j] = List[j];
            T2 = i;
            break;
          case 2:
            for(int j=0; j<9; j++)
              Top3[j] = List[j];
            T3 = i;
            break;
          case 3:
            for(int j=0; j<9; j++)
              Top4[j] = List[j];
            T4 = i;
            break;
        }
        result += 1;
      }
  }
  return result;
}
//---------------------------------------------------------------------------

int __fastcall TForm1::Evristic(fish *Versh)  //Эвристическая функция
{
  int result = 0;
  int sumrasst = 0;
  fish List[9];      //Оцениваемая конфигурация
  for(int i=0; i<9; i++)
  {
    List[i] = *Versh;
    Versh += 1;
  }
  bool flag =true;
  for(int i=0; i<9; i++)
  {
    if((List[i].x != EndList[i].x) || (List[i].y != EndList[i].y))
      flag = false;
  }
  if(flag)
  {
    return 0;
  }
  for(int i=1; i<9; i++)
  {
    sumrasst += abs(List[i].x - EndList[i].x) + abs(List[i].y - EndList[i].y);
  }
  int uporyad = 0;
  for(int i=1; i<9; i++)
  {
    if((List[i].x==2) && (List[i].y==2))
      uporyad += 1;
    else
      if(((List[i].x==1) && (List[i].y==3) && (List[i % 8 + 1].x==2) && (List[i % 8 + 1].y==3)) ||
         ((List[i].x==2) && (List[i].y==3) && (List[i % 8 + 1].x==3) && (List[i % 8 + 1].y==3)) ||
         ((List[i].x==3) && (List[i].y==3) && (List[i % 8 + 1].x==3) && (List[i % 8 + 1].y==2)) ||
         ((List[i].x==3) && (List[i].y==2) && (List[i % 8 + 1].x==3) && (List[i % 8 + 1].y==1)) ||
         ((List[i].x==3) && (List[i].y==1) && (List[i % 8 + 1].x==2) && (List[i % 8 + 1].y==1)) ||
         ((List[i].x==2) && (List[i].y==1) && (List[i % 8 + 1].x==1) && (List[i % 8 + 1].y==1)) ||
         ((List[i].x==1) && (List[i].y==1) && (List[i % 8 + 1].x==1) && (List[i % 8 + 1].y==2)) ||
         ((List[i].x==1) && (List[i].y==2) && (List[i % 8 + 1].x==1) && (List[i % 8 + 1].y==3)))
          uporyad += 0;
      else
        uporyad += 2;
  }
  result = sumrasst + 3*uporyad;
  if(FindConf(&List[0]))
    result +=100;
  return result;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N2Click(TObject *Sender) //Перемешать
{
  bChange = true;   //Перемешано
  randomize();
  int f=1;
  for(int i=0; i<1000;i++)
  {
    do
      f=random(8)+1;
    while(!Near(NowList[f],NowList[0]));
    fish P = NowList[0];
    NowList[0] = NowList[f];
    NowList[f] = P;
    Init();
  }
  ClearConfs();
}
//---------------------------------------------------------------------------

DWORD WINAPI Move( LPVOID lpParam )
{
  while((Fishka->Left != PustX) || (Fishka->Top != PustY))
  {
    
    if(Fishka->Left > PustX)
      Fishka->Left -= 1;
    if(Fishka->Left < PustX)
      Fishka->Left += 1;
    if(Fishka->Top > PustY)
      Fishka->Top -= 1;
    if(Fishka->Top < PustY)
      Fishka->Top += 1;
    Sleep(5);
  }
  ItIsBorrow = false;
  return 0;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Init()
{
  B1->Left = (NowList[1].x - 1) * 100; B1->Top  = (3 - NowList[1].y) * 100;
  B2->Left = (NowList[2].x - 1) * 100; B2->Top  = (3 - NowList[2].y) * 100;
  B3->Left = (NowList[3].x - 1) * 100; B3->Top  = (3 - NowList[3].y) * 100;
  B4->Left = (NowList[4].x - 1) * 100; B4->Top  = (3 - NowList[4].y) * 100;
  B5->Left = (NowList[5].x - 1) * 100; B5->Top  = (3 - NowList[5].y) * 100;
  B6->Left = (NowList[6].x - 1) * 100; B6->Top  = (3 - NowList[6].y) * 100;
  B7->Left = (NowList[7].x - 1) * 100; B7->Top  = (3 - NowList[7].y) * 100;
  B8->Left = (NowList[8].x - 1) * 100; B8->Top  = (3 - NowList[8].y) * 100;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GetReadyMove(TButton *B, int Num)
{
  EddConf(&NowList[0]);
  ItIsBorrow = true;
  Fishka = B;
  PustX = (NowList[0].x - 1) * 100;
  PustY = (3 - NowList[0].y) * 100;
  fish Var = NowList[0];
  NowList[0] = NowList[Num];
  NowList[Num] = Var;
  DWORD dwThreadId = 0;
  hMove = CreateThread(NULL, 0, Move, NULL, 0, &dwThreadId);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B1Click(TObject *Sender)
{
  if((Near(NowList[1],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B1,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B2Click(TObject *Sender)
{
  if((Near(NowList[2],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B2,2);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B3Click(TObject *Sender)
{
  if((Near(NowList[3],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B3,3);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B4Click(TObject *Sender)
{
  if((Near(NowList[4],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B4,4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B5Click(TObject *Sender)
{
  if((Near(NowList[5],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B5,5);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B6Click(TObject *Sender)
{
  if((Near(NowList[6],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B6,6);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B7Click(TObject *Sender)
{
  if((Near(NowList[7],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B7,7);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B8Click(TObject *Sender)
{
  if((Near(NowList[8],NowList[0])) && (!ItIsBorrow))
    GetReadyMove(B8,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EddConf(fish *Versh)
{
  fish List[9];      //Добавляемая конфигурация
  for(int i=0; i<9; i++)
  {
    List[i] = *Versh;
    Versh += 1;
  }
  __int64 sum=0;
  int por = 100000000;
  for(int i=0; i<9; i++)
  {
    sum += (List[i].x + 3*(3-List[i].y))*por;
    por /= 10;
  }
  __int64 *oldAllConfigs = new __int64[countConfigs];
  for(int i=0; i<countConfigs; i++)
    oldAllConfigs[i] = allConfigs[i];
  countConfigs += 1;
  allConfigs = new __int64[countConfigs];
  for(int i=0; i<countConfigs-1; i++)
    allConfigs[i] = oldAllConfigs[i];
  allConfigs[countConfigs-1] = sum;
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::FindConf(fish *Versh)
{
  fish List[9];      //Добавляемая конфигурация
  for(int i=0; i<9; i++)
  {
    List[i] = *Versh;
    Versh += 1;
  }
  __int64 sum=0;
  int por = 100000000;
  for(int i=0; i<9; i++)
  {
    sum += (List[i].x + 3*(3-List[i].y))*por;
    por /= 10;
  }
  int SearchCount = 0;
  do
  {
    if(allConfigs[SearchCount] == sum)
      return true;
    SearchCount += 1;
  }
  while(SearchCount < countConfigs);
  return false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClearConfs()
{
  allConfigs = new __int64[0];
  countConfigs = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

