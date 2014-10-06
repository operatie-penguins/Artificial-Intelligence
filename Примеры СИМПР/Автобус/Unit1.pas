unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, ImgList, Grids;
 const
 MESSAGE_STR = 'MyMessage';
type
  TForm1 = class(TForm)
    BitBtn1: TBitBtn;
    Image2: TImage;
    Panel1: TPanel;
    Panel2: TPanel;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton5: TSpeedButton;
    SpeedButton6: TSpeedButton;
    SpeedButton7: TSpeedButton;
    SpeedButton8: TSpeedButton;
    SpeedButton9: TSpeedButton;
    SpeedButton10: TSpeedButton;
    SpeedButton11: TSpeedButton;
    SpeedButton12: TSpeedButton;
    SpeedButton13: TSpeedButton;
    SpeedButton14: TSpeedButton;
    SpeedButton15: TSpeedButton;
    ImageList1: TImageList;
    Edit1: TEdit;
    Edit2: TEdit;
    Image1: TImage;
    Image3: TImage;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    ListBox1: TListBox;
    StringGrid1: TStringGrid;
    procedure BitBtn1Click(Sender: TObject);
     Procedure WNDProc ( var Message: Tmessage); override;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    msgSIMPR: UINT;
    { Public declarations }
  end;
var
  Form1: TForm1;
  Ikord, JKord: integer;
  KolPasInSt : integer; //Кол-во человек на станции
  KolPAsOutFromBus : integer; //Кол-во человек вышедших
  KolKrug : Integer;
  HodBus  : Boolean;
  HodPesh : Boolean;
  NomberSt: Integer;
  KolPas : integer;
  Group : integer;  // 1 если 1 чел 0 если пара
  GroupKol: integer; // Кол-во групп в грппе на пасадку
  ColorS : boolean; // Цвет светофора
  RandomColorS : Integer; // Рандом для светофора
  GoGame: boolean;
  Mas2Sm : array [1..5,1..2] of integer;  // Массив занятых двойных
  MAs1Sm : array [11..15] of integer; //Массив занятых одноместных
  jrebii : integer; // гр из 1 или 2 чел
  BusVisPas: boolean; // Если высадил то true
  KolPlInB1,KolPlInB2 : integer;    // cвободные места в авт
  curdir : String;
 KolPasInBus1,KolPasInBus2 : integer;

 // BasVisPas : boolean ; // true если высадил пасажиров, просто метка
  kolPas1, kolPas2 : integer; // Сколько  сгенерили
  Svet: boolean;
  Timer : integer;
  tmpStr : String;
//  Sit1,Sit2 : integer; // кол-во занятых мест
implementation

{$R *.dfm}


//procedure TTESSTT;
//var i,j : Integer;
//begin
//for i := 1 to 5 do
  //for j := 1 to 2 do
   // form1.StringGrid1.Cells[i,j] := IntToStr(mas2sm[i,j]);
//end;



procedure Delay(msecs : Longint);
var FirstTick : longint;
begin FirstTick:=GetTickCount;
repeat Application.ProcessMessages;
until GetTickCount-FirstTick >= msecs;
end;

//---------------------- Подсчет своб мест--------------------------------------
Procedure KolSitPlase ;
var
i,j:integer;

begin
KolPlInB1:=0;
KolPlInB2:=0;
// Одиночки
For i:=11 to 15 do
If Mas1Sm[i]=-1 then Inc(KolPlInB1);


// пары
For i:=1 to 5 do
 for j:=1 to 2 do   begin
    If ( ( j mod 2 <>0)   and ( Mas2Sm[i,j]=-1)
    and (Mas2Sm[i,j+1]=-1) ) then   KolPlInB2:=KolPlInB2+2 ;

  If Mas2Sm[i,j]=-1 then  Inc(KolPlInB1);
                    end;
