object MainForm: TMainForm
  Left = 354
  Top = 440
  Width = 389
  Height = 328
  Caption = 'Hero'
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    Left = 8
    Top = 8
    object GameItem: TMenuItem
      Caption = 'Game'
      object StartItem: TMenuItem
        Caption = 'Start'
        ShortCut = 113
        OnClick = StartItemClick
      end
      object PauseItem: TMenuItem
        Caption = 'Pause'
        ShortCut = 16464
        OnClick = PauseItemClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object ExitItem: TMenuItem
        Caption = 'Exit'
        ShortCut = 123
        OnClick = ExitItemClick
      end
    end
    object ParametersItem: TMenuItem
      Caption = 'Parameters'
      object FieldItem: TMenuItem
        Caption = 'Field...'
        ShortCut = 16454
        OnClick = FieldItemClick
      end
      object HeroItem: TMenuItem
        Caption = 'Hero...'
        ShortCut = 16456
        OnClick = HeroItemClick
      end
      object BonusesItem: TMenuItem
        Caption = 'Bonuses...'
        ShortCut = 16450
        OnClick = BonusesItemClick
      end
      object MonstersItem: TMenuItem
        Caption = 'Monsters...'
        ShortCut = 16461
        OnClick = MonstersItemClick
      end
    end
    object HelpItem: TMenuItem
      Caption = 'Help'
      object AboutItem: TMenuItem
        Caption = 'About...'
        ShortCut = 112
        OnClick = AboutItemClick
      end
    end
  end
end
