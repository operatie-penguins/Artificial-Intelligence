unit HeroUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Spin, Buttons;

type
  THeroForm = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    LifeEdit: TSpinEdit;
    AttackEdit: TSpinEdit;
    DefenceEdit: TSpinEdit;
    GroupBox2: TGroupBox;
    BonusCheck: TCheckBox;
    MonsterCheck: TCheckBox;
    ExitCheck: TCheckBox;
    CancelButton: TSpeedButton;
    OKButton: TSpeedButton;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure CancelButtonClick(Sender: TObject);
    procedure OKButtonClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.dfm}

uses MainUnit, ClassUnit;

procedure THeroForm.CancelButtonClick(Sender: TObject);
begin
  Close;
end;

procedure THeroForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure THeroForm.FormCreate(Sender: TObject);
begin
//
end;

procedure THeroForm.OKButtonClick(Sender: TObject);
var ga : TGlobalAimes;
begin
  ga := [];
  if BonusCheck.Checked then
    Include(ga, gaBonus);
  if MonsterCheck.Checked then
    Include(ga, gaMonster);
  if ExitCheck.Checked then
    Include(ga, gaExit);
  Game.SetHeroParameters(LifeEdit.Value, AttackEdit.Value, DefenceEdit.Value, ga);
  Close;
end;

end.