//Showmessage('Один '+ IntToStr(KolPlInB1)+ 'Двух '+IntToStr(KolPlInB2));
end;
// Удаление картинки при высадки
procedure DelSmFrSb(st: string)  ;
begin
curdir := GetCurrentDir;
If form1.SpeedButton1.Caption= ST THEN
Form1.SpeedButton1.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton2.Caption= ST THEN
form1.SpeedButton2.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton3.Caption= ST THEN
form1.SpeedButton3.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton4.Caption= ST THEN
form1.SpeedButton4.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton5.Caption= ST THEN
form1.SpeedButton5.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton6.Caption= ST THEN
form1.SpeedButton6.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton7.Caption= ST THEN
form1.SpeedButton7.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton8.Caption= ST THEN
form1.SpeedButton8.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton9.Caption= ST THEN
form1.SpeedButton9.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton10.Caption= ST THEN
form1.SpeedButton10.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton11.Caption= ST THEN
form1.SpeedButton11.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton12.Caption= ST THEN
form1.SpeedButton12.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton13.Caption= ST THEN
form1.SpeedButton13.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton14.Caption= ST THEN
form1.SpeedButton14.Glyph.LoadFromFile(curdir+'\1.bmp');

If form1.SpeedButton15.Caption= ST THEN
form1.SpeedButton15.Glyph.LoadFromFile(curdir+'\1.bmp');
end;
 // ----------Просцедура Генерации пасажиров на станции--------------------------
procedure GenerPasOnSt( var kolPas1: integer; var kolPas2: integer);
var
Kol2Sm: integer; //Кол-во групп по 2 чел

i: integer;
f: boolean;
begin
// Двойные
randomize;
Kol2Sm:= random(6);
KolPas2:=Kol2Sm*2;
// Одинарные
F:=false;
While f=false do begin
randomize;
KolPas1:= random(15);
If (KolPas1 <= (15-KolPas2)) then f:= true else f:= false;
form1.Edit1.Text:= IntToStr(kolPas1);
form1.Edit2.Text:= IntToStr(KolPas2);
                 end;

// Сдвиг Edit1 Edit2
Form1.Edit1.Left:=form1.Image2.Left+ 6;
form1.Edit1.Top:=form1.Image2.Top ;
form1.Edit2.Top:=form1.Image2.Top;
form1.Edit2.Left:= form1.Image2.Left + 26;
end;

procedure GetOutAll;
var
I,j, count :integer;
st: string;
begin
// Одиночки

For i:=11 to 15 do begin

Mas1Sm[i]:=-1;
St:=IntToStr(i)+'o';
DelSmFrSb(St);
St:='';
Count:=count-1;
                     end;
For i:=1 to 5 do
 For j:=1 to 2 do       begin
 St:=IntTostr(i)+IntToStr(j);
  DelSmFrSb(St);
 St:='';
                       end;
{ // Одиночки с двойных мест


 Mas2Sm[i,j]:=-1;
 St:=IntToStr(j);
 DelSmFrSb(St);
 St:='';
 Count:=count-1;
                       end;
// Пары

For i:=1 to 5 do
 For j:=1 to 2 do

  If ( Mas2Sm[i,j]=2) then   begin

       Mas2Sm[i,j]:= -1;
       St:= IntToStr(i)+IntToStr(j);
       DelSmFrSb(St);


                                end;  }



//TTESSTT;
end;
//------------------------Процедура Задания стартового положения---------------

procedure Start ;
var i,j: integer;
begin
timer:=1;
form1.Image2.Left:= 814;
form1.Image2.Top:= 64;

NomberSt:=0;
form1.Image2.Visible:= true;
//ColorS:= true;
Ikord := 814;
Jkord:= 64;
BusVisPas:= false;

HodBus := False;
HodPesh := false;

group:=-1;
for i:=1 to 5 do begin
 For j:=1 to 2 do
  Mas2Sm[i,j]:= -1;
  
                  end;
For i:=11 to 15 do
Mas1Sm[i]:=-1;

GroupKol:=0;
Inc(KolKrug);
form1.Edit1.Text:='';
form1.Edit2.Text:='';

GetOutAll;
end;



Procedure Sdvig; //(Ikord : integer; JKord : integer);
Var i: integer;

begin
for i:=1 to 9 do begin
form1.Image2.Left:= form1.Image2.Left -20;
form1.Image2.Top:= Form1.Image2.Top + 10;
delay(100);

                  end;
