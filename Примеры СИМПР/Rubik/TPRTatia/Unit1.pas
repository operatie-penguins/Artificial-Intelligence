unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, OpenGL, Menus, AppEvnts, ComCtrls, Buttons;

var test:integer;

const
  MESSAGE_STR='RubicMsg';
  No=2;
  Yes=3;
type
  TCubeColor = 1..6;
  TCubeLocation = 1..6;
  TCubArray = array [1..6,1..3,1..3] of TCubeColor;
  TColorArray = array [1..6] of TColor;
  TRotateDirection = (_left,_right,_up,_down,_CW,_CCW,
                       _left1,_left2,_left3,_right1,_right2,_right3,
                       _up1,_up2,_up3,_down1,_down2,_down3,
                       _CW1,_CW2,_CW3,_CCW1,_CCW2,_CCW3);
  TCube = class
  private
   //REMARKS 1 - top
   //        2 - bottom
   //        3 - left
   //        4 - right
   //        5 - up
   //        6 - down
   cub: TCubArray;
  public
   TestCube:TCubArray;
   procedure GetTest;
   procedure PutTest;
   function GetColor(l:TCubeLocation; i,j:integer):TCubeColor;
   function CheckEnd1():boolean; //верхний крест1
   function CheckEnd2():boolean; //верх
   function CheckEnd3():boolean; //2*верх
   function CheckEnd3d():boolean; //2*низ
   function CheckEnd4():boolean; //верхний крест2 (не фикс)
   function CheckEnd6():boolean; //верх (не фикс)
   procedure ColorToLocation(c1:TCubeColor;c2:TCubeColor;var l1:TCubeLocation; var l2:TCubeLocation); overload;
   procedure ColorToLocation(c1:TCubeColor;c2:TCubeColor;c3:TCubeColor;
             var l1:TCubeLocation; var l2:TCubeLocation; var l3:TCubeLocation);overload;
   constructor Create;
   procedure Rotate(direction:TRotateDirection);
   procedure Reset;
   procedure RandomizeCube;overload;
   procedure RandomizeCube(steps:longint);overload;
   property Cube : TCubArray read cub;
  end;

  TGLCube = class (TCube)
  private
    hrc: HGLRC;
    dc:HDC;
    h:HWND;
    color:TColorArray;
    bkColor,lnColor:TColor;
    rotSpeed:real;
    ang:real;
    dx,dy,dz:integer;
    rd:array [1..3,1..3] of boolean;
    procedure SetDCPixelFormat (hdc : HDC);
  public
    constructor Create(handle:HWND);
    destructor Dispose;
    procedure Draw;
    procedure ColorToGl(c:TColor;var R,G,B:GLFloat);
    property colors : TColorArray read color write color;
    property backgroundColor: TColor read bkColor write bkColor;
    property axisColor: TColor read lnColor write lnColor;
    property animationSpeed: real read rotSpeed write rotSpeed;
    procedure SetDefaultColors;
    procedure SetViewPort(left,top,right,bottom:integer);
    procedure RotateImage(anx,any,anz:double);
    procedure ResetImage;
    procedure AnimatedRotate(direction:TRotateDirection);
    procedure Animate;
  end;

  TCubeForm = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    PopupMenu1: TPopupMenu;
    right1: TMenuItem;
    up1: TMenuItem;
    down1: TMenuItem;
    CW1: TMenuItem;
    CCW1: TMenuItem;
    left1: TMenuItem;
    N1: TMenuItem;
    left11: TMenuItem;
    left21: TMenuItem;
    left31: TMenuItem;
    right11: TMenuItem;
    right21: TMenuItem;
    right31: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    up11: TMenuItem;
    up21: TMenuItem;
    up31: TMenuItem;
    N4: TMenuItem;
    down11: TMenuItem;
    down21: TMenuItem;
    down31: TMenuItem;
    N5: TMenuItem;
    CW11: TMenuItem;
    CW21: TMenuItem;
    CW31: TMenuItem;
    N6: TMenuItem;
    CCW11: TMenuItem;
    CCW21: TMenuItem;
    CCW31: TMenuItem;
    ApplicationEvents1: TApplicationEvents;
    TrackBar1: TTrackBar;
    TrackBar2: TTrackBar;
    TrackBar3: TTrackBar;
    Label1: TLabel;
    Button5: TButton;
    TrackBar4: TTrackBar;
    Button6: TButton;
    Label4: TLabel;
    Label5: TLabel;
    Memo1: TMemo;
    Panel1: TPanel;
    procedure Button4Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure left1Click(Sender: TObject);
    procedure right1Click(Sender: TObject);
    procedure up1Click(Sender: TObject);
    procedure down1Click(Sender: TObject);
    procedure CW1Click(Sender: TObject);
    procedure CCW1Click(Sender: TObject);
    procedure left11Click(Sender: TObject);
    procedure left21Click(Sender: TObject);
    procedure left31Click(Sender: TObject);
    procedure right11Click(Sender: TObject);
    procedure right21Click(Sender: TObject);
    procedure right31Click(Sender: TObject);
    procedure up11Click(Sender: TObject);
    procedure up21Click(Sender: TObject);
    procedure up31Click(Sender: TObject);
    procedure down11Click(Sender: TObject);
    procedure down21Click(Sender: TObject);
    procedure down31Click(Sender: TObject);
    procedure CW11Click(Sender: TObject);
    procedure CW21Click(Sender: TObject);
    procedure CW31Click(Sender: TObject);
    procedure CCW11Click(Sender: TObject);
    procedure CCW21Click(Sender: TObject);
    procedure CCW31Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure ApplicationEvents1Idle(Sender: TObject; var Done: Boolean);
    procedure Button5Click(Sender: TObject);
    procedure TrackBar4Change(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure WndProc(var Message: TMessage);override;
  private
    { Private declarations }
  public
    { Public declarations }
    cube:TGLCube;
    t:double;
    msgSIMPR:UINT;
  end;

var
  CubeForm: TCubeForm;

implementation

uses Unit2;

{$R *.dfm}

///////////////////// TCube Class  ///////////////////////////////
procedure TCube.GetTest;
var i,j,k:integer;
begin
 for i:=1 to 6 do
  for j:=1 to 3 do
   for k:=1 to 3 do TestCube[i][j][k]:=Cube[i][j][k];
end;

procedure TCube.PutTest;
var i,j,k:integer;
begin
 for i:=1 to 6 do
  for j:=1 to 3 do
   for k:=1 to 3 do Cub[i][j][k]:=TestCube[i][j][k];
end;

function TCube.GetColor(l:TCubeLocation; i,j:integer):TCubeColor;
begin
 GetColor:=cube[l][i][j];
end;

function TCube.CheckEnd1():boolean; //верхний крест1
var c:TCubeColor;
begin
 c:=cube[5][2][2];
 if (cube[5][2][1]=c)and(cube[5][1][2]=c)and(cube[5][2][3]=c)and(cube[5][3][2]=c)and
    (cube[1][2][1]=cube[1][2][2])and(cube[3][2][1]=cube[3][2][2])and
    (cube[2][2][1]=cube[2][2][2])and(cube[4][2][1]=cube[4][2][2]) then
    CheckEnd1:=true
 else CheckEnd1:=false;

end;

function TCube.CheckEnd2():boolean; //верх
var cu,cf,cl,cr,cb:TCubeColor;
begin
 cu:=cube[5][2][2];
 cf:=cube[1][2][2];
 cl:=cube[3][2][2];
 cr:=cube[4][2][2];
 cb:=cube[2][2][2];

 if (cube[1][1][1]=cf)and(cube[5][1][3]=cu)and(cube[3][1][1]=cl)and
    (cube[2][1][1]=cb)and(cube[5][1][1]=cu)and(cube[3][3][1]=cl)and
    (cube[2][3][1]=cb)and(cube[5][3][1]=cu)and(cube[4][3][1]=cr)and
    (cube[1][3][1]=cf)and(cube[5][3][3]=cu)and(cube[4][1][1]=cr)
 then
      CheckEnd2:=true
 else CheckEnd2:=false;

end;

function TCube.CheckEnd3():boolean; //2*верх
var cu,cf,cl,cr,cb:TCubeColor;
begin
 cf:=cube[1][2][2];
 cl:=cube[3][2][2];
 cr:=cube[4][2][2];
 cb:=cube[2][2][2];

 if (cube[1][1][2]=cf)and(cube[1][3][2]=cf)and
    (cube[2][1][2]=cb)and(cube[2][3][2]=cb)and
    (cube[3][1][2]=cl)and(cube[3][3][2]=cl)and
    (cube[4][1][2]=cr)and(cube[4][3][2]=cr) then
    CheckEnd3:=true
 else CheckEnd3:=false;

end;

function TCube.CheckEnd3d():boolean; //2*низ
var cd,cu,cf,cl,cr,cb:TCubeColor;
begin
 cf:=cube[1][2][2];
 cl:=cube[3][2][2];
 cr:=cube[4][2][2];
 cb:=cube[2][2][2];
 cd:=cube[6][2][2];

 if (cube[1][2][3]=cf)and(cube[6][2][3]=cd)and
    (cube[2][2][3]=cb)and(cube[6][2][1]=cd)and
    (cube[3][2][3]=cl)and(cube[6][1][2]=cd)and
    (cube[4][2][3]=cr)and(cube[6][3][2]=cd)and


    (cube[1][1][3]=cf)and(cube[6][1][3]=cd)and(cube[3][1][3]=cl)and
    (cube[2][1][3]=cb)and(cube[6][1][1]=cd)and(cube[3][3][3]=cl)and
    (cube[2][3][3]=cb)and(cube[6][3][1]=cd)and(cube[4][3][3]=cr)and
    (cube[1][3][3]=cf)and(cube[6][3][3]=cd)and(cube[4][1][3]=cr)and

    (cube[1][1][2]=cf)and(cube[1][3][2]=cf)and
    (cube[2][1][2]=cb)and(cube[2][3][2]=cb)and
    (cube[3][1][2]=cl)and(cube[3][3][2]=cl)and
    (cube[4][1][2]=cr)and(cube[4][3][2]=cr) then
    CheckEnd3d:=true
 else CheckEnd3d:=false;

end;

function TCube.CheckEnd4():boolean; //верхний крест2 (не фикс)
var cu,cf,cl,cr,cb:TCubeColor;
begin
 cf:=cube[1][2][2];
 cl:=cube[3][2][2];
 cr:=cube[4][2][2];
 cb:=cube[2][2][2];
 cu:=cube[5][2][2];

 if ((cube[1][2][1]=cf)and(cube[5][2][3]=cu)or(cube[1][2][1]=cu)and(cube[5][2][3]=cf))and
    ((cube[2][2][1]=cb)and(cube[5][2][1]=cu)or(cube[2][2][1]=cu)and(cube[5][2][1]=cb))and
    ((cube[3][2][1]=cl)and(cube[5][1][2]=cu)or(cube[3][2][1]=cu)and(cube[5][1][2]=cl))and
    ((cube[4][2][1]=cr)and(cube[5][3][2]=cu)or(cube[4][2][1]=cu)and(cube[5][3][2]=cr))then
    CheckEnd4:=true
 else CheckEnd4:=false;

end;

function TCube.CheckEnd6():boolean; //верх (не фикс)
var cu,cf,cl,cr,cb:TCubeColor;
begin
 cu:=cube[5][2][2];
 cf:=cube[1][2][2];
 cl:=cube[3][2][2];
 cr:=cube[4][2][2];
 cb:=cube[2][2][2];

 if ((cube[1][1][1]=cf)and(cube[5][1][3]=cu)and(cube[3][1][1]=cl)or
    (cube[1][1][1]=cu)and(cube[5][1][3]=cl)and(cube[3][1][1]=cf)or
    (cube[1][1][1]=cl)and(cube[5][1][3]=cf)and(cube[3][1][1]=cu))and

    ((cube[2][1][1]=cb)and(cube[5][1][1]=cu)and(cube[3][3][1]=cl)or
    (cube[2][1][1]=cu)and(cube[5][1][1]=cl)and(cube[3][3][1]=cb)or
    (cube[2][1][1]=cl)and(cube[5][1][1]=cb)and(cube[3][3][1]=cu))and

    ((cube[2][3][1]=cb)and(cube[5][3][1]=cu)and(cube[4][3][1]=cr)or
    (cube[2][3][1]=cu)and(cube[5][3][1]=cr)and(cube[4][3][1]=cb)or
    (cube[2][3][1]=cr)and(cube[5][3][1]=cb)and(cube[4][3][1]=cu))and

    ((cube[1][3][1]=cf)and(cube[5][3][3]=cu)and(cube[4][1][1]=cr)or
    (cube[1][3][1]=cu)and(cube[5][3][3]=cr)and(cube[4][1][1]=cf)or
    (cube[1][3][1]=cr)and(cube[5][3][3]=cf)and(cube[4][1][1]=cu))
 then
      CheckEnd6:=true
 else CheckEnd6:=false;

end;


procedure TCube.ColorToLocation(c1:TCubeColor;c2:TCubeColor;var l1:TCubeLocation; var l2:TCubeLocation);
begin
 if (cube[3][2][1]=c1) and (cube[5][1][2]=c2) then begin l1:=3; l2:=5; end;
 if (cube[3][2][1]=c2) and (cube[5][1][2]=c1 ) then begin l1:=5; l2:=3; end;

 if (cube[2][2][1]=c1) and (cube[5][2][1]=c2 ) then begin l1:=2; l2:=5; end;
 if (cube[2][2][1]=c2) and (cube[5][2][1]=c1 ) then begin l1:=5; l2:=2; end;

 if (cube[4][2][1]=c1) and (cube[5][3][2]=c2 ) then begin l1:=4; l2:=5; end;
 if (cube[4][2][1]=c2) and (cube[5][3][2]=c1 ) then begin l1:=5; l2:=4; end;

 if (cube[1][2][1]=c1) and (cube[5][2][3]=c2 ) then begin l1:=1; l2:=5; end;
 if (cube[1][2][1]=c2) and (cube[5][2][3]=c1 ) then begin l1:=5; l2:=1; end;

 if (cube[1][1][2]=c1) and (cube[3][1][2]=c2 ) then begin l1:=1; l2:=3; end;
 if (cube[1][1][2]=c2) and (cube[3][1][2]=c1 ) then begin l1:=3; l2:=1; end;

 if (cube[3][3][2]=c1) and (cube[2][1][2]=c2 ) then begin l1:=3; l2:=2; end;
 if (cube[3][3][2]=c2) and (cube[2][1][2]=c1 ) then begin l1:=2; l2:=3; end;

 if (cube[2][3][2]=c1) and (cube[4][3][2]=c2 ) then begin l1:=2; l2:=4; end;
 if (cube[2][3][2]=c2) and (cube[4][3][2]=c1 ) then begin l1:=4; l2:=2; end;

 if (cube[4][1][2]=c1) and (cube[1][3][2]=c2 ) then begin l1:=4; l2:=1; end;
 if (cube[4][1][2]=c2) and (cube[1][3][2]=c1 ) then begin l1:=1; l2:=4; end;

 if (cube[3][2][3]=c1) and (cube[6][1][2]=c2 ) then begin l1:=3; l2:=6; end;
 if (cube[3][2][3]=c2) and (cube[6][1][2]=c1 ) then begin l1:=6; l2:=3; end;

 if (cube[2][2][3]=c1) and (cube[6][2][1]=c2 ) then begin l1:=2; l2:=6; end;
 if (cube[2][2][3]=c2) and (cube[6][2][1]=c1 ) then begin l1:=6; l2:=2; end;

 if (cube[4][2][3]=c1) and (cube[6][3][2]=c2 ) then begin l1:=4; l2:=6; end;
 if (cube[4][2][3]=c2) and (cube[6][3][2]=c1 ) then begin l1:=6; l2:=4; end;

 if (cube[1][2][3]=c1) and (cube[6][2][3]=c2 ) then begin l1:=1; l2:=6; end;
 if (cube[1][2][3]=c2) and (cube[6][2][3]=c1 ) then begin l1:=6; l2:=1; end;

end;

procedure TCube.ColorToLocation(c1:TCubeColor;c2:TCubeColor;c3:TCubeColor;
             var l1:TCubeLocation; var l2:TCubeLocation; var l3:TCubeLocation);
begin
 if (cube[1][1][1]=c1) and (cube[3][1][1]=c2) and (cube[5][1][3]=c3) then
  begin l1:=1; l2:=3; l3:=5; end;
 if (cube[1][1][1]=c1) and (cube[3][1][1]=c3) and (cube[5][1][3]=c2) then
  begin l1:=1; l3:=3; l2:=5; end;
 if (cube[1][1][1]=c2) and (cube[3][1][1]=c1) and (cube[5][1][3]=c3) then
  begin l2:=1; l1:=3; l3:=5; end;
 if (cube[1][1][1]=c2) and (cube[3][1][1]=c3) and (cube[5][1][3]=c1) then
  begin l2:=1; l3:=3; l1:=5; end;
 if (cube[1][1][1]=c3) and (cube[3][1][1]=c1) and (cube[5][1][3]=c2) then
  begin l3:=1; l1:=3; l2:=5; end;
 if (cube[1][1][1]=c3) and (cube[3][1][1]=c2) and (cube[5][1][3]=c1) then
  begin l3:=1; l2:=3; l1:=5; end;

 if (cube[2][1][1]=c1) and (cube[3][3][1]=c2) and (cube[5][1][1]=c3) then
  begin l1:=2; l2:=3; l3:=5; end;
 if (cube[2][1][1]=c1) and (cube[3][3][1]=c3) and (cube[5][1][1]=c2) then
  begin l1:=2; l3:=3; l2:=5; end;
 if (cube[2][1][1]=c2) and (cube[3][3][1]=c1) and (cube[5][1][1]=c3) then
  begin l2:=2; l1:=3; l3:=5; end;
 if (cube[2][1][1]=c2) and (cube[3][3][1]=c3) and (cube[5][1][1]=c1) then
  begin l2:=2; l3:=3; l1:=5; end;
 if (cube[2][1][1]=c3) and (cube[3][3][1]=c1) and (cube[5][1][1]=c2) then
  begin l3:=2; l1:=3; l2:=5; end;
 if (cube[2][1][1]=c3) and (cube[3][3][1]=c2) and (cube[5][1][1]=c1) then
  begin l3:=2; l2:=3; l1:=5; end;

 if (cube[2][3][1]=c1) and (cube[4][3][1]=c2) and (cube[5][3][1]=c3) then
  begin l1:=2; l2:=4; l3:=5; end;
 if (cube[2][3][1]=c1) and (cube[4][3][1]=c3) and (cube[5][3][1]=c2) then
  begin l1:=2; l3:=4; l2:=5; end;
 if (cube[2][3][1]=c2) and (cube[4][3][1]=c1) and (cube[5][3][1]=c3) then
  begin l2:=2; l1:=4; l3:=5; end;
 if (cube[2][3][1]=c2) and (cube[4][3][1]=c3) and (cube[5][3][1]=c1) then
  begin l2:=2; l3:=4; l1:=5; end;
 if (cube[2][3][1]=c3) and (cube[4][3][1]=c1) and (cube[5][3][1]=c2) then
  begin l3:=2; l1:=4; l2:=5; end;
 if (cube[2][3][1]=c3) and (cube[4][3][1]=c2) and (cube[5][3][1]=c1) then
  begin l3:=2; l2:=4; l1:=5; end;

 if (cube[1][3][1]=c1) and (cube[4][1][1]=c2) and (cube[5][3][3]=c3) then
  begin l1:=1; l2:=4; l3:=5; end;
 if (cube[1][3][1]=c1) and (cube[4][1][1]=c3) and (cube[5][3][3]=c2) then
  begin l1:=1; l3:=4; l2:=5; end;
 if (cube[1][3][1]=c2) and (cube[4][1][1]=c1) and (cube[5][3][3]=c3) then
  begin l2:=1; l1:=4; l3:=5; end;
 if (cube[1][3][1]=c2) and (cube[4][1][1]=c3) and (cube[5][3][3]=c1) then
  begin l2:=1; l3:=4; l1:=5; end;
 if (cube[1][3][1]=c3) and (cube[4][1][1]=c1) and (cube[5][3][3]=c2) then
  begin l3:=1; l1:=4; l2:=5; end;
 if (cube[1][3][1]=c3) and (cube[4][1][1]=c2) and (cube[5][3][3]=c1) then
  begin l3:=1; l2:=4; l1:=5; end;

 if (cube[1][1][3]=c1) and (cube[3][1][3]=c2) and (cube[6][1][3]=c3) then
  begin l1:=1; l2:=3; l3:=6; end;
 if (cube[1][1][3]=c1) and (cube[3][1][3]=c3) and (cube[6][1][3]=c2) then
  begin l1:=1; l3:=3; l2:=6; end;
 if (cube[1][1][3]=c2) and (cube[3][1][3]=c1) and (cube[6][1][3]=c3) then
  begin l2:=1; l1:=3; l3:=6; end;
 if (cube[1][1][3]=c2) and (cube[3][1][3]=c3) and (cube[6][1][3]=c1) then
  begin l2:=1; l3:=3; l1:=6; end;
 if (cube[1][1][3]=c3) and (cube[3][1][3]=c1) and (cube[6][1][3]=c2) then
  begin l3:=1; l1:=3; l2:=6; end;
 if (cube[1][1][3]=c3) and (cube[3][1][3]=c2) and (cube[6][1][3]=c1) then
  begin l3:=1; l2:=3; l1:=6; end;

 if (cube[2][1][3]=c1) and (cube[3][3][3]=c2) and (cube[6][1][1]=c3) then
  begin l1:=2; l2:=3; l3:=6; end;
 if (cube[2][1][3]=c1) and (cube[3][3][3]=c3) and (cube[6][1][1]=c2) then
  begin l1:=2; l3:=3; l2:=6; end;
 if (cube[2][1][3]=c2) and (cube[3][3][3]=c1) and (cube[6][1][1]=c3) then
  begin l2:=2; l1:=3; l3:=6; end;
 if (cube[2][1][3]=c2) and (cube[3][3][3]=c3) and (cube[6][1][1]=c1) then
  begin l2:=2; l3:=3; l1:=6; end;
 if (cube[2][1][3]=c3) and (cube[3][3][3]=c1) and (cube[6][1][1]=c2) then
  begin l3:=2; l1:=3; l2:=6; end;
 if (cube[2][1][3]=c3) and (cube[3][3][3]=c2) and (cube[6][1][1]=c1) then
  begin l3:=2; l2:=3; l1:=6; end;

 if (cube[2][3][3]=c1) and (cube[4][3][3]=c2) and (cube[6][3][1]=c3) then
  begin l1:=2; l2:=4; l3:=6; end;
 if (cube[2][3][3]=c1) and (cube[4][3][3]=c3) and (cube[6][3][1]=c2) then
  begin l1:=2; l3:=4; l2:=6; end;
 if (cube[2][3][3]=c2) and (cube[4][3][3]=c1) and (cube[6][3][1]=c3) then
  begin l2:=2; l1:=4; l3:=6; end;
 if (cube[2][3][3]=c2) and (cube[4][3][3]=c3) and (cube[6][3][1]=c1) then
  begin l2:=2; l3:=4; l1:=6; end;
 if (cube[2][3][3]=c3) and (cube[4][3][3]=c1) and (cube[6][3][1]=c2) then
  begin l3:=2; l1:=4; l2:=6; end;
 if (cube[2][3][3]=c3) and (cube[4][3][3]=c2) and (cube[6][3][1]=c1) then
  begin l3:=2; l2:=4; l1:=6; end;

 if (cube[1][3][3]=c1) and (cube[4][1][3]=c2) and (cube[6][3][3]=c3) then
  begin l1:=1; l2:=4; l3:=6; end;
 if (cube[1][3][3]=c1) and (cube[4][1][3]=c3) and (cube[6][3][3]=c2) then
  begin l1:=1; l3:=4; l2:=6; end;
 if (cube[1][3][3]=c2) and (cube[4][1][3]=c1) and (cube[6][3][3]=c3) then
  begin l2:=1; l1:=4; l3:=6; end;
 if (cube[1][3][3]=c2) and (cube[4][1][3]=c3) and (cube[6][3][3]=c1) then
  begin l2:=1; l3:=4; l1:=6; end;
 if (cube[1][3][3]=c3) and (cube[4][1][3]=c1) and (cube[6][3][3]=c2) then
  begin l3:=1; l1:=4; l2:=6; end;
 if (cube[1][3][3]=c3) and (cube[4][1][3]=c2) and (cube[6][3][3]=c1) then
  begin l3:=1; l2:=4; l1:=6; end;


end;

constructor TCube.Create;
begin
 Reset;
 test:=0;
end;

procedure TCube.Reset;
var i,j,k:byte;
begin
 for i:=1 to 6 do
  for j:=1 to 3 do
   for k:=1 to 3 do
    cub[i,j,k]:=i;
end;

procedure TCube.Rotate(direction:TRotateDirection);
var i,j,k:byte;
    newcub:array [1..6,1..3,1..3] of TCubeColor;
begin
 for i:=1 to 6 do
  for j:=1 to 3 do
   for k:=1 to 3 do
    newcub[i,j,k]:=cub[i,j,k];
 case direction of
 _left : begin
         for i:=1 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[4,i,j];
           newcub[2,i,j]:=cub[3,i,j];
           newcub[3,i,j]:=cub[1,4-i,j];
           newcub[4,i,j]:=cub[2,4-i,j];
           newcub[5,i,j]:=cub[5,j,4-i];
           newcub[6,i,j]:=cub[6,j,4-i];
          end;
        end;
 _left1: begin
         for i:=1 to 3 do
          for j:=1 to 1 do
          begin
           newcub[1,i,j]:=cub[4,i,j];
           newcub[2,i,j]:=cub[3,i,j];
           newcub[3,i,j]:=cub[1,4-i,j];
           newcub[4,i,j]:=cub[2,4-i,j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[5,i,j]:=cub[5,j,4-i];
        end;
 _left2: begin
         for i:=1 to 3 do
          for j:=2 to 2 do
          begin
           newcub[1,i,j]:=cub[4,i,j];
           newcub[2,i,j]:=cub[3,i,j];
           newcub[3,i,j]:=cub[1,4-i,j];
           newcub[4,i,j]:=cub[2,4-i,j];
          end;
        end;
 _left3: begin
         for i:=1 to 3 do
          for j:=3 to 3 do
          begin
           newcub[1,i,j]:=cub[4,i,j];
           newcub[2,i,j]:=cub[3,i,j];
           newcub[3,i,j]:=cub[1,4-i,j];
           newcub[4,i,j]:=cub[2,4-i,j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[6,i,j]:=cub[6,j,4-i];
        end;
 _right :begin
         for i:=1 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[3,4-i,j];
           newcub[2,i,j]:=cub[4,4-i,j];
           newcub[3,i,j]:=cub[2,i,j];
           newcub[4,i,j]:=cub[1,i,j];
           newcub[5,i,j]:=cub[5,4-j,i];
           newcub[6,i,j]:=cub[6,4-j,i];
          end;
        end;
 _right1:begin
         for i:=1 to 3 do
          for j:=1 to 1 do
          begin
           newcub[1,i,j]:=cub[3,4-i,j];
           newcub[2,i,j]:=cub[4,4-i,j];
           newcub[3,i,j]:=cub[2,i,j];
           newcub[4,i,j]:=cub[1,i,j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[5,i,j]:=cub[5,4-j,i];
        end;
 _right2:begin
         for i:=1 to 3 do
          for j:=2 to 2 do
          begin
           newcub[1,i,j]:=cub[3,4-i,j];
           newcub[2,i,j]:=cub[4,4-i,j];
           newcub[3,i,j]:=cub[2,i,j];
           newcub[4,i,j]:=cub[1,i,j];
          end;
        end;
 _right3:begin
         for i:=1 to 3 do
          for j:=3 to 3 do
          begin
           newcub[1,i,j]:=cub[3,4-i,j];
           newcub[2,i,j]:=cub[4,4-i,j];
           newcub[3,i,j]:=cub[2,i,j];
           newcub[4,i,j]:=cub[1,i,j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[6,i,j]:=cub[6,4-j,i];
        end;
 _up   : begin
         for i:=1 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[6,i,4-j];
           newcub[2,i,j]:=cub[5,i,4-j];
           newcub[3,i,j]:=cub[3,j,4-i];
           newcub[4,i,j]:=cub[4,j,4-i];
           newcub[5,i,j]:=cub[1,i,j];
           newcub[6,i,j]:=cub[2,i,j];
          end;
        end;
 _up1  : begin
         for i:=1 to 1 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[6,i,4-j];
           newcub[2,i,j]:=cub[5,i,4-j];
           newcub[5,i,j]:=cub[1,i,j];
           newcub[6,i,j]:=cub[2,i,j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[3,i,j]:=cub[3,j,4-i];
        end;
 _up2  : begin
         for i:=2 to 2 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[6,i,4-j];
           newcub[2,i,j]:=cub[5,i,4-j];
           newcub[5,i,j]:=cub[1,i,j];
           newcub[6,i,j]:=cub[2,i,j];
          end;
        end;
 _up3  : begin
         for i:=3 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[6,i,4-j];
           newcub[2,i,j]:=cub[5,i,4-j];
           newcub[5,i,j]:=cub[1,i,j];
           newcub[6,i,j]:=cub[2,i,j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[4,i,j]:=cub[4,j,4-i];
        end;
 _down : begin
         for i:=1 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[5,i,j];
           newcub[2,i,j]:=cub[6,i,j];
           newcub[3,i,j]:=cub[3,4-j,i];
           newcub[4,i,j]:=cub[4,4-j,i];
           newcub[5,i,j]:=cub[2,i,4-j];
           newcub[6,i,j]:=cub[1,i,4-j];
          end;
        end;
 _down1 : begin
         for i:=1 to 1 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[5,i,j];
           newcub[2,i,j]:=cub[6,i,j];
           newcub[5,i,j]:=cub[2,i,4-j];
           newcub[6,i,j]:=cub[1,i,4-j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[3,i,j]:=cub[3,4-j,i];
        end;
 _down2 : begin
         for i:=2 to 2 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[5,i,j];
           newcub[2,i,j]:=cub[6,i,j];
           newcub[5,i,j]:=cub[2,i,4-j];
           newcub[6,i,j]:=cub[1,i,4-j];
          end;
        end;
 _down3 : begin
         for i:=3 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[5,i,j];
           newcub[2,i,j]:=cub[6,i,j];
           newcub[5,i,j]:=cub[2,i,4-j];
           newcub[6,i,j]:=cub[1,i,4-j];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[4,i,j]:=cub[4,4-j,i];
        end;
 _CW   : begin
         for i:=1 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[1,j,4-i];
           newcub[2,i,j]:=cub[2,j,4-i];
           newcub[3,i,j]:=cub[6,j,4-i];
           newcub[4,i,j]:=cub[5,j,4-i];
           newcub[5,i,j]:=cub[3,4-j,4-i];
           newcub[6,i,j]:=cub[4,4-j,4-i];
          end;
        end;
 _CW1  : begin
         for i:=1 to 3 do
          for j:=1 to 1 do
          begin
           newcub[3,j,i]:=cub[6,i,4-j];
           newcub[4,j,i]:=cub[5,i,4-j];
           newcub[5,i,4-j]:=cub[3,j,4-i];
           newcub[6,i,4-j]:=cub[4,j,4-i];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[1,i,j]:=cub[1,j,4-i];
        end;
 _CW2  : begin
         for i:=1 to 3 do
          for j:=2 to 2 do
          begin
           newcub[3,j,i]:=cub[6,i,4-j];
           newcub[4,j,i]:=cub[5,i,4-j];
           newcub[5,i,4-j]:=cub[3,j,4-i];
           newcub[6,i,4-j]:=cub[4,j,4-i];
          end;
        end;
 _CW3  : begin
         for i:=1 to 3 do
          for j:=3 to 3 do
          begin
           newcub[3,j,i]:=cub[6,i,4-j];
           newcub[4,j,i]:=cub[5,i,4-j];
           newcub[5,i,4-j]:=cub[3,j,4-i];
           newcub[6,i,4-j]:=cub[4,j,4-i];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[2,i,j]:=cub[2,j,4-i];
        end;
 _CCW  : begin
         for i:=1 to 3 do
          for j:=1 to 3 do
          begin
           newcub[1,i,j]:=cub[1,4-j,i];
           newcub[2,i,j]:=cub[2,4-j,i];
           newcub[3,i,j]:=cub[5,4-j,4-i];
           newcub[4,i,j]:=cub[6,4-j,4-i];
           newcub[5,i,j]:=cub[4,4-j,i];
           newcub[6,i,j]:=cub[3,4-j,i];
          end;
        end;
 _CCW1 : begin
         for i:=1 to 3 do
          for j:=1 to 1 do
          begin
           newcub[3,j,i]:=cub[5,4-i,4-j];
           newcub[4,j,i]:=cub[6,4-i,4-j];
           newcub[5,i,4-j]:=cub[4,j,i];
           newcub[6,i,4-j]:=cub[3,j,i];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[1,i,j]:=cub[1,4-j,i];
        end;
 _CCW2 : begin
         for i:=1 to 3 do
          for j:=2 to 2 do
          begin
           newcub[3,j,i]:=cub[5,4-i,4-j];
           newcub[4,j,i]:=cub[6,4-i,4-j];
           newcub[5,i,4-j]:=cub[4,j,i];
           newcub[6,i,4-j]:=cub[3,j,i];
          end;
        end;
 _CCW3 : begin
         for i:=1 to 3 do
          for j:=3 to 3 do
          begin
           newcub[3,j,i]:=cub[5,4-i,4-j];
           newcub[4,j,i]:=cub[6,4-i,4-j];
           newcub[5,i,4-j]:=cub[4,j,i];
           newcub[6,i,4-j]:=cub[3,j,i];
          end;
         for i:=1 to 3 do
          for j:=1 to 3 do
           newcub[2,i,j]:=cub[2,4-j,i];
        end;
 end{case} ;
 for i:=1 to 6 do
  for j:=1 to 3 do
   for k:=1 to 3 do
    cub[i,j,k]:=newcub[i,j,k];
end;



procedure TCube.RandomizeCube;
begin
 RandomizeCube(1000);
end;

procedure TCube.RandomizeCube(steps:longint);
var i,r:integer;
    t:TRotateDirection;
begin
 Randomize;
 for i:=1 to steps do
 begin
  r:=random(24);
  t:=_left;
  while r>0 do
  begin
   inc(t);
   dec(r);
  end;
  Rotate(t);
 end;
end;
////////////////////////////TGLCube///////////////////////////////

procedure TGLCube.SetDefaultColors;
begin
 color[1]:=2957508;  //4718756;
 color[2]:=33023; //16758711;  //clLime;
 color[3]:=10485760; //clBlue;
 color[4]:=5077021; //clYellow;
 color[5]:=clWhite; //clAqua;
 color[6]:=61680; //8454143; //clFuchsia;
 bkColor:=clBlack;
 lnColor:=clWhite;
end;

procedure TGLCube.ResetImage;
var
 ps : TPaintStruct;
begin
 wglMakeCurrent(dc,hrc);
 BeginPaint(h,ps);

 glEnable(GL_CULL_FACE);
 glLoadIdentity;
 glOrtho(-2,2,-2,2,-2,2);
 glEnable(GL_DEPTH_TEST);
 glRotatef(45,1,0,0);
 glRotatef(-45,0,1,0);
 glRotatef(0,0,0,1);
 EndPaint(h,ps);
 wglMakeCurrent(0,0);
end;

constructor TGLCube.Create(Handle:HWND);
begin
 h := Handle;
 dc := GetDC (Handle);
 SetDCPixelFormat(dc);
 hrc := wglCreateContext(dc);
 ResetImage;
 rotSpeed:=1;
 ang:=0;
 SetDefaultColors;
 inherited Create;
end;

destructor TGLCube.Dispose;
begin
 wglDeleteContext(hrc);
 ReleaseDC (h, DC);
 DeleteDC (DC);
end;

procedure TGLCube.AnimatedRotate(direction:TRotateDirection);
var t,t0:longint;
    i,j:byte;
begin
 t:=GetTickCount;
 t0:=t;
 for i:=1 to 3 do
  for j:=1 to 3 do
   rd[i,j]:=false;
 case direction of
 _left : begin
          dx:=0;
          dy:=-1;
          dz:=0;
          rd[2,1]:=true;
          rd[2,2]:=true;
          rd[2,3]:=true;
         end;
 _left1 : begin
          dx:=0;
          dy:=-1;
          dz:=0;
          rd[2,1]:=true;
         end;
 _left2 : begin
          dx:=0;
          dy:=-1;
          dz:=0;
          rd[2,2]:=true;
         end;
 _left3 : begin
          dx:=0;
          dy:=-1;
          dz:=0;
          rd[2,3]:=true;
         end;
 _right : begin
          dx:=0;
          dy:=1;
          dz:=0;
          rd[2,1]:=true;
          rd[2,2]:=true;
          rd[2,3]:=true;
         end;
 _right1 : begin
          dx:=0;
          dy:=1;
          dz:=0;
          rd[2,1]:=true;
         end;
 _right2 : begin
          dx:=0;
          dy:=1;
          dz:=0;
          rd[2,2]:=true;
         end;
 _right3 : begin
          dx:=0;
          dy:=1;
          dz:=0;
          rd[2,3]:=true;
         end;
 _up   : begin
          dx:=-1;
          dy:=0;
          dz:=0;
          rd[1,1]:=true;
          rd[1,2]:=true;
          rd[1,3]:=true;
         end;
 _up1  : begin
          dx:=-1;
          dy:=0;
          dz:=0;
          rd[1,1]:=true;
         end;
 _up2  : begin
          dx:=-1;
          dy:=0;
          dz:=0;
          rd[1,2]:=true;
         end;
 _up3  : begin
          dx:=-1;
          dy:=0;
          dz:=0;
          rd[1,3]:=true;
         end;
 _down : begin
          dx:=1;
          dy:=0;
          dz:=0;
          rd[1,1]:=true;
          rd[1,2]:=true;
          rd[1,3]:=true;
         end;
 _down1 : begin
          dx:=1;
          dy:=0;
          dz:=0;
          rd[1,1]:=true;
         end;
 _down2 : begin
          dx:=1;
          dy:=0;
          dz:=0;
          rd[1,2]:=true;
         end;
 _down3 : begin
          dx:=1;
          dy:=0;
          dz:=0;
          rd[1,3]:=true;
         end;
 _CW   : begin
          dx:=0;
          dy:=0;
          dz:=-1;
          rd[3,1]:=true;
          rd[3,2]:=true;
          rd[3,3]:=true;
         end;
 _CW1  : begin
          dx:=0;
          dy:=0;
          dz:=-1;
          rd[3,1]:=true;
         end;
 _CW2  : begin
          dx:=0;
          dy:=0;
          dz:=-1;
          rd[3,2]:=true;
         end;
 _CW3  : begin
          dx:=0;
          dy:=0;
          dz:=-1;
          rd[3,3]:=true;
         end;
 _CCW  : begin
          dx:=0;
          dy:=0;
          dz:=1;
          rd[3,1]:=true;
          rd[3,2]:=true;
          rd[3,3]:=true;
         end;
 _CCW1 : begin
          dx:=0;
          dy:=0;
          dz:=1;
          rd[3,1]:=true;
         end;
 _CCW2 : begin
          dx:=0;
          dy:=0;
          dz:=1;
          rd[3,2]:=true;
         end;
 _CCW3 : begin
          dx:=0;
          dy:=0;
          dz:=1;
          rd[3,3]:=true;
         end;
 end;{case}
 ang:=0;
 t:=GetTickCount;
 while (t-t0)<(rotSpeed*1000) do
 begin
  ang:=(t-t0)/(rotSpeed*1000)*90;
  Animate;
  t:=GetTickCount;
 end;
 Rotate(direction);
 ang:=0;
end;

procedure TGLCube.Animate;
var
 ps : TPaintStruct;
 cr,cg,cb:GLFloat;
 i,j,k:byte;
begin
 BeginPaint (h, ps);
 wglMakeCurrent(dc, hrc);
 ColorToGL(bkColor,cr,cg,cb);
 glClearColor (cr, cg, cb, 1.0);
 glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
// glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
 glLineWidth(5);
 //draw axis
{ ColorToGL(lnColor,cr,cg,cb);
 glColor3f (cr, cg, cb);
 glBegin(GL_LINES);
  glVertex3f(1,0,0);
  glVertex3f(2,0,0);
  glVertex3f(0,1,0);
  glVertex3f(0,2,0);
  glVertex3f(0,0,1);
  glVertex3f(0,0,2);
 glEnd;}
  //front(top)
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[1,i,4-j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    if rd[1,i] or rd[2,4-j] or rd[3,1] then
    begin
     glRotatef(ang,dx,dy,dz);
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.95)-1,1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.95)-1,1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.05)-1,1);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.05)-1,1);
     glEnd;
     glRotatef(-ang,dx,dy,dz);
    end else
    begin
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.95)-1,1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.95)-1,1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.05)-1,1);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.05)-1,1);
     glEnd;
    end;
   end;
  //back(bottom)
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[2,i,4-j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    if rd[1,i] or rd[2,4-j] or rd[3,3] then
    begin
     glRotatef(ang,dx,dy,dz);
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.95)-1,-1);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.05)-1,-1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.05)-1,-1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.95)-1,-1);
     glEnd;
     glRotatef(-ang,dx,dy,dz);
    end else
    begin
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.95)-1,-1);
     glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.05)-1,-1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.05)-1,-1);
     glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.95)-1,-1);
     glEnd;
    end;
   end;
  //left
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[3,4-j,4-i]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    if rd[1,1] or rd[2,4-i] or rd[3,4-j] then
    begin
     glRotatef(ang,dx,dy,dz);
     glBegin(GL_QUADS);
     glVertex3f(-1,2/3*(i-0.95)-1,2/3*(j-0.95)-1);
     glVertex3f(-1,2/3*(i-0.95)-1,2/3*(j-0.05)-1);
     glVertex3f(-1,2/3*(i-0.05)-1,2/3*(j-0.05)-1);
     glVertex3f(-1,2/3*(i-0.05)-1,2/3*(j-0.95)-1);
     glEnd;
     glRotatef(-ang,dx,dy,dz);
    end else
    begin
     glBegin(GL_QUADS);
     glVertex3f(-1,2/3*(i-0.95)-1,2/3*(j-0.95)-1);
     glVertex3f(-1,2/3*(i-0.95)-1,2/3*(j-0.05)-1);
     glVertex3f(-1,2/3*(i-0.05)-1,2/3*(j-0.05)-1);
     glVertex3f(-1,2/3*(i-0.05)-1,2/3*(j-0.95)-1);
     glEnd;
    end;
   end;
  //right
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[4,4-j,4-i]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    if rd[1,3] or rd[2,4-i] or rd[3,4-j] then
    begin
     glRotatef(ang,dx,dy,dz);
     glBegin(GL_QUADS);
     glVertex3f(1,2/3*(i-0.95)-1,2/3*(j-0.95)-1);
     glVertex3f(1,2/3*(i-0.05)-1,2/3*(j-0.95)-1);
     glVertex3f(1,2/3*(i-0.05)-1,2/3*(j-0.05)-1);
     glVertex3f(1,2/3*(i-0.95)-1,2/3*(j-0.05)-1);
     glEnd;
     glRotatef(-ang,dx,dy,dz);
    end else
    begin
     glBegin(GL_QUADS);
     glVertex3f(1,2/3*(i-0.95)-1,2/3*(j-0.95)-1);
     glVertex3f(1,2/3*(i-0.05)-1,2/3*(j-0.95)-1);
     glVertex3f(1,2/3*(i-0.05)-1,2/3*(j-0.05)-1);
     glVertex3f(1,2/3*(i-0.95)-1,2/3*(j-0.05)-1);
     glEnd;
    end;
   end;
  //down
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[6,i,j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    if rd[1,i] or rd[2,3] or rd[3,4-j] then
    begin
     glRotatef(ang,dx,dy,dz);
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,-1,2/3*(j-0.95)-1);
     glVertex3f(2/3*(i-0.05)-1,-1,2/3*(j-0.95)-1);
     glVertex3f(2/3*(i-0.05)-1,-1,2/3*(j-0.05)-1);
     glVertex3f(2/3*(i-0.95)-1,-1,2/3*(j-0.05)-1);
     glEnd;
     glRotatef(-ang,dx,dy,dz);
    end else
    begin
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,-1,2/3*(j-0.95)-1);
     glVertex3f(2/3*(i-0.05)-1,-1,2/3*(j-0.95)-1);
     glVertex3f(2/3*(i-0.05)-1,-1,2/3*(j-0.05)-1);
     glVertex3f(2/3*(i-0.95)-1,-1,2/3*(j-0.05)-1);
     glEnd;
    end;
   end;
  //up
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[5,i,j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    if rd[1,i] or rd[2,1] or rd[3,4-j] then
    begin
     glRotatef(ang,dx,dy,dz);
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,1,2/3*(j-0.95)-1);
     glVertex3f(2/3*(i-0.95)-1,1,2/3*(j-0.05)-1);
     glVertex3f(2/3*(i-0.05)-1,1,2/3*(j-0.05)-1);
     glVertex3f(2/3*(i-0.05)-1,1,2/3*(j-0.95)-1);
     glEnd;
     glRotatef(-ang,dx,dy,dz);
    end else
    begin
     glBegin(GL_QUADS);
     glVertex3f(2/3*(i-0.95)-1,1,2/3*(j-0.95)-1);
     glVertex3f(2/3*(i-0.95)-1,1,2/3*(j-0.05)-1);
     glVertex3f(2/3*(i-0.05)-1,1,2/3*(j-0.05)-1);
     glVertex3f(2/3*(i-0.05)-1,1,2/3*(j-0.95)-1);
     glEnd;
    end;
   end;
 glEnd;
 SwapBuffers(h);
 wglMakeCurrent(0, 0);
 EndPaint (h, ps);
