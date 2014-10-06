unit MonstersUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, Grids, ValEdit, Buttons, Spin;

type
  TMonstersForm = class(TForm)
    MonsterView: TListView;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    NumberEdit: TSpinEdit;
    AddButton: TSpeedButton;
    EditButton: TSpeedButton;
    DeleteButton: TSpeedButton;
    ApplyButton: TSpeedButton;
    CancelButton: TSpeedButton;
    OKButton: TSpeedButton;
    LifeEdit: TSpinEdit;
    AttackEdit: TSpinEdit;
    DefenceEdit: TSpinEdit;
    procedure ApplyButtonClick(Sender: TObject);
    procedure DeleteButtonClick(Sender: TObject);
    procedure EditButtonClick(Sender: TObject);
    procedure AddButtonClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure CancelButtonClick(Sender: TObject);
    procedure OKButtonClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.dfm}

procedure TMonstersForm.AddButtonClick(Sender: TObject);
begin
//
end;

procedure TMonstersForm.ApplyButtonClick(Sender: TObject);
begin
//
end;

procedure TMonstersForm.CancelButtonClick(Sender: TObject);
begin
  Close;
end;

procedure TMonstersForm.DeleteButtonClick(Sender: TObject);
begin
//
end;

procedure TMonstersForm.EditButtonClick(Sender: TObject);
begin
//
end;

procedure TMonstersForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure TMonstersForm.FormCreate(Sender: TObject);
begin
//
end;

procedure TMonstersForm.OKButtonClick(Sender: TObject);
begin
//
  Close;
end;

end.