Inc(NomberSt);
//GenerPasOnSt( kolPas1, kolPas2);
BusVisPas:= false;
 form1.Edit1.Text:='';
 form1.Edit2.Text:='';
end;
//------------------------------------------------------------------------------









// ----------Поиск соответственной Speedbutton ----------------------------------
procedure sootv(st: string; int : integer);
begin
If form1.SpeedButton1.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton1.Glyph);
If form1.SpeedButton2.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton2.Glyph);
If form1.SpeedButton3.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton3.Glyph);
If form1.SpeedButton4.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton4.Glyph);
If form1.SpeedButton5.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton5.Glyph);
If form1.SpeedButton6.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton6.Glyph);
If form1.SpeedButton7.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton7.Glyph);
If form1.SpeedButton8.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton8.Glyph);
If form1.SpeedButton9.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton9.Glyph);
If form1.SpeedButton10.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton10.Glyph);
If form1.SpeedButton11.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton11.Glyph);
If form1.SpeedButton12.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton12.Glyph);
If form1.SpeedButton13.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton13.Glyph);
If form1.SpeedButton14.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton14.Glyph);
If form1.SpeedButton15.Caption= ST THEN form1.ImageList1.GetBitmap(int,form1.SpeedButton15.Glyph);
end;



//--------------Определение группы па посадку-----------------------------------
 procedure OcherNaPasadky;
 var
 st1,st2: string;
 f: boolean;
 begin
 st2:= form1.Edit2.Text;
 st1:= form1.Edit1.Text;

 f:= false;
 while f = false do begin
 randomize;
 group:= random(3);   // 1 если один 0 если двойные
 If group=0 then f:= false;
 If ( (group=2) and (StrToInt(St2)>0) ) then f:= true;
 If ( (group=1) and (StrToInt(St1)>0) ) then f:= true;
 If ( (StrToInt(St2)=0)  and ( StrToInt(St1)=0) ) then begin
                                                              GroupKol:=35;
                                                              f:= true;
                                                         end;
                     end;

 If group=2 then GroupKol:=2;
 If group=1 then GroupKol:=1;
//Showmessage ('Группа= '+IntToStr(groupKol));
 end;

//------------------------------- Посадка в астобус Груп из 2-------------------
procedure GoSitDoubl;
Var
numi,numj : integer;
i, j: integer;
st : string;
begin


// Если на вх 2
numi:=-1;
numj:=-1;

For i:=1 to 5 do
 For j:=1 to 2 do

  If ( ( j=1)   and ( Mas2Sm[i,1]=-1)  and (Mas2Sm[i,2]=-1) )
  then begin
       numj:=j;
       numi:=i;
       end;
  If ( (Numi<>-1) and (Numj<>-1) ) then  begin
   Mas2Sm[numi,numj+1]:= 2;
   Mas2Sm[numi,numj]:= 2;
   St:= IntToStr(numi)+IntToStr(numj);
   sootv(st,0);
   St:='';
   St:= IntToStr(numi)+IntToStr(numj+1);
   sootv(st,1);// прорисовываем картинку
   st:='';

Form1.Edit2.Text:= IntToStr( StrToInt(form1.Edit2.text) -2  );
                                         end;


//TTESSTT;

end;

// -----------------------Посадка в автобус групп по 1 чел-ку
procedure GoSitPlaseOne;
var
i,j : integer;
st : string;
numi,numj : integer;
begin

numi:=-1;
numj := -1;
// Проверяем одиночнык
For i:=11 to 15 do 
 If Mas1Sm[i]=-1 then
  numi:= i;

                       
If numi<>-1 then begin

Mas1Sm[numi]:=1;
st:= IntToStr(numi)+'o';
sootv(st,2);
st:='';

Form1.Edit1.Text:= IntToStr( StrToInt(form1.Edit1.text) -1  );

                 end;

// Проверить двойные места
 If numi=-1 then begin
  For i:=1 to 5 do
   for j:=1 to 2 do
   If Mas2Sm[i,j]= -1 then begin
                           numi:=i;
                           numj:=j;

                           end;

   Mas2Sm[numi,numj]:= 1;
   St:= IntToStr(numi)+IntToStr(numj);
   sootv(st,2);
   St:='';
