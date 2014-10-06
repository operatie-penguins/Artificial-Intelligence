object FieldForm: TFieldForm
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Field parameters'
  ClientHeight = 236
  ClientWidth = 226
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
    Left = 120
    Top = 200
    Width = 98
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
    Top = 200
    Width = 96
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
    Width = 209
    Height = 89
    Caption = 'Field size'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 28
      Height = 13
      Caption = 'Width'
    end
    object Label2: TLabel
      Left = 8
      Top = 52
      Width = 31
      Height = 13
      Caption = 'Height'
    end
    object WidthEdit: TSpinEdit
      Left = 112
      Top = 21
      Width = 81
      Height = 22
      MaxValue = 100
      MinValue = 10
      TabOrder = 0
      Value = 100
    end
    object HeightEdit: TSpinEdit
      Left = 112
      Top = 52
      Width = 81
      Height = 22
      MaxValue = 100
      MinValue = 10
      TabOrder = 1
      Value = 100
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 104
    Width = 209
    Height = 81
    Caption = 'Obstacles'
    TabOrder = 1
    object Label3: TLabel
      Left = 8
      Top = 24
      Width = 90
      Height = 39
      Caption = 'Percent of field squares, occupied by obstacles'
      WordWrap = True
    end
    object SpinEdit1: TSpinEdit
      Left = 112
      Top = 24
      Width = 81
      Height = 22
      MaxValue = 100
      MinValue = 0
      TabOrder = 0
      Value = 5
    end
  end
end
