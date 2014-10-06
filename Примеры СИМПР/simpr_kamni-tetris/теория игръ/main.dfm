object mainForm: TmainForm
  Left = 367
  Top = 198
  Width = 947
  Height = 731
  Caption = #1051#1072#1073' '#8470'1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 40
    Top = 248
    Width = 3
    Height = 13
  end
  object Label2: TLabel
    Left = 64
    Top = 232
    Width = 3
    Height = 13
  end
  object Label1: TLabel
    Left = 80
    Top = 160
    Width = 3
    Height = 13
  end
  object mainLabel: TLabel
    Left = 380
    Top = 536
    Width = 3
    Height = 13
    Color = clMaroon
    ParentColor = False
  end
  object Label4: TLabel
    Left = 84
    Top = 102
    Width = 3
    Height = 13
    Color = clBtnFace
    ParentColor = False
  end
  object Label5: TLabel
    Left = 88
    Top = 168
    Width = 3
    Height = 13
  end
  object Label6: TLabel
    Left = 8
    Top = 64
    Width = 84
    Height = 13
    Caption = #1055#1086#1081#1084#1072#1083' '#1082#1072#1084#1085#1077#1081':'
  end
  object Label7: TLabel
    Left = 8
    Top = 120
    Width = 86
    Height = 13
    Caption = #1059#1087#1091#1089#1090#1080#1083' '#1082#1072#1084#1085#1077#1081':'
  end
  object ScrollBar1: TScrollBar
    Left = 176
    Top = 80
    Width = 17
    Height = 537
    Kind = sbVertical
    PageSize = 0
    TabOrder = 0
  end
  object ScrollBar2: TScrollBar
    Left = 192
    Top = 600
    Width = 313
    Height = 17
    PageSize = 0
    TabOrder = 1
  end
  object ScrollBar3: TScrollBar
    Left = 504
    Top = 80
    Width = 17
    Height = 537
    Kind = sbVertical
    PageSize = 0
    TabOrder = 2
  end
  object Edit1: TEdit
    Left = 176
    Top = 56
    Width = 345
    Height = 21
    TabOrder = 3
  end
  object MessageMemo: TMemo
    Left = 608
    Top = 56
    Width = 217
    Height = 561
    TabOrder = 4
  end
  object countEdit: TEdit
    Left = 112
    Top = 64
    Width = 41
    Height = 21
    TabOrder = 5
    Text = '0'
  end
  object minusEdit: TEdit
    Left = 112
    Top = 120
    Width = 41
    Height = 21
    TabOrder = 6
    Text = '0'
  end
  object cmdExit: TButton
    Left = 16
    Top = 584
    Width = 129
    Height = 33
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 7
    OnClick = cmdExitClick
  end
end
