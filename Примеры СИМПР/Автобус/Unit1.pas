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
  KolPasInSt : integer; //���-�� ������� �� �������
  KolPAsOutFromBus : integer; //���-�� ������� ��������
  KolKrug : Integer;
  HodBus  : Boolean;
  HodPesh : Boolean;
  NomberSt: Integer;
  KolPas : integer;
  Group : integer;  // 1 ���� 1 ��� 0 ���� ����
  GroupKol: integer; // ���-�� ����� � ����� �� �������
  ColorS : boolean; // ���� ���������
  RandomColorS : Integer; // ������ ��� ���������
  GoGame: boolean;
  Mas2Sm : array [1..5,1..2] of integer;  // ������ ������� �������
  MAs1Sm : array [11..15] of integer; //������ ������� �����������
  jrebii : integer; // �� �� 1 ��� 2 ���
  BusVisPas: boolean; // ���� ������� �� true
  KolPlInB1,KolPlInB2 : integer;    // c�������� ����� � ���
  curdir : String;
 KolPasInBus1,KolPasInBus2 : integer;

 // BasVisPas : boolean ; // true ���� ������� ���������, ������ �����
  kolPas1, kolPas2 : integer; // �������  ���������
  Svet: boolean;
  Timer : integer;
  tmpStr : String;
//  Sit1,Sit2 : integer; // ���-�� ������� ����
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

//---------------------- ������� ���� ����--------------------------------------
Procedure KolSitPlase ;
var
i,j:integer;

begin
KolPlInB1:=0;
KolPlInB2:=0;
// ��������
For i:=11 to 15 do
If Mas1Sm[i]=-1 then Inc(KolPlInB1);


// ����
For i:=1 to 5 do
 for j:=1 to 2 do   begin
    If ( ( j mod 2 <>0)   and ( Mas2Sm[i,j]=-1)
    and (Mas2Sm[i,j+1]=-1) ) then   KolPlInB2:=KolPlInB2+2 ;

  If Mas2Sm[i,j]=-1 then  Inc(KolPlInB1);
                    end;
//Showmessage('���� '+ IntToStr(KolPlInB1)+ '���� '+IntToStr(KolPlInB2));
end;
// �������� �������� ��� �������
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
 // ----------���������� ��������� ��������� �� �������--------------------------
procedure GenerPasOnSt( var kolPas1: integer; var kolPas2: integer);
var
Kol2Sm: integer; //���-�� ����� �� 2 ���

i: integer;
f: boolean;
begin
// �������
randomize;
Kol2Sm:= random(6);
KolPas2:=Kol2Sm*2;
// ���������
F:=false;
While f=false do begin
randomize;
KolPas1:= random(15);
If (KolPas1 <= (15-KolPas2)) then f:= true else f:= false;
form1.Edit1.Text:= IntToStr(kolPas1);
form1.Edit2.Text:= IntToStr(KolPas2);
                 end;

// ����� Edit1 Edit2
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
// ��������

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
{ // �������� � ������� ����


 Mas2Sm[i,j]:=-1;
 St:=IntToStr(j);
 DelSmFrSb(St);
 St:='';
 Count:=count-1;
                       end;
// ����

For i:=1 to 5 do
 For j:=1 to 2 do

  If ( Mas2Sm[i,j]=2) then   begin

       Mas2Sm[i,j]:= -1;
       St:= IntToStr(i)+IntToStr(j);
       DelSmFrSb(St);


                                end;  }



//TTESSTT;
end;
//------------------------��������� ������� ���������� ���������---------------

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









// ----------����� ��������������� Speedbutton ----------------------------------
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



//--------------����������� ������ �� �������-----------------------------------
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
 group:= random(3);   // 1 ���� ���� 0 ���� �������
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
//Showmessage ('������= '+IntToStr(groupKol));
 end;

//------------------------------- ������� � ������� ���� �� 2-------------------
procedure GoSitDoubl;
Var
numi,numj : integer;
i, j: integer;
st : string;
begin


