object MonstersForm: TMonstersForm
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Monster parameters'
  ClientHeight = 376
  ClientWidth = 329
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object AddButton: TSpeedButton
    Left = 184
    Top = 176
    Width = 137
    Height = 25
    Caption = 'Add new monster'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = AddButtonClick
  end
  object EditButton: TSpeedButton
    Left = 184
    Top = 218
    Width = 137
    Height = 25
    Caption = 'Edit this monster'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = EditButtonClick
  end
  object DeleteButton: TSpeedButton
    Left = 184
    Top = 260
    Width = 137
    Height = 25
    Caption = 'Delete this monster'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = DeleteButtonClick
  end
  object ApplyButton: TSpeedButton
    Left = 184
    Top = 302
    Width = 137
    Height = 25
    Caption = 'Apply changes'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = ApplyButtonClick
  end
  object CancelButton: TSpeedButton
    Left = 230
    Top = 344
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
    Left = 133
    Top = 344
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
  object MonsterView: TListView
    Left = 8
    Top = 8
    Width = 313
    Height = 160
    Checkboxes = True
    Color = clSkyBlue
    Columns = <
      item
        Caption = 'Monster type'
        Width = 255
      end
      item
        Caption = 'Number'
        Width = 51
      end>
    ColumnClick = False
    HideSelection = False
    TabOrder = 0
    ViewStyle = vsReport
  end
  object GroupBox1: TGroupBox
    Left = 9
    Top = 174
    Width = 169
    Height = 153
    Caption = 'Current monster parameters'
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 17
      Height = 13
      Caption = 'Life'
    end
    object Label2: TLabel
      Left = 16
      Top = 56
      Width = 31
      Height = 13
      Caption = 'Attack'
    end
    object Label3: TLabel
      Left = 16
      Top = 84
      Width = 40
      Height = 13
      Caption = 'Defence'
    end
    object Label4: TLabel
      Left = 16
      Top = 112
      Width = 37
      Height = 13
      Caption = 'Number'
    end
    object NumberEdit: TSpinEdit
      Left = 74
      Top = 112
      Width = 81
      Height = 22
      EditorEnabled = False
      MaxValue = 100
      MinValue = 0
      TabOrder = 0
      Value = 0
    end
    object LifeEdit: TSpinEdit
      Left = 74
      Top = 24
      Width = 81
      Height = 22
      EditorEnabled = False
      MaxValue = 1000
      MinValue = 1
      ReadOnly = True
      TabOrder = 1
      Value = 1
    end
    object AttackEdit: TSpinEdit
      Left = 74
      Top = 52
      Width = 81
      Height = 22
      EditorEnabled = False
      MaxValue = 1000
      MinValue = 1
      ReadOnly = True
      TabOrder = 2
      Value = 1
    end
    object DefenceEdit: TSpinEdit
      Left = 74
      Top = 80
      Width = 81
      Height = 22
      EditorEnabled = False
      MaxValue = 1000
      MinValue = 1
      ReadOnly = True
      TabOrder = 3
      Value = 1
    end
  end
end
