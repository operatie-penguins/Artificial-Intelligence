unit Unit3;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

type
  Trek = class(TForm)
    Ribak_I: TImage;
    vedr_im: TImage;
    ud_im: TImage;
    mash_im: TImage;
    ber_im: TImage;
    Label1: TLabel;
    Label2: TLabel;
    rib_v_mas: TLabel;
    rib_v_vedre: TLabel;
    Label3: TLabel;
    ud_stat: TLabel;
    Label4: TLabel;
    kol_ud: TLabel;
    pokl_stat: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Ribak_IProgress(Sender: TObject; Stage: TProgressStage;
      PercentDone: Byte; RedrawNow: Boolean; const R: TRect;
      const Msg: String);
    procedure Ribak_IStartDock(Sender: TObject;
      var DragObject: TDragDockObject);
    procedure Ribak_IDragDrop(Sender, Source: TObject; X, Y: Integer);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  rek: Trek;

implementation

uses Unit1, dom_f, Unit2;

{$R *.dfm}

procedure Trek.Button1Click(Sender: TObject);
begin
                 rek.ud_im.Picture.LoadFromFile('imm/ud_zak.bmp');
                 sleep(500);
end;

procedure Trek.Ribak_IProgress(Sender: TObject; Stage: TProgressStage;
  PercentDone: Byte; RedrawNow: Boolean; const R: TRect;
  const Msg: String);
begin
ud_im.Top:=ribak_i.Top+50;
ud_im.Left:=ribak_i.Left+20;
end;

procedure Trek.Ribak_IStartDock(Sender: TObject;
  var DragObject: TDragDockObject);
begin
ud_im.Top:=ribak_i.Top+50;
ud_im.Left:=ribak_i.Left+20;
end;

procedure Trek.Ribak_IDragDrop(Sender, Source: TObject; X, Y: Integer);
begin
ud_im.Top:=ribak_i.Top+50;
ud_im.Left:=ribak_i.Left+20;
end;

procedure Trek.FormShow(Sender: TObject);
begin
 rek.rib_v_vedre.caption:=inttostr(ribak.gl.v_rib_v_vedre)+' из '+inttostr(ribak.gl.V_vedra)+' возможных';
 rek.rib_v_mas.caption:=inttostr(ribak.gl.v_rib_v_yash)+' из '+inttostr(ribak.gl.v_yashika)+' возможных';
 rek.kol_ud.Caption:=inttostr(ribak.gl.kol_ud_v_mash);
 rek.vedr_im.Picture.LoadFromFile('imm/vedro.bmp');

end;

end.
