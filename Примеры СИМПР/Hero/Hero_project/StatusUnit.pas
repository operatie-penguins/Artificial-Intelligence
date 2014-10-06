unit StatusUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TStatusForm = class(TForm)
    HeroMemo: TMemo;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    HeroLifeText: TStaticText;
    HeroAttackText: TStaticText;
    HeroDefenceText: TStaticText;
    Label5: TLabel;
    Label6: TLabel;
    HeroXText: TStaticText;
    HeroYText: TStaticText;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    MonsterLifeText: TStaticText;
    MonsterAttackText: TStaticText;
    MonsterDefenceText: TStaticText;
    MonsterXText: TStaticText;
    MonsterYText: TStaticText;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.dfm}

procedure TStatusForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;

end.
