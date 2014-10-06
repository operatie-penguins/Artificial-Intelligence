object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 582
  ClientWidth = 784
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object DrawGrid1: TDrawGrid
    Left = 8
    Top = 8
    Width = 513
    Height = 566
    DefaultColWidth = 18
    DefaultRowHeight = 18
    FixedCols = 0
    FixedRows = 0
    GridLineWidth = 0
    TabOrder = 0
    OnDrawCell = DrawGrid1DrawCell
  end
  object Memo1: TMemo
    Left = 527
    Top = 8
    Width = 249
    Height = 566
    Lines.Strings = (
      '')
    TabOrder = 1
  end
end
