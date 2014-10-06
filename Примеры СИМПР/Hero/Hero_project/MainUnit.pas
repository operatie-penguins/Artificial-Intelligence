unit MainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, ExtCtrls, Menus,

 GameUnit;

const
  sCondition = 0;
  sAction = 1;

type
  TMainForm = class(TForm)
    MainMenu1: TMainMenu;
    GameItem: TMenuItem;
    StartItem: TMenuItem;
    N1: TMenuItem;
    ExitItem: TMenuItem;
    ParametersItem: TMenuItem;
    FieldItem: TMenuItem;
    HeroItem: TMenuItem;
    BonusesItem: TMenuItem;
    MonstersItem: TMenuItem;
    HelpItem: TMenuItem;
    AboutItem: TMenuItem;
    PauseItem: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure AboutItemClick(Sender: TObject);
    procedure MonstersItemClick(Sender: TObject);
    procedure BonusesItemClick(Sender: TObject);
    procedure HeroItemClick(Sender: TObject);
    procedure FieldItemClick(Sender: TObject);
    procedure ExitItemClick(Sender: TObject);
    procedure StartItemClick(Sender: TObject);
    procedure PauseItemClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    SimprMessage : Cardinal;
    Start : boolean;
    procedure WndProc(var Message: TMessage); override;
    procedure OnSimpr ( var Message : TMessage );
    procedure EndGame ( const Win : boolean; const WinMessage : string);
    procedure WinBattle ( const WinMessage : string );
    procedure PaintGame;
    procedure StartGame;
  end;

var
  MainForm: TMainForm;
  Game : TGame;
  ScreenX, ScreenY : Integer;

implementation

{$R *.dfm}

uses AboutUnit, FieldUnit, HeroUnit, BonusesUnit, MonstersUnit, ClassUnit,
     TableConditionUnit, TableActionUnit, GameViewUnit, StatusUnit;

procedure TMainForm.AboutItemClick(Sender: TObject);
var i : integer;
    present : boolean;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TAboutForm) then
      begin
        MDIChildren[i].Show;
        present := true;
      end;
  if not(present) then
    with TAboutForm.Create(Self) do
      Show;
end;

procedure TMainForm.BonusesItemClick(Sender: TObject);
var i : integer;
    present : boolean;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TBonusesForm) then
      begin
        MDIChildren[i].Show;
        present := true;
      end;
  if not(present) then
    with TBonusesForm.Create(Self) do
      Show;
end;

procedure TMainForm.EndGame(const Win: boolean; const WinMessage: string);
var i : integer;
    present : boolean;
begin
  if Win then
    MessageDlg(WinMessage, mtInformation, [mbOK],0)
  else
    MessageDlg(WinMessage, mtWarning, [mbOK], 0);
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TGameViewForm) then
      begin
        MDIChildren[i].Close;
        present := true;
      end;
  if not(present) then
    MessageDlg('Bugs with GameViewForm!', mtError, [mbOK], 0); 
end;

procedure TMainForm.ExitItemClick(Sender: TObject);
begin
  Close;
end;

procedure TMainForm.FieldItemClick(Sender: TObject);
var i : integer;
    present : boolean;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TFieldForm) then
      begin
        MDIChildren[i].Show;
        present := true;
      end;
  if not(present) then
    with TFieldForm.Create(Self) do
      Show;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  Randomize;
  SimprMessage := RegisterWindowMessage('SimprMessage');
  if SimprMessage = 0 then
    begin
      MessageDlg('Cannot register window message "SimprMessage!"', mtError, [mbOK], 0);
      Close;
    end;
  Start := false;
  Game := TGame.Create;
end;

procedure TMainForm.HeroItemClick(Sender: TObject);
var i : integer;
    present : boolean;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is THeroForm) then
      begin
        MDIChildren[i].Show;
        present := true;
      end;
  if not(present) then
    with THeroForm.Create(Self) do
      Show;
end;

procedure TMainForm.MonstersItemClick(Sender: TObject);
var i : integer;
    present : boolean;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TMonstersForm) then
      begin
        MDIChildren[i].Show;
        present := true;
      end;
  if not(present) then
    with TMonstersForm.Create(Self) do
      Show;
end;

procedure TMainForm.OnSimpr( var Message: TMessage);
var MessageType : integer;
    TableNumber : integer;
    ActionNumber : integer;
    Res : boolean;
    Result1 : integer;
begin
  Res := false;
  MessageType := Message.WParamHi;
  TableNumber := Message.WParamLo;
  ActionNumber := Message.LParam;
  if ActionNumber = 0 then
    begin
      ShowMessage('Stop');
      Exit;
    end;
  try
  case MessageType of
    sCondition :
      begin
        case TableNumber of
          1 : Res := cFirstTable(ActionNumber);
          2 : Res := cSecondTable(ActionNumber);
          3 : Res := cThirdTable(ActionNumber);
          4 : Res := cFourthTable(ActionNumber);
          5 : Res := cFifthTable(ActionNumber);
          6 : Res := cSixthTable(ActionNumber);
          7 : Res := cSeventhTable(ActionNumber);
          8 : Res := cEighthTable(ActionNumber);
          9 : Res := cNinethTable(ActionNumber);
        end;
      end;
    sAction    :
      begin
        Res := true;
        case TableNumber of
          1 : aFirstTable(ActionNumber);
          2 : aSecondTable(ActionNumber);
          3 : aThirdTable(ActionNumber);
          4 : aFourthTable(ActionNumber);
          5 : aFifthTable(ActionNumber);
          6 : aSixthTable(ActionNumber);
          7 : aSeventhTable(ActionNumber);
          8 : aEighthTable(ActionNumber);
          9 : aNinethTable(ActionNumber);
        end;
        if TableNumber <> 1 then
          PaintGame;
      end;
  end;
  except
    Res := false;
  end;  
  if Res then
    Result1 := 1
  else
    Result1 := 0;
  Message.Result := Result1;
