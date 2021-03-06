unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Unit2, Grids, StdCtrls, Buttons, ExtCtrls;

const
  MESSAGE_STR = 'MyMessage';
  No = 0;
  Yes = 1;

type
  TForm1 = class(TForm)
    DrawGrid1: TDrawGrid;
    Memo1: TMemo;
    procedure FormCreate(Sender: TObject);
    procedure WndProc(var Message: TMessage);override;
    procedure DrawGrid1DrawCell(Sender: TObject; ACol, ARow: Integer;
      Rect: TRect; State: TGridDrawState);
  private
    { Private declarations }
  public
    { Public declarations }
    msgSIMPR:UINT;
  end;

var
  Form1: TForm1;
  Lab: TLabyrinth;
  k: Integer;

implementation

{$R *.dfm}

procedure TForm1.DrawGrid1DrawCell(Sender: TObject; ACol, ARow: Integer;
  Rect: TRect; State: TGridDrawState);
var
  i: Integer;
  pic: TBitmap;
begin
  pic := TBitmap.Create;
  DrawGrid1.Canvas.Brush.Color := clGreen;
  DrawGrid1.Canvas.FillRect(DrawGrid1.CellRect(ACol,ARow));
  if Lab.LabMatrix[ARow,ACol] <= 1 then
  begin
    pic.LoadFromFile('pics/trava2.bmp');
    DrawGrid1.Canvas.Draw(DrawGrid1.CellRect(ACol,ARow).Left,
                DrawGrid1.CellRect(ACol,ARow).Top,pic);
  end;
  if ((Lab.Man.GetX = ACol) and (Lab.Man.GetY = ARow)) then
  begin
    pic.LoadFromFile('pics/ptica.bmp');
    pic.Transparent := True;
    DrawGrid1.Canvas.Draw(DrawGrid1.CellRect(ACol,ARow).Left,
                DrawGrid1.CellRect(ACol,ARow).Top,pic);
  end;
  for i := 0 to Length(Lab.Enemy) - 1 do
    if ((Lab.Enemy[i].GetX = ACol) and (Lab.Enemy[i].GetY = ARow)) then
    begin
     pic.LoadFromFile('pics/cat.bmp');
     pic.Transparent := True;
     DrawGrid1.Canvas.Draw(DrawGrid1.CellRect(ACol,ARow).Left,
                DrawGrid1.CellRect(ACol,ARow).Top,pic);
    end;
  for i := 0 to Length(Lab.Coins) - 1 do
    if ((Lab.Coins[i].GetX = ACol) and (Lab.Coins[i].GetY = ARow)) then
    begin
     pic.LoadFromFile('pics/korm.bmp');
     pic.Transparent := True;
     DrawGrid1.Canvas.Draw(DrawGrid1.CellRect(ACol,ARow).Left,
                DrawGrid1.CellRect(ACol,ARow).Top,pic);
    end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  MsgSIMPR:=RegisterWindowMessage(MESSAGE_STR);
  Lab := TLabyrinth.Create('lab.txt');
  DrawGrid1.RowCount := Length(Lab.LabMatrix);
  DrawGrid1.ColCount := Length(Lab.LabMatrix[0]);
  k := 0;
end;

procedure TForm1.WndProc(var Message: TMessage);
var
  res:boolean;