end;

procedure TGLCube.Draw;
var
 ps : TPaintStruct;
 cr,cg,cb:GLFloat;
 i,j,k:byte;
begin
 wglMakeCurrent(dc, hrc);
 BeginPaint (h, ps); 
 ColorToGL(bkColor,cr,cg,cb);
 glClearColor (cr, cg, cb, 1.0);
 glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);
// glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
 glLineWidth(5);
 //draw axis
 ColorToGL(lnColor,cr,cg,cb);
 glColor3f (cr, cg, cb);
 glBegin(GL_LINES);
  glVertex3f(1,0,0);
  glVertex3f(2,0,0);
  glVertex3f(0,1,0);
  glVertex3f(0,2,0);
  glVertex3f(0,0,1);
  glVertex3f(0,0,2);
 glEnd;
 glBegin(GL_QUADS);
  //front(top)
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[1,i,4-j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.95)-1,1);
    glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.95)-1,1);
    glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.05)-1,1);
    glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.05)-1,1);
   end;
  //back(bottom)
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[2,i,4-j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.95)-1,-1);
    glVertex3f(2/3*(i-0.95)-1,2/3*(j-0.05)-1,-1);
    glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.05)-1,-1);
    glVertex3f(2/3*(i-0.05)-1,2/3*(j-0.95)-1,-1);
   end;
  //left
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[3,4-j,4-i]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    glVertex3f(-1,2/3*(i-0.95)-1,2/3*(j-0.95)-1);
    glVertex3f(-1,2/3*(i-0.95)-1,2/3*(j-0.05)-1);
    glVertex3f(-1,2/3*(i-0.05)-1,2/3*(j-0.05)-1);
    glVertex3f(-1,2/3*(i-0.05)-1,2/3*(j-0.95)-1);
   end;
  //right
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[4,4-j,4-i]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    glVertex3f(1,2/3*(i-0.95)-1,2/3*(j-0.95)-1);
    glVertex3f(1,2/3*(i-0.05)-1,2/3*(j-0.95)-1);
    glVertex3f(1,2/3*(i-0.05)-1,2/3*(j-0.05)-1);
    glVertex3f(1,2/3*(i-0.95)-1,2/3*(j-0.05)-1);
   end;
  //down
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[6,i,j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    glVertex3f(2/3*(i-0.95)-1,-1,2/3*(j-0.95)-1);
    glVertex3f(2/3*(i-0.05)-1,-1,2/3*(j-0.95)-1);
    glVertex3f(2/3*(i-0.05)-1,-1,2/3*(j-0.05)-1);
    glVertex3f(2/3*(i-0.95)-1,-1,2/3*(j-0.05)-1);
   end;
  //up
  for i:=1 to 3 do
   for j:=1 to 3 do
   begin
    ColorToGL(color[cube[5,i,j]],cr,cg,cb);
    glColor3f (cr, cg, cb);
    glVertex3f(2/3*(i-0.95)-1,1,2/3*(j-0.95)-1);
    glVertex3f(2/3*(i-0.95)-1,1,2/3*(j-0.05)-1);
    glVertex3f(2/3*(i-0.05)-1,1,2/3*(j-0.05)-1);
    glVertex3f(2/3*(i-0.05)-1,1,2/3*(j-0.95)-1);
   end;
 glEnd;
 SwapBuffers(h);
 EndPaint (h, ps);
 wglMakeCurrent(0, 0);
end;

procedure TGLCube.SetViewPort(left,top,right,bottom:integer);
begin
 wglMakeCurrent(dc,hrc);
 glViewport(left, top, right, bottom);
 wglMakeCurrent(0,0);
end;

procedure TGLCube.RotateImage(anx,any,anz:double);
begin
 wglMakeCurrent(dc,hrc);
 glRotatef(anx,1,0,0);
 glRotatef(any,0,1,0);
 glRotatef(anz,0,0,1);
 wglMakeCurrent(0,0);
end;


{‘ормат пиксел€}
procedure TGLCube.SetDCPixelFormat (hdc : HDC);
var
 pfd : TPixelFormatDescriptor;
 nPixelFormat : Integer;
begin
 FillChar (pfd, SizeOf (pfd), 0);
// pfd.dwFlags  := PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER;
 nPixelFormat := ChoosePixelFormat (hdc, @pfd);
 SetPixelFormat (hdc, nPixelFormat, @pfd);
end;


procedure TGLCube.ColorToGl(c:TColor;var R,G,B:GLFloat);
begin
 R:=(c and $FF)/255;
 G:=((c and $FF00) shr 8)/255;
 B:=((c and $FF0000) shr 16)/255;
end;

//////////////////////////////////////////////////////////////////

procedure TCubeForm.Button4Click(Sender: TObject);
begin
 Close;
end;

procedure TCubeForm.FormCreate(Sender: TObject);
begin
 cube:=TGLCube.Create(Panel1.Handle);
 //CubeForm.WindowState:=wsMaximized;
 MsgSIMPR:=RegisterWindowMessage(MESSAGE_STR);
 test:=0;
end;

procedure TCubeForm.FormPaint(Sender: TObject);
begin
 cube.Draw;
end;

procedure TCubeForm.FormDestroy(Sender: TObject);
begin
 cube.Dispose;
end;

procedure TCubeForm.FormResize(Sender: TObject);
var
 dist:integer;
begin
 dist:=Panel1.Width;
 if dist>Panel1.Height then dist:=Panel1.Height;
 cube.SetViewPort((Panel1.Width-dist) div 2,
                  (Panel1.Height-dist) div 2,
                  Panel1.Width - (Panel1.Width-dist),
                  Panel1.Height - (Panel1.Height-dist));
 InvalidateRect(handle,nil,false);
end;


procedure TCubeForm.Button1Click(Sender: TObject);
begin
 cube.RandomizeCube;
 cube.Draw;
 cube.GetTest;
end;

procedure TCubeForm.Button3Click(Sender: TObject);
begin
 PopupMenu1.Popup(Button3.Left+CubeForm.Left+Button3.Width,Button3.Top+CubeForm.Top+35);
end;

procedure TCubeForm.left1Click(Sender: TObject);
begin
 cube.AnimatedRotate(_left);
 cube.Draw;
end;

procedure TCubeForm.right1Click(Sender: TObject);
begin
 cube.AnimatedRotate(_right);
 cube.Draw;
end;

procedure TCubeForm.up1Click(Sender: TObject);
begin
 cube.AnimatedRotate(_up);
 cube.Draw;

end;

procedure TCubeForm.down1Click(Sender: TObject);
begin
 cube.AnimatedRotate(_down);
 cube.Draw;
end;

procedure TCubeForm.CW1Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CW);
 cube.Draw;
