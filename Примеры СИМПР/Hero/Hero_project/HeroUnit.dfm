object HeroForm: THeroForm
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Hero parameters'
  ClientHeight = 297
  ClientWidth = 204
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object CancelButton: TSpeedButton
    Left = 105
    Top = 263
    Width = 91
    Height = 25
    Caption = 'Cancel'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = CancelButtonClick
  end
  object OKButton: TSpeedButton
    Left = 8
    Top = 263
    Width = 91
    Height = 25
    Caption = 'OK'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = OKButtonClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 121
    Caption = 'Start parameters'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 17
      Height = 13
      Caption = 'Life'
    end
    object Label2: TLabel
      Left = 8
      Top = 53
      Width = 31
      Height = 13
      Caption = 'Attack'
    end
    object Label3: TLabel
      Left = 8
      Top = 83
      Width = 40
      Height = 13
      Caption = 'Defence'
    end
    object LifeEdit: TSpinEdit
      Left = 96
      Top = 24
      Width = 81
      Height = 22
      MaxValue = 1000
      MinValue = 1
      TabOrder = 0
      Value = 10
    end
    object AttackEdit: TSpinEdit
      Left = 96
      Top = 53
      Width = 81
      Height = 22
      MaxValue = 1000
      MinValue = 1
      TabOrder = 1
      Value = 10
    end
    object DefenceEdit: TSpinEdit
      Left = 96
      Top = 83
      Width = 81
      Height = 22
      MaxValue = 1000
      MinValue = 1
      TabOrder = 2
      Value = 10
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 136
    Width = 185
    Height = 121
    Caption = 'Aimes'
    TabOrder = 1
    object BonusCheck: TCheckBox
      Left = 8
      Top = 24
      Width = 161
      Height = 17
      Caption = 'Collect all bonuses'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object MonsterCheck: TCheckBox
      Left = 8
      Top = 57
      Width = 161
      Height = 17
      Caption = 'Defeat all monsters'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object ExitCheck: TCheckBox
      Left = 8
      Top = 88
      Width = 137
      Height = 17
      Caption = 'Reach exit'
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
  end
end
