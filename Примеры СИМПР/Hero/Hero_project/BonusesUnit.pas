unit BonusesUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, Spin, Buttons, ComCtrls;

type
  TBonusesForm = class(TForm)
    PageControl1: TPageControl;
    LifeSheet: TTabSheet;
    AttackSheet: TTabSheet;
    DefenceSheet: TTabSheet;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Bevel1: TBevel;
    Bevel2: TBevel;
    Bevel3: TBevel;
    OneLifeEdit: TSpinEdit;
    FiveLifeEdit: TSpinEdit;
    TenLifeEdit: TSpinEdit;
    AllLifeEdit: TSpinEdit;
    PerOneLifeEdit: TSpinEdit;
    PerFiveLifeEdit: TSpinEdit;
    PerTenLifeEdit: TSpinEdit;
    PerAllLifeEdit: TSpinEdit;
    ApplyLifeButton: TSpeedButton;
    Label5: TLabel;
    AllBonusesText: TStaticText;
    CancelButton: TSpeedButton;
    OKButton: TSpeedButton;
    GroupBox3: TGroupBox;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Bevel7: TBevel;
    Bevel8: TBevel;
    Bevel9: TBevel;
    OneAttackEdit: TSpinEdit;
    FiveAttackEdit: TSpinEdit;
    TenAttackEdit: TSpinEdit;
    AllAttackEdit: TSpinEdit;
    PerOneAttackEdit: TSpinEdit;
    PerFiveAttackEdit: TSpinEdit;
    PerTenAttackEdit: TSpinEdit;
    PerAllAttackEdit: TSpinEdit;
    ApplyAttackButton: TSpeedButton;
    GroupBox2: TGroupBox;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Bevel4: TBevel;
    Bevel5: TBevel;
    Bevel6: TBevel;
    OneDefenceEdit: TSpinEdit;
    FiveDefenceEdit: TSpinEdit;
    TenDefenceEdit: TSpinEdit;
    AllDefenceEdit: TSpinEdit;
    PerOneDefenceEdit: TSpinEdit;
    PerFiveDefenceEdit: TSpinEdit;
    PerTenDefenceEdit: TSpinEdit;
    PerAllDefenceEdit: TSpinEdit;
    ApplyDefenceButton: TSpeedButton;
    Bevel10: TBevel;
    procedure ApplyDefenceButtonClick(Sender: TObject);
    procedure ApplyAttackButtonClick(Sender: TObject);
    procedure ApplyLifeButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure CancelButtonClick(Sender: TObject);
    procedure OKButtonClick(Sender: TObject);
    procedure ChangeLifeParameters ( Sender : TObject );
    procedure ChangeAttackParamteers ( Sender : TObject );
    procedure ChangeDefenceParameters ( Sender : TObject );
    procedure ChangeAllLife ( Sender : TObject );
    procedure ChangeAllAttack ( Sender : TObject );
    procedure ChangeAllDefence ( Sender : Tobject );
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.dfm}

uses MainUnit;

procedure TBonusesForm.ApplyAttackButtonClick(Sender: TObject);
begin
  Game.SetAttackParameters(OneAttackEdit.Value, FiveAttackEdit.Value, TenAttackEdit.Value);
end;

procedure TBonusesForm.ApplyDefenceButtonClick(Sender: TObject);
begin
  Game.SetDefenceParameters(OneDefenceEdit.Value, FiveDefenceEdit.Value, TenDefenceEdit.Value);
end;

procedure TBonusesForm.ApplyLifeButtonClick(Sender: TObject);
begin
  Game.SetLifeParameters(OneLifeEdit.Value, FiveLifeEdit.Value, TenLifeEdit.Value);
end;

procedure TBonusesForm.CancelButtonClick(Sender: TObject);
begin
  Close;
end;

procedure TBonusesForm.ChangeAttackParamteers(Sender: TObject);
begin
  AllAttackEdit.Value := OneAttackEdit.Value + FiveAttackEdit.Value + TenAttackEdit.Value;
  PerOneAttackEdit.Value := Round(OneAttackEdit.Value/AllAttackEdit.Value*100);
  PerFiveAttackEdit.Value := Round(FiveAttackEdit.Value/AllAttackEdit.Value*100);
  PerTenAttackEdit.Value := Round(TenAttackEdit.Value/AllAttackEdit.Value*100);
end;

procedure TBonusesForm.ChangeAllAttack(Sender: TObject);
begin
  OneAttackEdit.Value := Round(PerOneAttackEdit.Value*AllAttackEdit.Value/100);
  FiveAttackEdit.Value := Round(PerFiveAttackEdit.Value*AllAttackEdit.Value/100);
  TenAttackEdit.Value := Round(PerTenAttackEdit.Value*AllAttackEdit.Value/100);
end;

procedure TBonusesForm.ChangeDefenceParameters(Sender: TObject);
begin
  AllDefenceEdit.Value := OneDefenceEdit.Value + FiveDefenceEdit.Value + TenDefenceEdit.Value;
  PerOneDefenceEdit.Value := Round(OneDefenceEdit.Value/AllDefenceEdit.Value*100);
  PerFiveDefenceEdit.Value := Round(FiveDefenceEdit.Value/AllDefenceEdit.Value*100);
  PerTenDefenceEdit.Value := Round(TenDefenceEdit.Value/AllDefenceEdit.Value*100);
end;

procedure TBonusesForm.ChangeAllDefence(Sender: Tobject);
begin
  OneDefenceEdit.Value := Round(PerOneDefenceEdit.Value*AllDefenceEdit.Value/100);
  FiveDefenceEdit.Value := Round(PerFiveDefenceEdit.Value*AllDefenceEdit.Value/100);
  TenDefenceEdit.Value := Round(PerTenDefenceEdit.Value*AllDefenceEdit.Value/100);
end;

procedure TBonusesForm.ChangeLifeParameters(Sender: TObject);
begin
  AllLifeEdit.Value := OneLifeEdit.Value + FiveLifeEdit.Value + TenLifeEdit.Value;
  PerOneLifeEdit.Value := Round(OneLifeEdit.Value/AllLifeEdit.Value*100);
  PerFiveLifeEdit.Value := Round(FiveLifeEdit.Value/AllLifeEdit.Value*100);
  PerTenLifeEdit.Value := Round(TenLifeEdit.Value/AllLifeEdit.Value*100);
end;

procedure TBonusesForm.ChangeAllLife(Sender: TObject);
begin
  OneLifeEdit.Value := Round(PerOneLifeEdit.Value*AllLifeEdit.Value/100);
  FiveLifeEdit.Value := Round(PerFiveLifeEdit.Value*AllLifeEdit.Value/100);
  TenLifeEdit.Value := Round(PerTenLifeEdit.Value*AllLifeEdit.Value/100);
end;

procedure TBonusesForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure TBonusesForm.FormCreate(Sender: TObject);
begin
//
end;

procedure TBonusesForm.OKButtonClick(Sender: TObject);
begin
  Game.SetLifeParameters(OneLifeEdit.Value, FiveLifeEdit.Value, TenLifeEdit.Value);
  Game.SetAttackParameters(OneAttackEdit.Value, FiveAttackEdit.Value, TenAttackEdit.Value);
  Game.SetDefenceParameters(OneDefenceEdit.Value, FiveDefenceEdit.Value, TenDefenceEdit.Value);
  Close;
end;

end.