end;

procedure TCubeForm.CCW1Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CCW);
 cube.Draw;
end;

procedure TCubeForm.left11Click(Sender: TObject);
begin
 cube.AnimatedRotate(_left1);
 cube.Draw;
end;

procedure TCubeForm.left21Click(Sender: TObject);
begin
 cube.AnimatedRotate(_left2);
 cube.Draw;
end;

procedure TCubeForm.left31Click(Sender: TObject);
begin
 cube.AnimatedRotate(_left3);
 cube.Draw;
end;

procedure TCubeForm.right11Click(Sender: TObject);
begin
 cube.AnimatedRotate(_right1);
 cube.Draw;
end;

procedure TCubeForm.right21Click(Sender: TObject);
begin
 cube.AnimatedRotate(_right2);
 cube.Draw;
end;

procedure TCubeForm.right31Click(Sender: TObject);
begin
 cube.AnimatedRotate(_right3);
 cube.Draw;
end;

procedure TCubeForm.up11Click(Sender: TObject);
begin
 cube.AnimatedRotate(_up1);
 cube.Draw;
end;

procedure TCubeForm.up21Click(Sender: TObject);
begin
 cube.AnimatedRotate(_up2);
 cube.Draw;
end;

procedure TCubeForm.up31Click(Sender: TObject);
begin
 cube.AnimatedRotate(_up3);
 cube.Draw;
