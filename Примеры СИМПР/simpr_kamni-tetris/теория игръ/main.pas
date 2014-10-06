unit main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

const
  MESSAGE_STR='labMessage';
  No=0;
  Yes=1;

type
  PElement = ^TElement;
  TElement = Record
           style : boolean;
           element: TLabel;
           Next: PElement;
         end;

  TmainForm = class(TForm)
    ScrollBar1: TScrollBar;
    ScrollBar2: TScrollBar;
    ScrollBar3: TScrollBar;
    Edit1: TEdit;
    mainLabel: TLabel;
    Label4: TLabel;

    MessageMemo: TMemo;
    countEdit: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label5: TLabel;
    minusEdit: TEdit;
    Label6: TLabel;
    Label7: TLabel;
    cmdExit: TButton;
    procedure FormCreate(Sender: TObject);
    procedure WndProc(var Message: TMessage);override;
    procedure Next();
    procedure Zadergka();
    procedure cmdExitClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    msgSIMPR:UINT;
  end;

var
  mainForm: TmainForm;
 // star : PElement;

  state : array [1..5,1..2] of integer;
  style : array [1..5,1..2] of boolean;

implementation

{$R *.dfm}



procedure TmainForm.Next();
var
  color : byte;

begin
      Randomize;
      Label1.Left := Label2.Left;
      Label1.Top := Label2.Top;
      Label1.Color := Label2.Color;

      Label2.Left := 200 + 30 * random(9);
      Label2.Top := 86;
      Label2.Color := clGreen;

      color := random(2);
      if (color = 0) then
        Label2.color := clBlack;
end;

procedure TmainForm.WndProc(var Message: TMessage);
var res:boolean;
    count, minus : integer;
    
