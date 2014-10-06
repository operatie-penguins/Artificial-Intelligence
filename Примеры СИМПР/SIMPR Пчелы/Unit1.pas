unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Unit2, ExtCtrls, StdCtrls, ComCtrls;

const
  MESSAGE_STR = 'MyMessage';
  No = 0;
  Yes = 1;

type
  TForm1 = class(TForm)
    Image1: TImage;
    ProgressBar1: TProgressBar;
    Timer1: TTimer;
    Timer2: TTimer;
    Timer3: TTimer;
    Timer4: TTimer;
    ProgressBar2: TProgressBar;
    Timer5: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure WndProc(var Message: TMessage);override;
    procedure Timer1Timer(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
    procedure Timer4Timer(Sender: TObject);
    procedure Timer5Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    msgSIMPR:UINT;
  end;

var
  Form1: TForm1;
  Bees: array[1..3] of Bee;
  Flowers: array[1..5] of Flower;
  Indicator, Indicator2: Integer;

implementation

{$R *.dfm}

procedure InitParam;
var
  i: Integer;
begin
  Indicator := 0;
  Indicator2 := 0;

  Bees[1].image := TImage.Create(Form1);
  Bees[1].image.Parent := Form1;
  Bees[1].image.Left := 390;
  Bees[1].image.Top := 100;
  Bees[1].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\Pchela.bmp');
  Bees[1].image.Transparent := true;
  Bees[1].X := 390;
  Bees[1].Y := 100;
  Bees[1].Step := 0;
  Bees[1].Speed := 10;

  Bees[2].image := TImage.Create(Form1);
  Bees[2].image.Parent := Form1;
  Bees[2].image.Left := 460;
  Bees[2].image.Top := 130;
  Bees[2].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\Pchela.bmp');
  Bees[2].image.Transparent := true;
  Bees[2].X := 460;
  Bees[2].Y := 130;
  Bees[2].Step := 0;
  Bees[2].Speed := 15;

  Bees[3].image := TImage.Create(Form1);
  Bees[3].image.Parent := Form1;
  Bees[3].image.Left := 520;
  Bees[3].image.Top := 100;
  Bees[3].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\Pchela.bmp');
  Bees[3].image.Transparent := true;
  Bees[3].X := 520;
  Bees[3].Y := 100;
  Bees[3].Step := 0;
  Bees[3].Speed := 20;

  for i := 1 to 5 do
  begin
    Flowers[i].image := TImage.Create(Form1);
    Flowers[i].image.Parent := Form1;
    Flowers[i].image.Left := round(162*i) - 72;
    Flowers[i].image.Top := 462;
    Flowers[i].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\flower.bmp');
    Flowers[i].image.Transparent := true;
    Flowers[i].image.AutoSize := true;
    Flowers[i].X := round(162*i) - 72;
    Flowers[i].Y := 462;
  end;

end;

procedure MoveTo(i: Integer);
begin
  Bees[i].image.Left :=
        Bees[i].image.Left + round((Flowers[Bees[i].Flower].X - Bees[i].X)/Bees[i].Speed);
  Bees[i].image.Top :=
        Bees[i].image.Top + round((Flowers[Bees[i].Flower].Y - Bees[i].Y)/Bees[i].Speed);
  Inc(Bees[i].Step);
  if Bees[i].Step = Bees[i].Speed then
    Bees[i].State := 3;
end;

procedure MoveBack(i: Integer);
begin
  Bees[i].image.Left :=
        Bees[i].image.Left - round((Flowers[Bees[i].Flower].X - Bees[i].X)/Bees[i].Speed);
  Bees[i].image.Top :=
        Bees[i].image.Top - round((Flowers[Bees[i].Flower].Y - Bees[i].Y)/Bees[i].Speed);
  Dec(Bees[i].Step);
  if Bees[i].Step = 0 then
    Bees[i].State := 0;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  MsgSIMPR:=RegisterWindowMessage(MESSAGE_STR);
  InitParam;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  Bees[1].IsWithHoney := True;
  Flowers[Bees[1].Flower].IsWithPollen := False;
  Flowers[Bees[1].Flower].IsWithBee := False;
  Bees[1].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\PchelaWithHoney.bmp');
  Flowers[Bees[1].Flower].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\flower.bmp');
  Timer1.Enabled := False;
end;

procedure TForm1.Timer2Timer(Sender: TObject);
begin
  Bees[2].IsWithHoney := True;
  Flowers[Bees[2].Flower].IsWithPollen := False;
  Flowers[Bees[2].Flower].IsWithBee := False;
  Bees[2].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\PchelaWithHoney.bmp');
  Flowers[Bees[2].Flower].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\flower.bmp');
  Timer2.Enabled := False;
end;

procedure TForm1.Timer3Timer(Sender: TObject);
begin
  Bees[3].IsWithHoney := True;
  Flowers[Bees[3].Flower].IsWithPollen := False;
  Flowers[Bees[3].Flower].IsWithBee := False;
  Bees[3].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\PchelaWithHoney.bmp');
  Flowers[Bees[3].Flower].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\flower.bmp');
  Timer3.Enabled := False;
end;

procedure TForm1.Timer4Timer(Sender: TObject);
var
  i: Integer;
begin
  Randomize;
  i := random(5)+1;
  Flowers[i].IsWithPollen := True;
  Flowers[i].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\flowerWithPollen.bmp');
  Timer4.Interval := random(4000) + 2000;
end;

procedure TForm1.Timer5Timer(Sender: TObject);
begin
  ProgressBar2.StepIt;
  Inc(Indicator2);
end;

procedure TForm1.WndProc(var Message: TMessage);
var
  res:boolean;
  i: Integer;
  sum: Integer;
begin
  if message.Msg=msgSIMPR then
  begin
    Res:=false;
    if message.WParamHi=0 then
    begin
      case message.WParamLo of
        1: //������� 1
        begin
          case message.LParam of
            1:
            begin
              if (Bees[1].State = 0) then
                Res := True;
            end;
            2:
            begin
              if (Bees[1].State = 1) then
                Res := True;
            end;
            3:
            begin
              if (Bees[1].State = 3) then
                Res := True;
            end;
            4:
            begin
              if (Bees[1].State = 2) then
                Res := True;
            end;
            5:
            begin
              sum := 0;
              for i := 1 to 3 do
                if (Bees[i].State = 0) then
                  Inc(sum);
              if (sum > 1) then
                Res := True;
            end;
            6:
            begin
              if ((Flowers[1].IsWithPollen) or (Flowers[2].IsWithPollen)) then
                Res := True;
            end;
            7:
            begin
              if (Bees[1].Flower > 0) then
                if (Flowers[Bees[1].Flower].IsWithBee) then
                  Res := True;
            end;
            8:
            begin
              if (Bees[1].Step = Bees[1].Speed) then
                Res := True;
            end;
            9:
            begin
              if (Bees[1].IsWithHoney) then
                Res := True;
            end;
          end;
        end;
        2: //������� 2
        begin
          case message.LParam of
            1:
            begin
              if (Bees[2].State = 0) then
                Res := True;
            end;
            2:
            begin
              if (Bees[2].State = 1) then
                Res := True;
            end;
            3:
            begin
              if (Bees[2].State = 3) then
                Res := True;
            end;
            4:
            begin
              if (Bees[2].State = 2) then
                Res := True;
            end;
            5:
            begin
              sum := 0;
              for i := 1 to 3 do
                if (Bees[i].State = 0) then
                  Inc(sum);
              if (sum > 1) then
                Res := True;
            end;
            6:
            begin
              if ((Flowers[2].IsWithPollen) or (Flowers[3].IsWithPollen)
                        or (Flowers[4].IsWithPollen)) then
                Res := True;
            end;
            7:
            begin
              if (Bees[2].Flower > 0) then
                if (Flowers[Bees[2].Flower].IsWithBee) then
                  Res := True;
            end;
            8:
            begin
              if (Bees[2].Step = Bees[2].Speed) then
                Res := True;
            end;
            9:
            begin
              if (Bees[2].IsWithHoney) then
                Res := True;
            end;
          end;
        end;
        3:
        begin
          case message.LParam of
            1:
            begin
              if (Bees[3].State = 0) then
                Res := True;
            end;
            2:
            begin
              if (Bees[3].State = 1) then
                Res := True;
            end;
            3:
            begin
              if (Bees[3].State = 3) then
                Res := True;
            end;
            4:
            begin
              if (Bees[3].State = 2) then
                Res := True;
            end;
            5:
            begin
              sum := 0;
              for i := 1 to 3 do
                if (Bees[i].State = 0) then
                  Inc(sum);
              if (sum > 1) then
                Res := True;
            end;
            6:
            begin
              if ((Flowers[4].IsWithPollen) or (Flowers[5].IsWithPollen)) then
                Res := True;
            end;
            7:
            begin
              if (Bees[3].Flower > 0) then
                if (Flowers[Bees[3].Flower].IsWithBee) then
                  Res := True;
            end;
            8:
            begin
              if (Bees[3].Step = Bees[3].Speed) then
                Res := True;
            end;
            9:
            begin
              if (Bees[3].IsWithHoney) then
                Res := True;
            end;
          end;
        end;
        4: //������� 3
        begin
          case message.LParam of
            1:
            begin
              if (Indicator2 >= 10) then
                Res := True;
            end;
            2:
            begin
              if (Indicator >= 10) then
                Res := True;
            end;
           end;
        end;
      end;
    end;

    if message.WParamHi = 1 then
    begin
      case message.WParamLo of
        1:
        begin
          //MessageDlg('�������� � ������� 1',mtInformation,[mbOk],0);
          case message.LParam of
            1: ;
            2:
            begin
              if (Bees[1].State <> 1) then
              begin
                Bees[1].State := 1;
                if Flowers[1].IsWithPollen then
                  Bees[1].Flower := 1
                else
                  Bees[1].Flower := 2;
              end;
              MoveTo(1);
            end;
            3:
            begin
              Bees[1].State := 3;
              Flowers[Bees[1].Flower].IsWithBee := True;
              Flowers[Bees[1].Flower].Bee := 1;
              Timer1.Enabled := True;
            end;
            4:
            begin
              if (Bees[1].State <> 2) then
              begin
                Bees[1].State := 2;
                if Bees[1].Flower > 0 then
                //Bees[1].Flower := 0;
              end;
              MoveBack(1);
            end;
            5:
            begin
              if (Bees[1].IsWithHoney) then
              begin
                Inc(Indicator);
                ProgressBar1.StepIt;
                Bees[1].IsWithHoney := False;
                Bees[1].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\Pchela.bmp');
              end;
              Bees[1].State := 0;
            end;
          end;
        end;
        2:
        begin
          case message.LParam of
            1: ;
            2:
            begin
              if (Bees[2].State <> 1) then
              begin
                Bees[2].State := 1;
                if Flowers[2].IsWithPollen then
                  Bees[2].Flower := 2
                else if Flowers[3].IsWithPollen then
                  Bees[2].Flower := 3
                else
                  Bees[2].Flower := 4;
              end;
              MoveTo(2);
            end;
            3:
            begin
              Bees[2].State := 3;
              Flowers[Bees[2].Flower].IsWithBee := True;
              Flowers[Bees[2].Flower].Bee := 1;
              Timer2.Enabled := True;
            end;
            4:
            begin
              if (Bees[2].State <> 2) then
              begin
                Bees[2].State := 2;
                //Bees[2].Flower := 0;
              end;
              MoveBack(2);
            end;
            5:
            begin
              if (Bees[2].IsWithHoney) then
              begin
                Inc(Indicator);
                Bees[2].IsWithHoney := False;
                ProgressBar1.StepIt;
                Bees[2].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\Pchela.bmp');
              end;
              Bees[2].State := 0;
            end;
          end;
        end;
        3:
        begin
          case message.LParam of
            1: ;
            2:
            begin
              if (Bees[3].State <> 1) then
              begin
                Bees[3].State := 1;
                if Flowers[4].IsWithPollen then
                  Bees[3].Flower := 4
                else
                  Bees[3].Flower := 5;
              end;
              MoveTo(3);
            end;
            3:
            begin
              Bees[3].State := 3;
              Flowers[Bees[3].Flower].IsWithBee := True;
              Flowers[Bees[3].Flower].Bee := 1;
              Timer3.Enabled := True;
            end;
            4:
            begin
              if Bees[3].State <> 2 then
              begin
                Bees[3].State := 2;
                //Bees[3].Flower := 0;
              end;
              MoveBack(3);
            end;
            5:
            begin
              if (Bees[3].IsWithHoney) then
              begin
                Inc(Indicator);
                ProgressBar1.StepIt;
                Bees[3].image.Picture.LoadFromFile(GetCurrentDir + '\' + 'pictures\Pchela.bmp');
                Bees[3].IsWithHoney := False;
              end;
              Bees[3].State := 0;
            end;
          end;
        end;
        4:
        begin
          case message.LParam of
            1: ;
          end;
        end;
      end;
      Res:=true;
    end;

    Sleep(10);

    if res then
      message.Result:=1
    else
      message.Result:=0;

  end
  else
    inherited WndProc(Message);
end;

end.
