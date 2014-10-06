program Hero_project;

uses
  Forms,
  MainUnit in 'MainUnit.pas' {MainForm},
  AboutUnit in 'AboutUnit.pas' {AboutForm},
  FieldUnit in 'FieldUnit.pas' {FieldForm},
  HeroUnit in 'HeroUnit.pas' {HeroForm},
  BonusesUnit in 'BonusesUnit.pas' {BonusesForm},
  MonstersUnit in 'MonstersUnit.pas' {MonstersForm},
  ClassUnit in 'ClassUnit.pas',
  GameUnit in 'GameUnit.pas',
  TableConditionUnit in 'TableConditionUnit.pas',
  TableActionUnit in 'TableActionUnit.pas',
  GameViewUnit in 'GameViewUnit.pas' {GameViewForm},
  StatusUnit in 'StatusUnit.pas' {StatusForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