end;

procedure TMainForm.PaintGame;
var i, j, cx, cy : integer;
    present : boolean;
    f : TGameViewForm;
    s : TStatusForm;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TGameViewForm) then
      begin
        f := (MDIChildren[i] as TGameViewForm);
        present := true;
      end;
  if not(present) then
    f := TGameViewForm.Create(Self);
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TStatusForm) then
      begin
        s := (MDIChildren[i] as TStatusForm);
        present := true;
      end;
  if not(present) then
    s := TStatusForm.Create(Self);
  s.HeroLifeText.Caption := inttostr(Game.Hero.Life);
  s.HeroAttackText.Caption := inttostr(Game.Hero.Attack);
  s.HeroDefenceText.Caption := inttostr(Game.Hero.Defence);
  s.HeroXText.Caption := inttostr(Game.Hero.Coords.x);
  s.HeroYText.Caption := inttostr(Game.Hero.Coords.y);
  if Game.CurrentMonster <> nil then
    begin
      s.MonsterLifeText.Caption := inttostr(Game.CurrentMonster.Life);
      s.MonsterAttackText.Caption := inttostr(Game.CurrentMonster.Attack);
      s.MonsterDefenceText.Caption := inttostr(Game.CurrentMonster.Defence);
      s.MonsterXText.Caption := inttostr(Game.CurrentMonster.Coords.x);
      s.MonsterYText.Caption := inttostr(Game.CurrentMonster.Coords.y);
    end;
  if not(Game.Battle) then
    begin
      for i := 0 to 18 do
        for j := 0 to 12 do
          f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,i*56,j*56,13);

      for i := -1 to Game.Field.FieldWidth do
        for j := -1 to Game.Field.FieldHeight do
          begin
            cx:=i-ScreenX;
            cy:=j-ScreenY;

            f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,0);
              if (Game.Field.FieldMatrix[i, j] is THero) then
                 f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,1)
              else
                if (Game.Field.FieldMatrix[i, j] is TLifeBonus) then
                  f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,5)
                else
                  if (Game.Field.FieldMatrix[i, j] is TAttackBonus) then
                    f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,3)
                  else
                    if (Game.Field.FieldMatrix[i, j] is TDefenceBonus) then
                      f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,4)
                    else
                      if (Game.Field.FieldMatrix[i, j] is TMonster) then
                        f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,11)
                      else
                        if (Game.Field.FieldMatrix[i, j] is TObstacle) then
                          f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,7)
                        else
                          if (Game.Field.FieldMatrix[i, j] is TExit) then
                            f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,2)
                          else
                            if (Game.Field.FieldMatrix[i, j] is TObject) then
                              f.DXImageList1.Items.Items[0].Draw(f.DXDraw1.Surface,(cx+1)*56,(cy+1)*56,6)
          end;
    end;
  f.DXDraw1.Flip;
  Application.ProcessMessages;
  i := 0;
  while i<100000000 do
    inc(i);
end;

procedure TMainForm.StartGame;
var i : integer;
    present : boolean;
    f : TStatusForm;
begin
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TGameViewForm) then
      begin
        MDIChildren[i].Show;
        with (MDIChildren[i] as TGameViewForm) do
          begin
            ScrollBar1.Max:= Game.Field.FieldWidth+2;
            ScrollBar2.Max:= Game.Field.FieldHeight+2;
{            GameViewGrid.ColCount := Game.Field.FieldWidth+2;
            GameViewGrid.RowCount := Game.Field.FieldHeight+2;
}          end;
        present := true;
      end;
  if not(present) then
    with TGameViewForm.Create(Self) do
      begin
        Show;
        ScrollBar1.Max:= Game.Field.FieldWidth+2;
        ScrollBar2.Max:= Game.Field.FieldHeight+2;
{        GameViewGrid.ColCount := Game.Field.FieldWidth+2;
        GameViewGrid.RowCount := Game.Field.FieldHeight+2;
}      end;
  present := false;
  for i := 0 to MDIChildCount - 1 do
    if (MDIChildren[i] is TStatusForm) then
      begin
        MDIChildren[i].Show;
        present := true;
        Game.AssignForm((MDIChildren[i] as TStatusForm));
      end;
  if not(present) then
    begin
      f := TStatusForm.Create(Self);
      f.Show;
      Game.AssignForm((f as TStatusForm));
    end;
  PaintGame;
end;

procedure TMainForm.StartItemClick(Sender: TObject);
begin
  Start := true;
end;

procedure TMainForm.WinBattle(const WinMessage: string);
begin
  MessageDlg(WinMessage, mtInformation, [mbOK], 0);
end;

procedure TMainForm.WndProc(var Message: TMessage);
begin
  if (Message.Msg = SimprMessage)and(not PauseItem.Checked) then
    OnSimpr ( Message )
  else
    inherited WndProc(Message);
end;

procedure TMainForm.PauseItemClick(Sender: TObject);
begin
  PauseItem.Checked:= not PauseItem.Checked;
end;

end.
