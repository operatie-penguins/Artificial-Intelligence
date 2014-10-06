program car_washing_proj;

uses
  Forms,
  car_washing in 'car_washing.pas' {frmCarWashing},
  about in 'about.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Модель автомойки';
  Application.CreateForm(TfrmCarWashing, frmCarWashing);
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
