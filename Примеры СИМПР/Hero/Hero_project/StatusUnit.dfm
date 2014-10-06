object StatusForm: TStatusForm
  Left = 0
  Top = 580
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Status'
  ClientHeight = 176
  ClientWidth = 840
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 544
    Top = 8
    Width = 33
    Height = 13
    Caption = 'Hero : '
  end
  object Label2: TLabel
    Left = 544
    Top = 32
    Width = 24
    Height = 13
    Caption = 'Life :'
  end
  object Label3: TLabel
    Left = 544
    Top = 56
    Width = 38
    Height = 13
    Caption = 'Attack :'
  end
  object Label4: TLabel
    Left = 544
    Top = 80
    Width = 50
    Height = 13
    Caption = 'Defence : '
  end
  object Label5: TLabel
    Left = 544
    Top = 104
    Width = 51
    Height = 13
    Caption = 'Coords.x :'
  end
  object Label6: TLabel
    Left = 544
    Top = 128
    Width = 51
    Height = 13
    Caption = 'Coords.y :'
  end
  object Label7: TLabel
    Left = 704
    Top = 8
    Width = 86
    Height = 13
    Caption = 'Current monster :'
  end
  object Label8: TLabel
    Left = 704
    Top = 32
    Width = 24
    Height = 13
    Caption = 'Life :'
  end
  object Label9: TLabel
    Left = 704
    Top = 56
    Width = 38
    Height = 13
    Caption = 'Attack :'
  end
  object Label10: TLabel
    Left = 704
    Top = 80
    Width = 47
    Height = 13
    Caption = 'Defence :'
  end
  object Label11: TLabel
    Left = 704
    Top = 104
    Width = 51
    Height = 13
    Caption = 'Coords.x :'
  end
  object Label12: TLabel
    Left = 704
    Top = 128
    Width = 51
    Height = 13
    Caption = 'Coords.y :'
  end
  object HeroMemo: TMemo
    Left = 8
    Top = 8
    Width = 522
    Height = 161
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object HeroLifeText: TStaticText
    Left = 601
    Top = 33
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 1
  end
  object HeroAttackText: TStaticText
    Left = 601
    Top = 56
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 2
  end
  object HeroDefenceText: TStaticText
    Left = 601
    Top = 82
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 3
  end
  object HeroXText: TStaticText
    Left = 601
    Top = 105
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 4
  end
  object HeroYText: TStaticText
    Left = 601
    Top = 128
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 5
  end
  object MonsterLifeText: TStaticText
    Left = 773
    Top = 32
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 6
  end
  object MonsterAttackText: TStaticText
    Left = 773
    Top = 55
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 7
  end
  object MonsterDefenceText: TStaticText
    Left = 773
    Top = 78
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 8
  end
  object MonsterXText: TStaticText
    Left = 773
    Top = 101
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 9
  end
  object MonsterYText: TStaticText
    Left = 773
    Top = 128
    Width = 59
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 10
  end
end
