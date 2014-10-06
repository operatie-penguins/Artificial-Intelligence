object mainForm: TmainForm
  Left = 252
  Top = 303
  Width = 902
  Height = 665
  Caption = 'raid'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mainMenu
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object mazeBevel: TBevel
    Left = 0
    Top = 0
    Width = 617
    Height = 617
    Style = bsRaised
  end
  inline mazeFrame: TmazeFrame
    Left = 8
    Top = 8
    Width = 600
    Height = 600
    Color = clMedGray
    ParentColor = False
    TabOrder = 0
    inherited mazePanel: TPanel
      Width = 97
      inherited Image: TImage
        Width = 96
        Transparent = True
      end
    end
  end
  object memoLog: TMemo
    Left = 624
    Top = 0
    Width = 265
    Height = 617
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object mainMenu: TMainMenu
    Left = 560
    Top = 568
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N12: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1089#1080#1090#1091#1072#1094#1080#1102
        OnClick = N12Click
      end
      object N2: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N2Click
      end
    end
    object N3: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      object N4: TMenuItem
        Caption = #1056#1072#1079#1084#1077#1088#1099' '#1086#1073#1083#1072#1089#1090#1080
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1086#1073#1098#1077#1082#1090#1086#1074
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = '"'#1055#1083#1086#1090#1085#1086#1089#1090#1100'" '#1083#1072#1073#1080#1088#1080#1085#1090#1072
        OnClick = N6Click
      end
    end
    object N7: TMenuItem
      Caption = #1047#1072#1087#1091#1089#1082
      object N8: TMenuItem
        AutoHotkeys = maManual
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1083#1072#1073#1080#1088#1080#1085#1090
        OnClick = N8Click
      end
      object N9: TMenuItem
        Caption = #1056#1072#1089#1087#1088#1077#1076#1077#1083#1080#1090#1100'  '#1086#1073#1098#1077#1082#1090#1099
        OnClick = N9Click
      end
      object N11: TMenuItem
        AutoCheck = True
        Caption = #1040#1074#1090#1086#1089#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1087#1088#1080' '#1074#1099#1093#1086#1076#1077
        OnClick = N11Click
      end
      object N13: TMenuItem
        AutoCheck = True
        Caption = #1040#1074#1090#1086#1079#1072#1075#1088#1091#1079#1082#1072' '#1087#1088#1080' '#1074#1093#1086#1076#1077
        OnClick = N13Click
      end
      object N10: TMenuItem
        AutoCheck = True
        Caption = #1047#1072#1076#1077#1088#1078#1082#1072
      end
    end
  end
end
