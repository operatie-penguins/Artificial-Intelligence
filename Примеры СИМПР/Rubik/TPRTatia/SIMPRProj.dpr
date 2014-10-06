program SIMPRProj;

uses
  Forms,
  Unit1 in 'Unit1.pas' {CubeForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TCubeForm, CubeForm);
  Application.Run;
end.