begin
  if message.Msg=msgSIMPR then
  begin
    Res:=false;
    if message.WParamHi=0 then
    begin
      case message.WParamLo of
        1: //������� 1
        begin
          Lab.TakeCoin;
          Memo1.Lines.Add('������� 1');
          case message.LParam of
            1:
            begin
              if ((Lab.Man.GetX = Lab.Enemy[k].GetX) and
                        (Lab.Man.GetY = Lab.Enemy[k].GetY)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 1 yes')
              else
                Memo1.Lines.Add('������� 1 no');
            end;
            2:
            begin
              if (Lab.IsCashOnWay(Lab.Man,Lab.Man.GetDirection)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 2 yes')
              else
                Memo1.Lines.Add('������� 2 no');
            end;
            3:
            begin
              if (Lab.IsCashOnWay(Lab.Man,Lab.Man.LeftSide)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 3 yes')
              else
                Memo1.Lines.Add('������� 3 no');
            end;
            4:
            begin
              if (Lab.IsCashOnWay(Lab.Man,Lab.Man.RightSide)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 4 yes')
              else
                Memo1.Lines.Add('������� 4 no');
            end;
            5:
            begin
              if (Lab.IsCashOnWay(Lab.Man,4)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 5 yes')
              else
                Memo1.Lines.Add('������� 5 no');
            end;
            6:
            begin
              if (Lab.IsCashOnWay(Lab.Man,5)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 6 yes')
              else
                Memo1.Lines.Add('������� 6 no');
            end;
            7:
            begin
              if (Lab.AreThereCoins) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 7 yes')
              else
                Memo1.Lines.Add('������� 7 no');
            end;
          end;
        end;
        2: //������� 2
        begin
          Memo1.Lines.Add('������� 2');
          case message.LParam of
            1:
            begin
              if ((Lab.Man.GetX = Lab.Enemy[k].GetX) and
                        (Lab.Man.GetY = Lab.Enemy[k].GetY)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 1 yes')
              else
                Memo1.Lines.Add('������� 1 no');
            end;
            2:
            begin
              if (Lab.IsManOnWay(Lab.Enemy[k],Lab.Enemy[k].LeftSide)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 2 yes')
              else
                Memo1.Lines.Add('������� 2 no');
            end;
            3:
            begin
              if (Lab.IsManOnWay(Lab.Enemy[k],Lab.Enemy[k].RightSide)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 3 yes')
              else
                Memo1.Lines.Add('������� 3 no');
            end;
            4:
            begin
              if (Lab.IsManOnWay(Lab.Enemy[k],Lab.Enemy[k].BackSide)) then
                Res := true;
              if Res then
                Memo1.Lines.Add('������� 4 yes')
              else
                Memo1.Lines.Add('������� 4 no');
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
            1:
            begin
              {Lab.TurnRandomWay(Lab.Man);
              if Lab.IsForwardWay(Lab.Man) then
                Lab.Man.Move
              else
                Lab.TurnRandomWay(Lab.Man);  }
            end;
            2:
            begin
              if Lab.IsForwardWay(Lab.Man) then
                Lab.Man.Move
              else
                Lab.TurnRandomWay(Lab.Man);
            end;
            3: 
            begin
              Lab.Man.Turn(Lab.Man.LeftSide);
              if Lab.IsForwardWay(Lab.Man) then
                Lab.Man.Move
              else
                Lab.TurnRandomWay(Lab.Man);
            end;
            4: 
            begin
              Lab.Man.Turn(Lab.Man.RightSide);
              if Lab.IsForwardWay(Lab.Man) then
                Lab.Man.Move
              else
                Lab.TurnRandomWay(Lab.Man);
            end;
            5:
            begin
              Lab.Man.Turn(Lab.Man.BackSide);
              if Lab.IsForwardWay(Lab.Man) then
                Lab.Man.Move
              else
                Lab.TurnRandomWay(Lab.Man);
            end;
            6:
            begin

            end;
          end;
        end;
        2:
        begin
          case message.LParam of
            1: ;
            2:
            begin
              if Lab.IsForwardWay(Lab.Enemy[k]) then
                Lab.Enemy[k].Move
              else
                Lab.TurnRandomWay(Lab.Enemy[k]);
            end;
            3:
            begin
              Lab.Enemy[k].Turn(Lab.Enemy[k].BackSide);
              if Lab.IsForwardWay(Lab.Enemy[k]) then
                Lab.Enemy[k].Move
              else
                Lab.TurnRandomWay(Lab.Enemy[k]);
            end;
            4:
            begin
              Randomize;
              if (random(2) = 0) then
              begin
                if Lab.IsLeftWay(Lab.Enemy[k]) then
                begin
                  Lab.Enemy[k].Turn(Lab.Enemy[k].LeftSide);
                  Lab.Enemy[k].Move
                end
                else
                  Lab.TurnRandomWay(Lab.Enemy[k])
              end
              else
              begin
                if Lab.IsRightWay(Lab.Enemy[k]) then
                begin
                  Lab.Enemy[k].Turn(Lab.Enemy[k].RightSide);
                  Lab.Enemy[k].Move
                end
                else
                  Lab.TurnRandomWay(Lab.Enemy[k])
              end;
            end;
          end;
          DrawGrid1.Repaint;
          Sleep(500);
        end;
      end;
      Res:=true;
    end;

    if res then
      message.Result:=1
    else
      message.Result:=0;

  end
  else
    inherited WndProc(Message);
end;

end.
