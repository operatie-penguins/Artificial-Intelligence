program ParkPrj;

uses
  Forms,
  ParkU1 in 'ParkU1.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