begin
  Randomize;
  if message.Msg=msgSIMPR then
   begin
  //     messageMemo.Lines.Add(IntToStr(message.WParamHi));
    //�������� ���������!!!!!!!!!!
    Res:=false;

    if message.WParamHi=0 then
    begin
     //�������!!!!!!!!!!
     case message.WParamLo of
      //�������1
      1 : begin
      MessageMemo.Lines.Add('����. 1');
      case message.LParam of
            1: begin // ������� 1
                if(Label1.Left < mainLabel.Left) then Res:=true;
                MessageMemo.Lines.Add('���. 1 : ' + BoolToStr(Res));
               end;
            2: begin // ������� 2
                if (Label1.Left > mainLabel.Left) then Res:=true;
                MessageMemo.Lines.Add('���. 2 : ' + BoolToStr(Res));
               end;
            3: begin // ������� 3
                if (Label1.Left = mainLabel.Left) then Res:=true;
                MessageMemo.Lines.Add('���. 3 : ' + BoolToStr(Res));
               end;
            4: begin // ������� 4
                if Label1.Color = clGreen then
                Res:=true;
                MessageMemo.Lines.Add('���. 4 : ' + BoolToStr(Res));
               end;
            5: begin // ������� 5
                if Label1.Color = clBlack then
                Res:=true;
                MessageMemo.Lines.Add('���. 5 : ' + BoolToStr(Res));
               end;
            6: begin // ������� 6
                if (Label1.Top = mainLabel.Top) and (Label1.Left <> mainLabel.Left)
                  then Res:=true;
                MessageMemo.Lines.Add('���. 6 : ' + BoolToStr(Res));
               end;
            7: begin // ������� 7
                if abs(Label1.Top - mainLabel.Top) <= abs(Label1.Left - mainLabel.Left)
                  then Res:=true;
                  MessageMemo.Lines.Add('���. 7 : ' + BoolToStr(Res));
               end;
      end; {case}
      end;

      //�������2
      2 : begin
      MessageMemo.Lines.Add('����. 2');
      case message.LParam of
            1: begin // ������� 1
               if Label1.Top < mainLabel.Top then Res:=true;
               MessageMemo.Lines.Add('���. 1 : ' + BoolToStr(Res));
               end;
            2: begin // ������� 2
                if Label1.Top = mainLabel.Top then Res:=true;
               MessageMemo.Lines.Add('���. 2 : ' + BoolToStr(Res));
               end;
       end; {case}
       end; {2}

       //�������3
      3 : begin
      MessageMemo.Lines.Add('����. 3');
      case message.LParam of
            1: begin // ������� 1
               if Label2.Left < mainLabel.Left then Res:=true;
               MessageMemo.Lines.Add('���. 1 : ' + BoolToStr(Res));
               end;
            2: begin // ������� 2
                if Label2.Left > mainLabel.Left then Res:=true;
               MessageMemo.Lines.Add('���. 2 : ' + BoolToStr(Res));
               end;
            3: begin // ������� 3
               if Label2.Left = mainLabel.Left then Res:=true;
               MessageMemo.Lines.Add('���. 3 : ' + BoolToStr(Res));
               end;
            4: begin // ������� 4
                if Label2.Color = clGreen then Res:=true;
               MessageMemo.Lines.Add('���. 4 : ' + BoolToStr(Res));
               end;
            5: begin // ������� 5
                if Label2.Color = clBlack then Res:=true;
               MessageMemo.Lines.Add('���. 5 : ' + BoolToStr(Res));
               end;
            6: begin // ������� 6
                if mainLabel.Left = 200 then Res:=true;
               MessageMemo.Lines.Add('���. 6 : ' + BoolToStr(Res));
               end;
            7: begin // ������� 7
                if mainLabel.Left = 470 then Res:=true;
               MessageMemo.Lines.Add('���. 7 : ' + BoolToStr(Res));
               end;
       end; {case}
       end; {3}

       //�������4
      4 : begin
      MessageMemo.Lines.Add('����. 4');
      case message.LParam of
            1: begin // ������� 1
               if mainLabel.Left <= 290 then Res:=true;
               MessageMemo.Lines.Add('���. 1 : ' + BoolToStr(Res));
               end;
            2: begin // ������� 2
                if mainLabel.Left > 290 then Res:=true;
               MessageMemo.Lines.Add('���. 2 : ' + BoolToStr(Res));
               end;
       end; {case}
       end; {4}

       //�������5
      5 : begin
      MessageMemo.Lines.Add('����.5');
      case message.LParam of
            1: begin // ������� 1
               if Label1.Top < mainLabel.Top then Res:=true;
               MessageMemo.Lines.Add('���. 1 : ' + BoolToStr(Res));
               end;
            2: begin // ������� 2
                if (Label1.Top = mainLabel.Top) and (Label1.Left <> mainLabel.Left)
                 then Res:=true;
               MessageMemo.Lines.Add('���. 2 : ' + BoolToStr(Res));
               end;
            3: begin // ������� 3
                if (Label1.Top = mainLabel.Top) and (Label1.Left = mainLabel.Left)
                 then Res:=true;
               MessageMemo.Lines.Add('���. 3 : ' + BoolToStr(Res));
               end;
            4: begin // ������� 4
               if mainLabel.Left <= 290 then Res:=true;
               MessageMemo.Lines.Add('���. 4 : ' + BoolToStr(Res));
               end;
            5: begin // ������� 5
                if mainLabel.Left > 290 then Res:=true;
               MessageMemo.Lines.Add('���. 5 : ' + BoolToStr(Res));
               end;
       end; {case}
       end; {5}

      end; {case}
    end;


    if message.WParamHi=1 then
    begin
    //��������!!!!!!!!!!
     case message.WParamLo of
      //������� 1
      1 : begin
      case message.LParam of
      1: begin // �������� 1
          mainLabel.Left := mainLabel.Left - 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      2: begin // �������� 2
          mainLabel.Left := mainLabel.Left + 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      3: begin // �������� 3
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      4: begin // �������� 4
          minus := StrToInt(minusEdit.Text);
          minus := minus + 1;
          minusEdit.Text := IntToStr(minus);
         end;
      5: begin // �������� 5
          Next();
         end;
      end; {case}
      end; {1}
      //������� 2
      2 : begin
      case message.LParam of
            1: begin // �������� 1
                  Label1.Top := Label1.Top + 30;
                  Label2.Top := Label2.Top + 30;
               end;
            2: begin // �������� 2
                  count := StrToInt(countEdit.Text);
                  count := count + 1;
                  countEdit.Text := IntToStr(count);
               end;
            3: begin // �������� 3
             //     Label1.Left := 200 + 30 * random(9);
             //     Label1.Top := 86;
                    Next();
               end;

      end; {case}
      end; {2}

      //������� 3
      3 : begin
      case message.LParam of
      1: begin // �������� 1
          mainLabel.Left := mainLabel.Left - 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      2: begin // �������� 2
          mainLabel.Left := mainLabel.Left + 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      3: begin // �������� 3
        //  mainLabel.Left := mainLabel.Left + 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      end; {case}
      end; {3}

      //������� 4
      4 : begin
      case message.LParam of
      1: begin // �������� 1
          mainLabel.Left := mainLabel.Left + 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      2: begin // �������� 2
          mainLabel.Left := mainLabel.Left - 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      end; {case}
      end; {4}

      //������� 5
      5 : begin
      case message.LParam of
      1: begin // �������� 1
          next();
         end;
      2: begin // �������� 2
          mainLabel.Left := mainLabel.Left + 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
         end;
      3: begin // �������� 3
          mainLabel.Left := mainLabel.Left - 30;
          Label1.Top := Label1.Top + 30;
          Label2.Top := Label2.Top + 30;
          end;
      end; {5}
       end; {case}
    end;{case}
     Res:=true;
    end;

  zadergka();

 //������ ���������!!!!!!!!!
   if res then   message.Result:=1
   else   message.Result:=0;
   end
    else inherited WndProc(Message); // �� ������ ���������
end;

//--------------------------------------------------------------


procedure TmainForm.FormCreate(Sender: TObject);
begin
  MsgSIMPR:=RegisterWindowMessage(MESSAGE_STR);

  mainLabel.Height := 60;
  mainLabel.Width := 30;

  Label1.Height := 30;
  Label1.Width := 30;
  Label1.Top := 86;
  Label1.Left := 200 + 30 * random(9);
  Label1.Color := clGreen;

  Label2.Top := -4;
  Label2.Left := 200 + 30 * random(9);
  Label2.Height := 30;
  Label2.Width := 30;
  Label2.Color := clBlack;

  Label3.Top := 86;
  Label3.Left := 200 + 30 * random(9);
  Label3.Height := 30;
  Label3.Width := 30;
 // Label3.Color := clGreen;

  Label4.Top := 86;
  Label4.Left := 200 + 30 * random(9);
  Label4.Height := 30;
  Label4.Width := 30;
//  Label4.Color := clGreen;

  Label5.Top := 86;
  Label5.Left := 200 + 30 * random(9);
  Label5.Height := 30;
  Label5.Width := 30;
 // Label5.Color := clGreen;

end;

procedure TmainForm.Zadergka();
var
  i : integer;

begin
    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;

    for i := 1 to 999999 do
    begin
    end;
end;


procedure TmainForm.cmdExitClick(Sender: TObject);
begin
  close;
end;

end.
