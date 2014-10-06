unit dom_f;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

type
  Tdom = class(TForm)
    mash_im: TImage;
    dom_im: TImage;
    ribak_im: TImage;
    ved_im: TImage;
    ud_im: TImage;
    eda_stat: TLabel;
    ud_v_mash: TLabel;
    rib_v_podvale: TLabel;
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dom: Tdom;

implementation

uses Unit1, Unit2, Unit3;

{$R *.dfm}

procedure Tdom.FormShow(Sender: TObject);

begin
dom.ud_v_mash.Caption:='удочек в машине '+inttostr(ribak.gl.kol_ud_v_mash);
dom.rib_v_podvale.Caption:='в подвале '+inttostr(ribak.t3.v_rib_v_podvale)+' рыб из '+inttostr(ribak.t3.v_podvala)+' возможных';
end;

end.
