unit FieldUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Spin, Buttons;

type
  TFieldForm = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    WidthEdit: TSpinEdit;
    HeightEdit: TSpinEdit;
    GroupBox2: TGroupBox;
    Label3: TLabel;
    SpinEdit1: TSpinEdit;
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

uses MainUnit;

procedure TFieldForm.CancelButtonClick(Sender: TObject);
begin
  Close;
end;

procedure TFieldForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure TFieldForm.FormCreate(Sender: TObject);
begin
//
end;

procedure TFieldForm.OKButtonClick(Sender: TObject);
begin
  Game.SetFieldParameters(WidthEdit.Value, HeightEdit.Value, SpinEdit1.Value);
  Close;
end;

end.
