object frmMain: TfrmMain
  Left = 273
  Top = 154
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1051#1072#1073#1086#1088#1072#1090#1086#1088#1085#1072#1103' '#1088#1072#1073#1086#1090#1072
  ClientHeight = 400
  ClientWidth = 400
  Color = clWhite
  DockSite = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PrintScale = poPrintToFit
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pnlDock: TPanel
    Left = 185
    Top = 155
    Width = 31
    Height = 90
    Caption = #1044#1054#1050
    Color = clMedGray
    TabOrder = 0
  end
  object grbxCtrl: TGroupBox
    Left = 5
    Top = 5
    Width = 265
    Height = 50
    Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
    Color = clWhite
    ParentColor = False
    TabOrder = 1
    object btnInfo: TButton
      Left = 10
      Top = 15
      Width = 75
      Height = 25
      Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103
      TabOrder = 0
      OnClick = btnInfoClick
    end
    object btnScnd: TButton
      Left = 95
      Top = 15
      Width = 75
      Height = 25
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      TabOrder = 1
      OnClick = btnScndClick
    end
    object btnClose: TButton
      Left = 180
      Top = 15
      Width = 75
      Height = 25
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 2
      OnClick = btnCloseClick
    end
  end
  object tmr_Main: TTimer
    Enabled = False
    Interval = 2000
    Left = 768
  end
end
