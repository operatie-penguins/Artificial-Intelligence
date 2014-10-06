unit GameViewUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, DXDraws, StdCtrls;

type
  TGameViewForm = class(TForm)
    DXImageList1: TDXImageList;
    DXDraw1: TDXDraw;
    ScrollBar1: TScrollBar;
    ScrollBar2: TScrollBar;
    procedure ScrollBar2Change(Sender: TObject);
    procedure ScrollBar1Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.dfm}

uses MainUnit;

procedure TGameViewForm.ScrollBar2Change(Sender: TObject);
begin
  ScreenY:=ScrollBar2.Position;
  MainForm.PaintGame;
end;

procedure TGameViewForm.ScrollBar1Change(Sender: TObject);
begin
  ScreenX:=ScrollBar1.Position;
  MainForm.PaintGame;
end;

end.