Form1.Edit1.Text:= IntToStr( StrToInt(form1.Edit1.text) -1  );

                end;
//TTESSTT;
end;

//-----------------------------Проверка наличия пустых двойных мест-------------

function ChekSvobodDoublPlace : boolean;
VAr
i,j,nj,ni : integer;
begin
nj:=-1;
ni:=-1;
For i:=1 to 5 do
 For j:=1 to 2 do

  If ( ( j = 1)   and ( Mas2Sm[i,j]=-1)  and (Mas2Sm[i,j+1]=-1) )
  then begin
       nj:=j;
       ni:=i;
       end;

If ( (nj<>-1) and (ni<>-1) ) then  ChekSvobodDoublPlace:= true else
ChekSvobodDoublPlace:= false;

end;


//------------------------ Высадка пасажиров------------------------------------

Procedure GoOut( var BasVisPas: boolean);
var
i,j:integer;
rand: integer;
KolPasInBus1 : integer;
KolPasInBus2: integer;
f,ff: boolean;
count: integer;
St: string;
begin

KolSitPlase;
 BasVisPas:= true;

//------------------------- Высадка одиночек
  //


KolPasInBus1:= 15 -  KolPlInB1;
//Showmessage('Кол-во занятых 1 мест ' +IntToStr(KolPasInBus1));
If KolPasInBus1<>0 then begin // если 1 то высаживать
f:= false;
While f=false do begin
randomize;
rand:= random(KolPasInBus1+1); // cколько всего высаживать
If rand=0 then f:= false else f:= true;
                 end;

count:=rand;
St:='';
// высадка с одиночных мест одиночек
for j:=11 to High(Mas1Sm) do
If ( (Mas1sm[j]=1) and (count<>0)) then  begin
Mas1Sm[j]:=-1;
St:=IntToStr(j)+'o';
DelSmFrSb(St);
St:='';
Count:=count-1;
                                         end;
// Высадка с двойных одиночек
If  count<>0 then begin
For i:=1 to 5 do
 For j:=1 to 2 do
 If Mas2Sm[i,j]=1 then begin
 Mas2Sm[i,j]:=-1;
 St:=IntToStr(j);
 DelSmFrSb(St);
 St:='';
 Count:=count-1;
                       end;
                  end;



               end;

//TTESSTT;

// -----------------------------------Высадка пар------------------------------


KolPasInBus2:= 10 -  KolPlInB2;
//Showmessage('Кол-во занятых 2 мест '+ IntToStr(KolPasInBus2));
If KolPasInBus2<>0 then begin  // Если 1 то высаживать
f:= false;

While f=false do begin
randomize;
rand:= random(KolPasInBus2+1); // cколько всего высаживать
If rand=0 then f:= false else f:= true;
                 end;
count:=rand;
St:='';
For i:=1 to 5 do
 For j:=1 to 2 do

  If ( ( j=1)   and ( Mas2Sm[i,j]=2) And(Count<>0)
   and (Mas2Sm[i,j+1]=2) ) then begin

       Mas2Sm[i,j+1]:= -1;
       Mas2Sm[i,j]:= -1;
       St:= IntToStr(i)+IntToStr(j);
       DelSmFrSb(St);

       St:='';
       St:= IntToStr(i)+IntToStr(j+1);
       DelSmFrSb(St);
       st:='';
       Count:=Count-1;


                                end;



               end;




//TTESSTT;
end;

// ------------------Высадка всех на конечной ------------------------------------



/// Генерация человек на переходе
procedure GenpasOnColor;
var
Kol2Sm: integer; //Кол-во групп по 2 чел

i: integer;
f: boolean;
begin


If ( (form1.Edit4.Text='') and (form1.Edit5.Text='') ) then begin
// Двойные
randomize;
Kol2Sm:= random(6);
KolPas2:=Kol2Sm*2;
// Одинарные
F:=false;
While f=false do begin
randomize;
KolPas1:= random(15);
If (KolPas1 <= (15-KolPas2)) then f:= true else f:= false;
form1.Edit4.Text:= IntToStr(kolPas1);
form1.Edit5.Text:= IntToStr(KolPas2);
                 end;
                                                                              end else