end;

procedure TCubeForm.down11Click(Sender: TObject);
begin
 cube.AnimatedRotate(_down1);
 cube.Draw;
end;

procedure TCubeForm.down21Click(Sender: TObject);
begin
 cube.AnimatedRotate(_down2);
 cube.Draw;
end;

procedure TCubeForm.down31Click(Sender: TObject);
begin
 cube.AnimatedRotate(_down3);
 cube.Draw;
end;

procedure TCubeForm.CW11Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CW1);
 cube.Draw;
end;

procedure TCubeForm.CW21Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CW2);
 cube.Draw;
end;

procedure TCubeForm.CW31Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CW3);
 cube.Draw;
end;

procedure TCubeForm.CCW11Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CCW1);
 cube.Draw;
end;

procedure TCubeForm.CCW21Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CCW2);
 cube.Draw;
end;

procedure TCubeForm.CCW31Click(Sender: TObject);
begin
 cube.AnimatedRotate(_CCW3);
 cube.Draw;
end;

procedure TCubeForm.Button2Click(Sender: TObject);
begin
// cube.Reset;
 cube.PutTest;
 cube.Draw;
end;

procedure TCubeForm.ApplicationEvents1Idle(Sender: TObject;
  var Done: Boolean);
var t0,dt:double;
begin
 t0:=GetTickCount();
 dt:=abs(t-t0)*0.01;
 t:=t0;
 if (TrackBar1.Position=0)and(TrackBar2.Position=0)and(TrackBar3.Position=0) then
  exit;
 cube.RotateImage(dt*TrackBar1.Position,dt*TrackBar2.Position,dt*TrackBar3.Position);
 InvalidateRect(Handle,nil,false);

