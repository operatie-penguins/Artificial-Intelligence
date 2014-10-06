object Form1: TForm1
  Left = 280
  Top = 224
  Width = 715
  Height = 709
  Caption = 'RABBITS'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 707
    Height = 525
    Align = alClient
    TabOrder = 0
    object PaintBox1: TPaintBox
      Left = 1
      Top = 1
      Width = 705
      Height = 523
      Align = alClient
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 525
    Width = 707
    Height = 150
    Align = alBottom
    Caption = 'Panel2'
    TabOrder = 1
    object LogMemo: TMemo
      Left = 1
      Top = 1
      Width = 705
      Height = 148
      Align = alClient
      TabOrder = 0
    end
  end
end