end;

//------------------------------------------------------------------------------
procedure TForm1.BitBtn1Click(Sender: TObject);
var
st: string;
Ikord , JKord :integer;
begin
//Ikord := form1.Image2.Left;
//JKord := form1.Image2.Top;
//Sdvig;// (Ikord , JKord );
//GenerPasOnSt
{
 delay(1000);
form1.SpeedButton1.Glyph.Canvas.FillRect(form1.SpeedButton1.ClientRect);  }
//st:= IntToStr(21);
//sootv(st,0);
//st:= IntToStr(22);
//sootv(st,1);
//OcherNaPasadky;
//form1.ImageList1.GetBitmap(0,form1.SpeedButton1.Glyph);
//
//Form1.SpeedButton1.Glyph.Canvas.FloodFill (90,90,clBtnFace,fsSurface);
//Form1.SpeedButton1.Glyph.Canvas.Refresh;
//Image1.Canvas.FloodFill (90,90,clBtnFace,fsSurface);
//form1.SpeedButton1.Glyph.Canvas.FillRect(form1.SpeedButton1.ClientRect);
//Form1.SpeedButton1.Glyph.Free;
//Form1.SpeedButton1.Glyph.Create;
//Form1.SpeedButton1.Glyph.Canvas.Refresh;
//Form1.SpeedButton1.Glyph.LoadFromFile('../1.bmp');
//delay(1000);
//form1.ImageList1.GetBitmap(0,form1.SpeedButton1.Glyph);
//
 ///delay(1000);
 //If form1.Edit3.Color=ClRed  then form1.Edit3.Color:= ClLime ;
  end;
//------------------------------------------------------------------------------


//=========================================WndProc==============================

 procedure TForm1.WndProc (var Message : TMessage);
var
res: boolean;
begin // of proc wnd
 

 res:= false;

 If message.Msg=msgSIMPR then
     begin   //2begin
   
//--------------------------------------------------------------------------
                                 //   YSLOVIYA
//--------------------------------------------------------------------------
     If message.WParamHi=0 then
       begin

 case  message.WParamLo of               //vibor tabl yslovii     BIG
  



//------------------------------tablica  1  ------------------------------------

 1: begin   // 1
       //        Showmessage ('Табл 1 услов');
           case message.LParam of



      1:  Begin
          If form1.Image2.Visible= false then res:= true;
        //  If res=true then Showmessage ('Нет Автобуса');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т1 у1='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      2:  begin
          IF Kolkrug =0 then res:=true;
         // If res=true then Showmessage ('Пройденно 0 кругов');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т1 у2='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      3:  Begin
          If (KolKrug>=1) and (KolKrug<6) then res:= true;
         // If res=true then Showmessage ('1<=Кол-во кругов<4');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т1 у3='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      4:  Begin
          If  HodBus=true then res:= true;
         // If res=true then  Showmessage ('Ход Автобуса');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т1 у4='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      5:  Begin
          If HodPesh= true then res:= true;
          //If res=true then Showmessage ('Ход Пешехода');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т1 у5='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;
      6:  Begin
          If Kolkrug=6 then res := true;
         // If res=true then Showmessage ('Пошел 4 круг');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т1 у6='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

     end; // of case
    end; // end 1