// ���� �� �� 2
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
   sootv(st,1);// ������������� ��������
   st:='';

Form1.Edit2.Text:= IntToStr( StrToInt(form1.Edit2.text) -2  );
                                         end;


//TTESSTT;

end;

// -----------------------������� � ������� ����� �� 1 ���-��
procedure GoSitPlaseOne;
var
i,j : integer;
st : string;
numi,numj : integer;
begin

numi:=-1;
numj := -1;
// ��������� ���������
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

// ��������� ������� �����
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

//-----------------------------�������� ������� ������ ������� ����-------------

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


//------------------------ ������� ���������------------------------------------

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

//------------------------- ������� ��������
  //


KolPasInBus1:= 15 -  KolPlInB1;
//Showmessage('���-�� ������� 1 ���� ' +IntToStr(KolPasInBus1));
If KolPasInBus1<>0 then begin // ���� 1 �� ����������
f:= false;
While f=false do begin
randomize;
rand:= random(KolPasInBus1+1); // c������ ����� ����������
If rand=0 then f:= false else f:= true;
                 end;

count:=rand;
St:='';
// ������� � ��������� ���� ��������
for j:=11 to High(Mas1Sm) do
If ( (Mas1sm[j]=1) and (count<>0)) then  begin
Mas1Sm[j]:=-1;
St:=IntToStr(j)+'o';
DelSmFrSb(St);
St:='';
Count:=count-1;
                                         end;
// ������� � ������� ��������
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

// -----------------------------------������� ���------------------------------


KolPasInBus2:= 10 -  KolPlInB2;
//Showmessage('���-�� ������� 2 ���� '+ IntToStr(KolPasInBus2));
If KolPasInBus2<>0 then begin  // ���� 1 �� ����������
f:= false;

While f=false do begin
randomize;
rand:= random(KolPasInBus2+1); // c������ ����� ����������
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

// ------------------������� ���� �� �������� ------------------------------------



/// ��������� ������� �� ��������
procedure GenpasOnColor;
var
Kol2Sm: integer; //���-�� ����� �� 2 ���

i: integer;
f: boolean;
begin


If ( (form1.Edit4.Text='') and (form1.Edit5.Text='') ) then begin
// �������
randomize;
Kol2Sm:= random(6);
KolPas2:=Kol2Sm*2;
// ���������
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
       //        Showmessage ('���� 1 �����');
           case message.LParam of



      1:  Begin
          If form1.Image2.Visible= false then res:= true;
        //  If res=true then Showmessage ('��� ��������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�1 �1='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      2:  begin
          IF Kolkrug =0 then res:=true;
         // If res=true then Showmessage ('��������� 0 ������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�1 �2='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      3:  Begin
          If (KolKrug>=1) and (KolKrug<6) then res:= true;
         // If res=true then Showmessage ('1<=���-�� ������<4');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�1 �3='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      4:  Begin
          If  HodBus=true then res:= true;
         // If res=true then  Showmessage ('��� ��������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�1 �4='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

      5:  Begin
          If HodPesh= true then res:= true;
          //If res=true then Showmessage ('��� ��������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�1 �5='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;
      6:  Begin
          If Kolkrug=6 then res := true;
         // If res=true then Showmessage ('����� 4 ����');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�1 �6='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

     end; // of case
    end; // end 1