end;

procedure TCubeForm.Button5Click(Sender: TObject);
begin
 TrackBar1.Position:=0;
 TrackBar2.Position:=0;
 TrackBar3.Position:=0;
 cube.ResetImage;
 cube.Draw;
end;

procedure TCubeForm.TrackBar4Change(Sender: TObject);
begin
 cube.animationSpeed:=(20-TrackBar4.Position)*(20-TrackBar4.Position)/100;
end;

procedure TCubeForm.Button6Click(Sender: TObject);
var i,r:integer;
    t:TRotateDirection;
begin
 Randomize;
 for i:=1 to 30 do
 begin
  r:=random(24);
  t:=_left;
  while r>0 do
  begin
   inc(t);
   dec(r);
  end;
  cube.AnimatedRotate(t);
 end;
 cube.Draw;
end;



procedure TCubeForm.WndProc(var Message: TMessage);
var res:boolean;
    cu,cf,cl,cr,cb,cd:TCubeColor;
    l1,l2,l3:TCubeLocation;
    lu,lf,ll,lr,lb,ld:TCubeLocation;

begin
  if message.Msg=msgSIMPR then
   begin
    //ѕќЋ”„»Ћ» —ќќЅў≈Ќ»≈!!!!!!!!!!
    cu:=cube.GetColor(5,2,2);
    cf:=cube.GetColor(1,2,2);
    cl:=cube.GetColor(3,2,2);
    cr:=cube.GetColor(4,2,2);
    cb:=cube.GetColor(2,2,2);
    cd:=cube.GetColor(6,2,2);
    lu:=5;
    lf:=1;
    ll:=3;
    lb:=2;
    lr:=4;
    ld:=6;
   //REMARKS 1 - top
   //        2 - bottom
   //        3 - left
   //        4 - right
   //        5 - up
   //        6 - down
    Res:=false;
    if message.WParamHi=0 then
    begin
     //”—Ћќ¬»≈!!!!!!!!!!
     case message.WParamLo of
      //таблица1
      1 : begin
           Cube.ColorToLocation(cu,cf,l1,l2); // верх - фасад
           case message.LParam of
            1: begin //крестик1
                if Cube.CheckEnd1() then Res:=true;
               end;
            2: begin // в->в
                if l1=lu then Res:=true;
               end;
            3: begin // ф->ф
                if l2=lf then Res:=true;
               end;
            4: begin // в->п
                if l1=lr then Res:=true;
               end;
            5: begin // ф->п
                if l2=lr then Res:=true;
               end;
            6: begin // в->л
                if l1=ll then Res:=true;
               end;
            7: begin // ф->л
                if l2=ll then Res:=true;
               end;
            8: begin // в->ф
                if l1=lf then Res:=true;
               end;
            9: begin // ф->в
                if l2=lu then Res:=true;
               end;
            10: begin // в->н
                if l1=ld then Res:=true;
               end;
            11: begin // ф->н
                if l2=ld then Res:=true;
               end;
            12: begin // ф->т
                if l2=lb then Res:=true;
               end;
            13: begin // в->т
                if l1=lb then Res:=true;
               end;
           end; {case}
          end;
      //таблица2
      2 : begin
           Cube.ColorToLocation(cu,cf,cl,l1,l2,l3); // верх - фасад - лево
           case message.LParam of
            1: begin //верх
                if Cube.CheckEnd2() then Res:=true;
               end;
            2: begin // в->в
                if l1=lu then Res:=true;
               end;
            3: begin // в->ф
                if l1=lf then Res:=true;
               end;
            4: begin // в->л
                if l1=ll then Res:=true;
               end;
            5: begin // в->п
                if l1=lr then Res:=true;
               end;
            6: begin // в->т
                if l1=lb then Res:=true;
               end;
            7: begin // в->н
                if l1=ld then Res:=true;
               end;
            8: begin // ф->в
                if l2=lu then Res:=true;
               end;
            9: begin // ф->ф
                if l2=lf then Res:=true;
               end;
            10: begin // ф->л
                if l2=ll then Res:=true;
               end;
            11: begin // ф->п
                if l2=lr then Res:=true;
               end;
            12: begin // ф->т
                if l2=lb then Res:=true;
               end;
            13: begin // ф->н
                if l2=ld then Res:=true;
               end;
            14: begin // л->в
                if l3=lu then Res:=true;
               end;
            15: begin // л->ф
                if l3=lf then Res:=true;
               end;
            16: begin // л->л
                if l3=ll then Res:=true;
               end;
            17: begin // л->п
                if l3=lr then Res:=true;
               end;
            18: begin // л->т
                if l3=lb then Res:=true;
               end;
            19: begin // л->н
                if l3=ld then Res:=true;
               end;
           end; {case}
          end; {2}
      //таблица3
      3 : begin
           Cube.ColorToLocation(cf,cl,l1,l2); // фасад - лево
           case message.LParam of
            1: begin //2*верх
                if Cube.CheckEnd3() then Res:=true;
               end;
            2: begin // ф->ф
                if l1=lf then Res:=true;
               end;
            3: begin // ф->л
                if l1=ll then Res:=true;
               end;
            4: begin // ф->т
                if l1=lb then Res:=true;
               end;
            5: begin // ф->п
                if l1=lr then Res:=true;
               end;
            6: begin // ф->н
                if l1=ld then Res:=true;
               end;
            7: begin // л->ф
                if l2=lf then Res:=true;
               end;
            8: begin // л->л
                if l2=ll then Res:=true;
               end;
            9: begin // л->т
                if l2=lb then Res:=true;
               end;
            10: begin // л->п
                if l2=lr then Res:=true;
               end;
            11: begin // л->н
                if l2=ld then Res:=true;
               end;
            12: begin //2*низ
                if Cube.CheckEnd3d() then Res:=true;
               end;
           end; {case}
          end; {3}
      //таблица4
      4 : begin
           Cube.ColorToLocation(cu,cf,l1,l2); // верх - фасад
           case message.LParam of
            1: begin //крестик2(не фикс)
                if Cube.CheckEnd4() then Res:=true;
               end;
            2: begin // ф->ф
                if l2=lf then Res:=true;
               end;
            3: begin // ф->л
                if l2=ll then Res:=true;
               end;
            4: begin // ф->т
                if l2=lb then Res:=true;
               end;
            5: begin // ф->п
                if l2=lr then Res:=true;
               end;
            6: begin // ф->в
                if l2=lu then Res:=true;
               end;
            7: begin // в->ф
                if l1=lf then Res:=true;
               end;
            8: begin // в->л
                if l1=ll then Res:=true;
               end;
            9: begin // в->т
                if l1=lb then Res:=true;
               end;
            10: begin // в->п
                if l1=lr then Res:=true;
               end;
            11: begin // в->в
                if l1=lu then Res:=true;
               end;
           end; {case}
          end; {4}
      //таблица5
      5 : begin
           case message.LParam of
            1: begin   {1}
                Cube.ColorToLocation(cu,cf,l1,l2); // верх - фасад
                if l2=lf then Res:=true;
               end;
            2: begin   {2}
                Cube.ColorToLocation(cu,cr,l1,l2); // верх - право
                if l2=lr then Res:=true;
               end;
            3: begin   {3}
                Cube.ColorToLocation(cu,cb,l1,l2); // верх - тыл
                if l2=lb then Res:=true;
               end;
           end; {case}
          end; {5}
      //таблица6
      6 : begin
           Cube.ColorToLocation(cu,cf,cl,l1,l2,l3); // верх - фасад - лево
           case message.LParam of
            1: begin //верх (не фикс)
                if Cube.CheckEnd6() then Res:=true;
               end;
            2: begin // ф->ф
                if l2=lf then Res:=true;
               end;
            3: begin // ф->л
                if l2=ll then Res:=true;
               end;
            4: begin // ф->т
                if l2=lb then Res:=true;
               end;
            5: begin // ф->п
                if l2=lr then Res:=true;
               end;
            6: begin // ф->в
                if l2=lu then Res:=true;
               end;
            7: begin // в->ф
                if l1=lf then Res:=true;
               end;
            8: begin // в->л
                if l1=ll then Res:=true;
               end;
            9: begin // в->т
                if l1=lb then Res:=true;
               end;
            10: begin // в->п
                if l1=lr then Res:=true;
               end;
            11: begin // в->в
                if l1=lu then Res:=true;
               end;
            12: begin // л->ф
                if l3=lf then Res:=true;
               end;
            13: begin // л->л
                if l3=ll then Res:=true;
               end;
            14: begin // л->т
                if l3=lb then Res:=true;
               end;
            15: begin // л->п
                if l3=lr then Res:=true;
               end;
            16: begin // л->в
                if l3=lu then Res:=true;
               end;
           end; {case}
          end; {6}
      //таблица7
      7 : begin
           Cube.ColorToLocation(cu,cf,cr,l1,l2,l3); // верх - фасад - право
           case message.LParam of
            1: begin // ф->ф
                if l2=lf then Res:=true;
               end;
            2: begin // ф->в
                if l2=lu then Res:=true;
               end;
            3: begin // ф->п
                if l2=lr then Res:=true;
               end;
            4: begin // 2->в
                Cube.ColorToLocation(cu,cr,cb,l1,l2,l3); // верх - право - тыл
                if l1=lu then Res:=true;
               end;
            5: begin // 3->в
                Cube.ColorToLocation(cu,cb,cl,l1,l2,l3); // верх - тыл - лево
                if l1=lu then Res:=true;
               end;
           end; {case}
          end; {6}
     end; {case}
    end;
    if message.WParamHi=1 then
    begin
    //ƒействие!!!!!!!!!!
     case message.WParamLo of
      //таблица 1
      1 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_CW1);
               end;
            2: begin
                cube.AnimatedRotate(_CW1);
               end;
            3: begin
                cube.AnimatedRotate(_up3);
               end;
            4: begin
                cube.AnimatedRotate(_up3);
               end;
            5: begin
                cube.AnimatedRotate(_down1);
               end;
            6: begin
                cube.AnimatedRotate(_left1);
               end;
            7: begin
                cube.AnimatedRotate(_down1);
               end;
            8: begin
                cube.AnimatedRotate(_right3);
               end;
            9: begin
                cube.AnimatedRotate(_right3);
               end;
            10: begin
                cube.AnimatedRotate(_CCW1);
               end;
            11: begin
                cube.AnimatedRotate(_CCW1);
               end;
            12: begin
                cube.AnimatedRotate(_down3);
               end;
            13: begin
                cube.AnimatedRotate(_up1);
               end;
            14: begin
                cube.AnimatedRotate(_right1);
               end;
            15: begin
                cube.AnimatedRotate(_left3);
               end;
            16: begin
                cube.AnimatedRotate(_right2);
               end;
            17: begin
                cube.AnimatedRotate(_left2);
               end;
            18: begin
                cube.AnimatedRotate(_left);
               end;
            19: begin
                cube.AnimatedRotate(_CW3);
               end;
            20: begin
                cube.AnimatedRotate(_CW3);
               end;
            21: begin
                showmessage('Error1');
               end;
           end; {case}
          end; {1}
      //таблица 2
      2 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_CW1);
               end;
            2: begin
                cube.AnimatedRotate(_CW1);
               end;
            3: begin
                cube.AnimatedRotate(_CCW1);
               end;
            4: begin
                cube.AnimatedRotate(_up3);
               end;
            5: begin
                cube.AnimatedRotate(_up3);
               end;
            6: begin
                cube.AnimatedRotate(_down3);
               end;
            7: begin
                cube.AnimatedRotate(_down3);
               end;
            8: begin
                cube.AnimatedRotate(_down1);
               end;
            9: begin
                cube.AnimatedRotate(_down1);
               end;
            10: begin
                cube.AnimatedRotate(_up1);
               end;
            11: begin
                cube.AnimatedRotate(_up1);
               end;
            12: begin
                cube.AnimatedRotate(_right3);
               end;
            13: begin
                cube.AnimatedRotate(_right3);
               end;
            14: begin
                cube.AnimatedRotate(_right3);
               end;
            15: begin
                cube.AnimatedRotate(_left3);
               end;
            16: begin
                cube.AnimatedRotate(_left3);
               end;
            17: begin
                cube.AnimatedRotate(_left);
               end;
            18: begin
                cube.AnimatedRotate(_CCW1);
               end;
            19: begin
                cube.AnimatedRotate(_left3);
               end;
            20: begin
                showmessage('Error2');
               end;
           end; {case}
          end; {2}
      //таблица 3
      3 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_CW1);
               end;
            2: begin
                cube.AnimatedRotate(_CW1);
               end;
            3: begin
                cube.AnimatedRotate(_CCW1);
               end;
            4: begin
                cube.AnimatedRotate(_CCW1);
               end;
            5: begin
                cube.AnimatedRotate(_down1);
               end;
            6: begin
                cube.AnimatedRotate(_down1);
               end;
            7: begin
                cube.AnimatedRotate(_up1);
               end;
            8: begin
                cube.AnimatedRotate(_up1);
               end;
            9: begin
                cube.AnimatedRotate(_up3);
               end;
            10: begin
                cube.AnimatedRotate(_down3);
               end;
            11: begin
                cube.AnimatedRotate(_right3);
               end;
            12: begin
                cube.AnimatedRotate(_right3);
               end;
            13: begin
                cube.AnimatedRotate(_right3);
               end;
            14: begin
                cube.AnimatedRotate(_right3);
               end;
            15: begin
                cube.AnimatedRotate(_right3);
               end;
            16: begin
                cube.AnimatedRotate(_left3);
               end;
            17: begin
                cube.AnimatedRotate(_left3);
               end;
            18: begin
                cube.AnimatedRotate(_left3);
               end;
            19: begin
                cube.AnimatedRotate(_left3);
               end;
            20: begin
                cube.AnimatedRotate(_left3);
               end;
            21: begin
                cube.AnimatedRotate(_CCW3);
               end;
            22: begin
                cube.AnimatedRotate(_CW3);
               end;
            23: begin
                cube.AnimatedRotate(_left);
               end;
            24: begin
                cube.AnimatedRotate(_down);
               end;
            25: begin
                cube.AnimatedRotate(_down);
               end;
            26: begin
                showmessage('Error3');
               end;
           end; {case}
          end; {3}
      //таблица 4
      4 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_CW1);
               end;
            2: begin
                cube.AnimatedRotate(_CCW1);
               end;
            3: begin
                cube.AnimatedRotate(_up3);
               end;
            4: begin
                cube.AnimatedRotate(_down3);
               end;
            5: begin
                cube.AnimatedRotate(_left1);
               end;
            6: begin
                cube.AnimatedRotate(_left1);
               end;
            7: begin
                cube.AnimatedRotate(_left1);
               end;
            8: begin
                cube.AnimatedRotate(_left1);
               end;
            9: begin
                cube.AnimatedRotate(_right1);
               end;
            10: begin
                cube.AnimatedRotate(_right1);
               end;
            11: begin
                cube.AnimatedRotate(_CCW3);
               end;
            12: begin
                cube.AnimatedRotate(_CCW3);
               end;
            13: begin
                cube.AnimatedRotate(_CW3);
               end;
            14: begin
                cube.AnimatedRotate(_CW3);
               end;
            15: begin
                cube.AnimatedRotate(_down1);
               end;
            16: begin
                cube.AnimatedRotate(_up1);
               end;
            17: begin
                cube.AnimatedRotate(_left);
               end;
            18: begin
                showmessage('Error4');
               end;
           end; {case}
          end; {4}
      //таблица 5
      5 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_up3);
               end;
            2: begin
                cube.AnimatedRotate(_up3);
               end;
            3: begin
                cube.AnimatedRotate(_up3);
               end;
            4: begin
                cube.AnimatedRotate(_up3);
               end;
            5: begin
                cube.AnimatedRotate(_up3);
               end;
            6: begin
                cube.AnimatedRotate(_up3);
               end;
            7: begin
                cube.AnimatedRotate(_up3);
               end;
            8: begin
                cube.AnimatedRotate(_up3);
               end;
            9: begin
                cube.AnimatedRotate(_right2);
               end;
            10: begin
                cube.AnimatedRotate(_right2);
               end;
            11: begin
                cube.AnimatedRotate(_right2);
               end;
            12: begin
                cube.AnimatedRotate(_right2);
               end;
            13: begin
                cube.AnimatedRotate(_right2);
               end;
            14: begin
                cube.AnimatedRotate(_right2);
               end;
            15: begin
                cube.AnimatedRotate(_right2);
               end;
            16: begin
                cube.AnimatedRotate(_right2);
               end;
            17: begin
                cube.AnimatedRotate(_left1);
               end;
            18: begin
                cube.AnimatedRotate(_left1);
               end;
            19: begin
                cube.AnimatedRotate(_right1);
               end;
            20: begin
                cube.AnimatedRotate(_CW1);
               end;
            21: begin
                cube.AnimatedRotate(_CW1);
               end;
            22: begin
                cube.AnimatedRotate(_CW1);
               end;
            23: begin
                cube.AnimatedRotate(_CW1);
               end;
            24: begin
                cube.AnimatedRotate(_CW1);
               end;
            25: begin
                cube.AnimatedRotate(_CW1);
               end;
            26: begin
                cube.AnimatedRotate(_CW1);
               end;
            27: begin
                cube.AnimatedRotate(_CW1);
               end;
            28: begin
                cube.AnimatedRotate(_left);
               end;
            29: begin
                cube.AnimatedRotate(_right1);
               end;
            30: begin
                showmessage('Error5');
               end;
           end; {case}
          end; {5}
      //таблица 6
      6 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_CW1);
               end;
            2: begin
                cube.AnimatedRotate(_CW1);
               end;
            3: begin
                cube.AnimatedRotate(_CCW1);
               end;
            4: begin
                cube.AnimatedRotate(_CCW1);
               end;
            5: begin
                cube.AnimatedRotate(_down1);
               end;
            6: begin
                cube.AnimatedRotate(_up1);
               end;
            7: begin
                cube.AnimatedRotate(_up3);
               end;
            8: begin
                cube.AnimatedRotate(_down3);
               end;
            9: begin
                cube.AnimatedRotate(_left);
               end;
            10: begin
                showmessage('Error6');
               end;
           end; {case}
          end; {6}
      //таблица 7
      7 : begin
           case message.LParam of
            1: begin
                cube.AnimatedRotate(_CW1);
               end;
            2: begin
                cube.AnimatedRotate(_CW1);
               end;
            3: begin
                cube.AnimatedRotate(_CW1);
               end;
            4: begin
                cube.AnimatedRotate(_CW1);
               end;
            5: begin
                cube.AnimatedRotate(_CW1);
               end;
            6: begin
                cube.AnimatedRotate(_CW1);
               end;
            7: begin
                cube.AnimatedRotate(_CW1);
               end;
            8: begin
                cube.AnimatedRotate(_CW1);
               end;
            9: begin
                cube.AnimatedRotate(_CCW1);
               end;
            10: begin
                cube.AnimatedRotate(_CCW1);
               end;
            11: begin
                cube.AnimatedRotate(_CCW1);
               end;
            12: begin
                cube.AnimatedRotate(_CCW1);
               end;
            13: begin
                cube.AnimatedRotate(_CCW1);
               end;
            14: begin
                cube.AnimatedRotate(_CCW1);
               end;
            15: begin
                cube.AnimatedRotate(_CCW1);
               end;
            16: begin
                cube.AnimatedRotate(_CCW1);
               end;
            17: begin
                cube.AnimatedRotate(_up3);
               end;
            18: begin
                cube.AnimatedRotate(_up3);
               end;
            19: begin
                cube.AnimatedRotate(_up3);
               end;
            20: begin
                cube.AnimatedRotate(_up3);
               end;
            21: begin
                cube.AnimatedRotate(_up3);
               end;
            22: begin
                cube.AnimatedRotate(_up3);
               end;
            23: begin
                cube.AnimatedRotate(_up3);
               end;
            24: begin
                cube.AnimatedRotate(_up3);
               end;
            25: begin
                cube.AnimatedRotate(_down3);
               end;
            26: begin
                cube.AnimatedRotate(_down3);
               end;
            27: begin
                cube.AnimatedRotate(_down3);
               end;
            28: begin
                cube.AnimatedRotate(_down3);
               end;
            29: begin
                cube.AnimatedRotate(_down3);
               end;
            30: begin
                cube.AnimatedRotate(_down3);
               end;
            31: begin
                cube.AnimatedRotate(_down3);
               end;
            32: begin
                cube.AnimatedRotate(_down3);
               end;
            33: begin
                cube.AnimatedRotate(_left1);
               end;
            34: begin
                cube.AnimatedRotate(_left1);
               end;
            36: begin
                cube.AnimatedRotate(_right1);
               end;
            37: begin
                cube.AnimatedRotate(_right1);
               end;
            38: begin
                cube.AnimatedRotate(_left);
               end;
            35: begin
                showmessage('Error7');
               end;
           end; {case}
          end; {7}
     end;{case}
     Res:=true;
    end;
 //¬ыдали результат!!!!!!!!!
   if res then   message.Result:=1
   else   message.Result:=0;
   end
    else inherited WndProc(Message);
end;





end.