//------------------------------ tablica  2-------------------------------------

 2: begin  //2
       //  Showmessage ('Таблица 2 услов');
      case  message.LParam of

       1: Begin

          If ( (form1.Image2.Left=814) and (form1.Image2.Top= 64) ) then res:= true;
          //If res=true then Showmessage ('Автобус на старте');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у1='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       2: Begin

          If  NomberSt>=1 then res:= true;
         // If res=true then Showmessage ('Автобус у Остановки');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у2='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       3: Begin

            If ( (form1.Edit1.Text<>'') and (Form1.Edit2.Text<>'') ) then res:= true;
         //  If res=true then Showmessage ('Люди на остановке построенны');
           if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
           ListBox1.Items.Add('т2 у3='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       4: Begin

           If BusVisPas = true then res:= true;
         //If res=true then Showmessage ('Автобус высадил людей');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у4='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       5: Begin

           If groupKol= 1 then res:= true;
         // If res=true then Showmessage ('В очереди 1 человек');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у5='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       6: Begin

           If groupKol= 2 then res:= true;
         //If res=true then Showmessage ('В очереди 2 человека');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у6='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       7: Begin

           KolSitPlase ;
           case groupKol of
           1:  If( KolPlInB1>=1) or (KolPlInB2>=1) then res:= true;
           2:  If KolPlInB2>=2 then res:= true

           else ;

           end;

         // Showmessage('Число Своб мест > гр в очереди');
          
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у7='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

         8: Begin

            If ( (form1.Image2.Left= 94) and (form1.Image2.Top= 424)   ) then res:= true;
          // If res=true then Showmessage ('Автобус у светофора');

           {    }
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у8='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

         9: Begin

           If (form1.Edit3.Color= ClRed) then res:=  true;
          // If res=true then Showmessage ('Свет светофора красный');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у9='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;
          10: Begin

          If ( (form1.Image2.Left= -86) and (form1.Image2.Top= 514)   ) then res:= true;
         // If res=true then Showmessage ('Автобус на финише');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т2 у9='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;


      end; // end of case
    end; //  end 2


//-------------------------------tablica  3-------------------------------------
        3: begin  //3
                  //    Showmessage ('Табл 3 услов');
      case  message.LParam of

       1: begin

           If GoGame = true then res:= true;
           //If res=true then Showmessage('Начало игры');
           gogame:= false;
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т3 у1='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
           end;
       2: begin

          If form1.Edit3.Color=clRed then res:= true;
         // If res=true then Showmessage('Красный цвет светофора');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т3 у2='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

       3: begin


          If Timer >= 10 then res:=true;
        //  If res=true then Showmessage('сменить цвет светофора');
        //  Showmessage('Timer= ' + IntToStr(Timer));
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('т3 у3='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

           end; // end of case
    end; //  end of 3


//------------------------------------End of ysloviya---------------------------

           end; // of  big case
         end; // end of   //vibor tabl yslovii



//------------------------------------------------------------------------------
                                 //   DEISTVIYA
//------------------------------------------------------------------------------


 if message.WParamHi=1 then
   Begin
       case message.WParamLo of  // case na tabl
//----------------------tablica 1 ----------------------------------------------
        1:  begin      //1
     //   Showmessage ('Табл 1 Действ');
              case message.LParam of
            1: begin
            Delay(100);
               Start;
               // Showmessage (' Автобус на старт');
                ListBox1.Items.Add('т1 д1='+tmpstr);
               end;

            2: begin

                HodPesh:= true;
               // Showmessage ('Отдать ход Пеш');
                HodBus:= false;
                ListBox1.Items.Add('т1 д2='+tmpstr);
               end;
            3: begin

                HodBus:= true;
              //  Showmessage ('Отдать ход Авт');
                HodPesh:= false;
                ListBox1.Items.Add('т1 д3='+tmpstr);
               end;
            4: begin
                GoGame:= true;
                inc(kolKrug);
               //   Showmessage ('Сообщить о начале игры');
                ListBox1.Items.Add('т1 д4='+tmpstr);
               end;

              end; // end of case **
            end;     // end of 1


//----------------------tablica 2-------------------------------------------------


     2:  begin      //2
          //   Showmessage ('Табл 2 действ');
              case message.LParam of//** {message.Lparam of }
                1: Begin
                Delay(1000);
                   Sdvig;// (Ikord, JKord );
                  //Showmessage('Сдвиг до след остановкки ');
                ListBox1.Items.Add('т2 д1');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                2: Begin
                Delay(100);
                   GenerPasOnSt( kolPas1, kolPas2);
                 //  Showmessage('Сгенерить людей на остановке');
                ListBox1.Items.Add('т2 д2');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                3: Begin
                Delay(100);
                    GoOut( BusVisPas);
                   //  Showmessage('Высадить людей');
                ListBox1.Items.Add('т2 д3');
          ListBox1.ItemIndex:=ListBox1.Count-1;

                   End;

                4:
                    Begin
                    //Delay(10);
                     If ((StrToInt (form1.Edit1.Text)>0) or ( StrToInt(Form1.Edit2.Text)>0)) then begin
                     OcherNaPasadky;
                  //  Showmessage('Определить очередь  '+ IntToStr(GroupKol))
                                                                            end;
                  If ((StrToInt (form1.Edit1.Text)=0) and ( StrToInt(Form1.Edit2.Text)=0)) then begin
                      GroupKol:=35;
                  //    Showmessage('очередь=  '+ IntToStr(GroupKol)) ;
                                                                                                end;

                ListBox1.Items.Add('т2 д4');
              ListBox1.ItemIndex:=ListBox1.Count-1;
                        End;

                5: Begin

                      Delay(1000);
                     GoSitPlaseOne;
                     KolSitPlase;
                   //  Showmessage (IntToStr(KolPlInB1));
                  //   Showmessage('Посадить группу из 1 ');
                  //   Showmessage (IntToStr(KolPlInB1));
                   {GetOutAll;  Inc(KolKrug);
                   Showmessage('Высадить всех');
                    Inc (KolKrug); }
                ListBox1.Items.Add('т2 д5');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;


                6: Begin
                  Delay(1000);
                 GoSitDoubl;
                  KolSitPlase;
                  // Showmessage('Посадить группу из 2 ');
                  // Showmessage(IntToStr(KolPlInB2));
                ListBox1.Items.Add('т2 д6');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                7: Begin
                Delay(10);
                   form1.Edit1.Text:='';
                   form1.Edit2.Text:='';
                 //  Showmessage('Убрать пасажиров с остановки');
                   {HodPesh:= true;
                   Showmessage ('Отдать ход Пеш');
                   HodBus:= false; }
                ListBox1.Items.Add('т2 д7');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;
                8: Begin
                   delay(100);
                           BusVisPas:= false;
               //       Showmessage ('Пометить что пас не высаженны');
                   ListBox1.Items.Add('т2 д8');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                    End;

               9: Begin

                  HodPesh:= true;
                  // Showmessage ('Отдать ход Пеш');
                   HodBus:= false;
                ListBox1.Items.Add('т2 д9');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;


                 10: Begin
                 Delay(1000);
                    GetOutAll;
               //    Showmessage ('Высадить всех');
                ListBox1.Items.Add('т2 д10');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                 11: Begin
                 Delay(100);
                    Start;
                    //Showmessage ('Автобус на старт');
                ListBox1.Items.Add('т2 д11');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;


              end; // end of case **
         end;     // end of 2


//----------------------tablica 3---------------------------------------------

        3:         begin      //3 tabl
          //      Showmessage ('Табл 3 действий');
              case message.LParam of//** {message.Lparam of}
              1: Begin
                  delay(100);
                  If form1.Edit3.Color=ClRed  then form1.Edit3.Color:= ClLime else

                   form1.Edit3.Color:= ClRed;

                   timer:=1;


           //     Showmessage('Задать цвет светофору') ;
                 GoGame:= false;

                             //     end;
                 End;


              2: Begin
             //  delay(1000);
                 Form1.Edit4.Text:='';
                 Form1.Edit5.Text:='';
                 //Showmessage('Позволить перейти');
                 End;


              3: Begin
              delay(100);
                 Inc(timer);
              //    Showmessage('Timer= ' + IntToStr(Timer));
                 HodBus:= true;
                 //Showmessage ('Отдать ход Автобусу');
                 HodPesh:= false;

                 End;

              4 : Begin
               //delay(1000);
                 GenpasOnColor;
                // Showmessage('Поставить Людей у светофора');

                 End;


              end; // end of case **
        end;     // end of 1 tab3


//------------------------------------------End Of Deistviya--------------------
end;
    res:=true;
 end;

       if res then message.result:=1 else
        message.result:=0;

    end // end of case  na DEISTVIYA
     else inherited  WndProc(Message);
     end; // end // of proc wnd








//==================================End Of WndProc==============================


procedure TForm1.FormCreate(Sender: TObject);
begin
form1.Image2.Visible:= false;
gogame:= true;
kolKrug:=0;
timer:=1;
form1.Edit3.Color:= Cllime;
form1.StringGrid1.Visible:= false;
MsgSIMPR:= RegisterWindowMessage(MESSAGE_STR);
end;

end.