//------------------------------ tablica  2-------------------------------------

 2: begin  //2
       //  Showmessage ('������� 2 �����');
      case  message.LParam of

       1: Begin

          If ( (form1.Image2.Left=814) and (form1.Image2.Top= 64) ) then res:= true;
          //If res=true then Showmessage ('������� �� ������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �1='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       2: Begin

          If  NomberSt>=1 then res:= true;
         // If res=true then Showmessage ('������� � ���������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �2='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       3: Begin

            If ( (form1.Edit1.Text<>'') and (Form1.Edit2.Text<>'') ) then res:= true;
         //  If res=true then Showmessage ('���� �� ��������� ����������');
           if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
           ListBox1.Items.Add('�2 �3='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       4: Begin

           If BusVisPas = true then res:= true;
         //If res=true then Showmessage ('������� ������� �����');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �4='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       5: Begin

           If groupKol= 1 then res:= true;
         // If res=true then Showmessage ('� ������� 1 �������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �5='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       6: Begin

           If groupKol= 2 then res:= true;
         //If res=true then Showmessage ('� ������� 2 ��������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �6='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

       7: Begin

           KolSitPlase ;
           case groupKol of
           1:  If( KolPlInB1>=1) or (KolPlInB2>=1) then res:= true;
           2:  If KolPlInB2>=2 then res:= true

           else ;

           end;

         // Showmessage('����� ���� ���� > �� � �������');
          
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �7='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

         8: Begin

            If ( (form1.Image2.Left= 94) and (form1.Image2.Top= 424)   ) then res:= true;
          // If res=true then Showmessage ('������� � ���������');

           {    }
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �8='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;

         9: Begin

           If (form1.Edit3.Color= ClRed) then res:=  true;
          // If res=true then Showmessage ('���� ��������� �������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �9='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;
          10: Begin

          If ( (form1.Image2.Left= -86) and (form1.Image2.Top= 514)   ) then res:= true;
         // If res=true then Showmessage ('������� �� ������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�2 �9='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          End;


      end; // end of case
    end; //  end 2


//-------------------------------tablica  3-------------------------------------
        3: begin  //3
                  //    Showmessage ('���� 3 �����');
      case  message.LParam of

       1: begin

           If GoGame = true then res:= true;
           //If res=true then Showmessage('������ ����');
           gogame:= false;
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�3 �1='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
           end;
       2: begin

          If form1.Edit3.Color=clRed then res:= true;
         // If res=true then Showmessage('������� ���� ���������');
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�3 �2='+tmpstr);
          ListBox1.ItemIndex:=ListBox1.Count-1;
          end;

       3: begin


          If Timer >= 10 then res:=true;
        //  If res=true then Showmessage('������� ���� ���������');
        //  Showmessage('Timer= ' + IntToStr(Timer));
          if res = true then tmpStr := 'TRUE' else tmpStr := 'FALSE';
          ListBox1.Items.Add('�3 �3='+tmpstr);
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
     //   Showmessage ('���� 1 ������');
              case message.LParam of
            1: begin
            Delay(100);
               Start;
               // Showmessage (' ������� �� �����');
                ListBox1.Items.Add('�1 �1='+tmpstr);
               end;

            2: begin

                HodPesh:= true;
               // Showmessage ('������ ��� ���');
                HodBus:= false;
                ListBox1.Items.Add('�1 �2='+tmpstr);
               end;
            3: begin

                HodBus:= true;
              //  Showmessage ('������ ��� ���');
                HodPesh:= false;
                ListBox1.Items.Add('�1 �3='+tmpstr);
               end;
            4: begin
                GoGame:= true;
                inc(kolKrug);
               //   Showmessage ('�������� � ������ ����');
                ListBox1.Items.Add('�1 �4='+tmpstr);
               end;

              end; // end of case **
            end;     // end of 1


//----------------------tablica 2-------------------------------------------------


     2:  begin      //2
          //   Showmessage ('���� 2 ������');
              case message.LParam of//** {message.Lparam of }
                1: Begin
                Delay(1000);
                   Sdvig;// (Ikord, JKord );
                  //Showmessage('����� �� ���� ���������� ');
                ListBox1.Items.Add('�2 �1');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                2: Begin
                Delay(100);
                   GenerPasOnSt( kolPas1, kolPas2);
                 //  Showmessage('��������� ����� �� ���������');
                ListBox1.Items.Add('�2 �2');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                3: Begin
                Delay(100);
                    GoOut( BusVisPas);
                   //  Showmessage('�������� �����');
                ListBox1.Items.Add('�2 �3');
          ListBox1.ItemIndex:=ListBox1.Count-1;

                   End;

                4:
                    Begin
                    //Delay(10);
                     If ((StrToInt (form1.Edit1.Text)>0) or ( StrToInt(Form1.Edit2.Text)>0)) then begin
                     OcherNaPasadky;
                  //  Showmessage('���������� �������  '+ IntToStr(GroupKol))
                                                                            end;
                  If ((StrToInt (form1.Edit1.Text)=0) and ( StrToInt(Form1.Edit2.Text)=0)) then begin
                      GroupKol:=35;
                  //    Showmessage('�������=  '+ IntToStr(GroupKol)) ;
                                                                                                end;

                ListBox1.Items.Add('�2 �4');
              ListBox1.ItemIndex:=ListBox1.Count-1;
                        End;

                5: Begin

                      Delay(1000);
                     GoSitPlaseOne;
                     KolSitPlase;
                   //  Showmessage (IntToStr(KolPlInB1));
                  //   Showmessage('�������� ������ �� 1 ');
                  //   Showmessage (IntToStr(KolPlInB1));
                   {GetOutAll;  Inc(KolKrug);
                   Showmessage('�������� ����');
                    Inc (KolKrug); }
                ListBox1.Items.Add('�2 �5');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;


                6: Begin
                  Delay(1000);
                 GoSitDoubl;
                  KolSitPlase;
                  // Showmessage('�������� ������ �� 2 ');
                  // Showmessage(IntToStr(KolPlInB2));
                ListBox1.Items.Add('�2 �6');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                7: Begin
                Delay(10);
                   form1.Edit1.Text:='';
                   form1.Edit2.Text:='';
                 //  Showmessage('������ ��������� � ���������');
                   {HodPesh:= true;
                   Showmessage ('������ ��� ���');
                   HodBus:= false; }
                ListBox1.Items.Add('�2 �7');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;
                8: Begin
                   delay(100);
                           BusVisPas:= false;
               //       Showmessage ('�������� ��� ��� �� ���������');
                   ListBox1.Items.Add('�2 �8');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                    End;

               9: Begin

                  HodPesh:= true;
                  // Showmessage ('������ ��� ���');
                   HodBus:= false;
                ListBox1.Items.Add('�2 �9');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;


                 10: Begin
                 Delay(1000);
                    GetOutAll;
               //    Showmessage ('�������� ����');
                ListBox1.Items.Add('�2 �10');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;

                 11: Begin
                 Delay(100);
                    Start;
                    //Showmessage ('������� �� �����');
                ListBox1.Items.Add('�2 �11');
          ListBox1.ItemIndex:=ListBox1.Count-1;
                   End;


              end; // end of case **
         end;     // end of 2


//----------------------tablica 3---------------------------------------------

        3:         begin      //3 tabl
          //      Showmessage ('���� 3 ��������');
              case message.LParam of//** {message.Lparam of}
              1: Begin
                  delay(100);
                  If form1.Edit3.Color=ClRed  then form1.Edit3.Color:= ClLime else

                   form1.Edit3.Color:= ClRed;

                   timer:=1;


           //     Showmessage('������ ���� ���������') ;
                 GoGame:= false;

                             //     end;
                 End;


              2: Begin
             //  delay(1000);
                 Form1.Edit4.Text:='';
                 Form1.Edit5.Text:='';
                 //Showmessage('��������� �������');
                 End;


              3: Begin
              delay(100);
                 Inc(timer);
              //    Showmessage('Timer= ' + IntToStr(Timer));
                 HodBus:= true;
                 //Showmessage ('������ ��� ��������');
                 HodPesh:= false;

                 End;

              4 : Begin
               //delay(1000);
                 GenpasOnColor;
                // Showmessage('��������� ����� � ���������');

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
