object ControlForm: TControlForm
  Left = 209
  Top = 116
  Width = 433
  Height = 475
  BorderIcons = [biMinimize, biMaximize]
  Caption = 'Control'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 109
    Height = 20
    Caption = #1063#1080#1089#1083#1086' '#1079#1072#1081#1094#1077#1074':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 32
    Width = 110
    Height = 20
    Caption = #1063#1080#1089#1083#1086' '#1074#1086#1083#1082#1086#1074':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 56
    Width = 142
    Height = 20
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1090#1088#1072#1074#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 256
    Top = 56
    Width = 64
    Height = 20
    Caption = #1055#1088#1077#1076#1077#1083':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object cbLog: TCheckBox
    Left = 8
    Top = 408
    Width = 97
    Height = 17
    Caption = #1051#1086#1075
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = cbLogClick
  end
  object Button1: TButton
    Left = 160
    Top = 408
    Width = 75
    Height = 25
    Caption = #1057#1090#1072#1088#1090'!'
    TabOrder = 1
    OnClick = Button1Click
  end
  object tbHareCount: TEdit
    Left = 128
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'tbHareCount'
  end
  object tbWolfCount: TEdit
    Left = 128
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
  end
  object tbFoodCount: TEdit
    Left = 168
    Top = 56
    Width = 81
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object tbFoodLimit: TEdit
    Left = 328
    Top = 56
    Width = 81
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 80
    Width = 393
    Height = 57
    Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1078#1080#1079#1085#1080
    TabOrder = 6
    object Label5: TLabel
      Left = 16
      Top = 20
      Width = 60
      Height = 20
      Caption = #1047#1072#1081#1094#1077#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 176
      Top = 20
      Width = 60
      Height = 20
      Caption = #1042#1086#1083#1082#1086#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object tbHareLifeLength: TEdit
      Left = 80
      Top = 20
      Width = 81
      Height = 21
      TabOrder = 0
      Text = 'tbHareLifeLength'
    end
    object tbWolfLifeLength: TEdit
      Left = 240
      Top = 20
      Width = 81
      Height = 21
      TabOrder = 1
      Text = 'Edit1'
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 144
    Width = 393
    Height = 73
    Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1073#1077#1088#1077#1084#1077#1085#1085#1086#1089#1090#1080' '#1080' '#1095#1080#1089#1083#1086' '#1087#1086#1090#1086#1084#1082#1086#1074
    TabOrder = 7
    object Label7: TLabel
      Left = 16
      Top = 20
      Width = 60
      Height = 20
      Caption = #1047#1072#1081#1094#1077#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 176
      Top = 20
      Width = 60
      Height = 20
      Caption = #1042#1086#1083#1082#1086#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object tbHarePregnancyLength: TEdit
      Left = 80
      Top = 20
      Width = 81
      Height = 21
      TabOrder = 0
      Text = 'tbHarePregnancyLength'
    end
    object tbWolfPregnancyLength: TEdit
      Left = 240
      Top = 20
      Width = 81
      Height = 21
      TabOrder = 1
      Text = 'Edit1'
    end
    object tbHareSpawnFactor: TEdit
      Left = 80
      Top = 44
      Width = 81
      Height = 21
      TabOrder = 2
      Text = 'Edit1'
    end
    object tbWolfSpawnFactor: TEdit
      Left = 240
      Top = 44
      Width = 81
      Height = 21
      TabOrder = 3
      Text = 'Edit1'
    end
  end
  object GroupBox3: TGroupBox
    Left = 16
    Top = 224
    Width = 393
    Height = 105
    Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103' '#1090#1088#1072#1074#1099' (/1000)'
    TabOrder = 8
    object Label9: TLabel
      Left = 16
      Top = 28
      Width = 85
      Height = 20
      Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 16
      Top = 52
      Width = 107
      Height = 20
      Caption = #1056#1072#1079#1084#1085#1086#1078#1077#1085#1080#1077':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object tbFoodGenProbability: TEdit
      Left = 128
      Top = 28
      Width = 81
      Height = 21
      TabOrder = 0
      Text = 'tbFoodGenProbability'
    end
    object tbFoodRespawnProbability: TEdit
      Left = 128
      Top = 52
      Width = 81
      Height = 21
      TabOrder = 1
      Text = 'Edit1'
    end
  end
  object GroupBox4: TGroupBox
    Left = 16
    Top = 336
    Width = 393
    Height = 57
    Caption = #1057#1082#1086#1088#1086#1089#1090#1080
    TabOrder = 9
    object Label11: TLabel
      Left = 16
      Top = 20
      Width = 60
      Height = 20
      Caption = #1047#1072#1081#1094#1077#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 176
      Top = 20
      Width = 60
      Height = 20
      Caption = #1042#1086#1083#1082#1086#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object tbHareSpeed: TEdit
      Left = 80
      Top = 20
      Width = 81
      Height = 21
      TabOrder = 0
      Text = 'tbHareLifeLength'
    end
    object tbWolfSpeed: TEdit
      Left = 240
      Top = 20
      Width = 81
      Height = 21
      TabOrder = 1
      Text = 'Edit1'
    end
  end
end
