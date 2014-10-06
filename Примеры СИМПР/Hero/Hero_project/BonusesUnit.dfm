object BonusesForm: TBonusesForm
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Bonus parameters'
  ClientHeight = 335
  ClientWidth = 245
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
  object Label5: TLabel
    Left = 23
    Top = 272
    Width = 54
    Height = 13
    Caption = 'All bonuses'
  end
  object CancelButton: TSpeedButton
    Left = 146
    Top = 304
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
    Left = 49
    Top = 304
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
  object Bevel10: TBevel
    Left = 8
    Top = 264
    Width = 231
    Height = 2
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 241
    Height = 249
    ActivePage = LifeSheet
    Style = tsFlatButtons
    TabOrder = 0
    object LifeSheet: TTabSheet
      Caption = 'Life'
      object ApplyLifeButton: TSpeedButton
        Left = 134
        Top = 186
        Width = 91
        Height = 25
        Caption = 'Apply'
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = ApplyLifeButtonClick
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 3
        Width = 225
        Height = 177
        Caption = 'Life bonuses'
        TabOrder = 0
        object Label1: TLabel
          Left = 8
          Top = 24
          Width = 31
          Height = 13
          Caption = '+1 life'
        end
        object Label2: TLabel
          Left = 8
          Top = 56
          Width = 31
          Height = 13
          Caption = '+5 life'
        end
        object Label3: TLabel
          Left = 8
          Top = 87
          Width = 37
          Height = 13
          Caption = '+10 life'
        end
        object Label4: TLabel
          Left = 11
          Top = 136
          Width = 28
          Height = 13
          Caption = 'All life'
        end
        object Bevel1: TBevel
          Left = 16
          Top = 120
          Width = 193
          Height = 2
        end
        object Bevel2: TBevel
          Left = 144
          Top = 16
          Width = 2
          Height = 98
        end
        object Bevel3: TBevel
          Left = 144
          Top = 128
          Width = 2
          Height = 41
        end
        object OneLifeEdit: TSpinEdit
          Left = 72
          Top = 24
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 0
          Value = 0
        end
        object FiveLifeEdit: TSpinEdit
          Left = 72
          Top = 56
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 1
          Value = 0
        end
        object TenLifeEdit: TSpinEdit
          Left = 72
          Top = 87
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 2
          Value = 0
        end
        object AllLifeEdit: TSpinEdit
          Left = 72
          Top = 136
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 3000
          MinValue = 0
          ReadOnly = True
          TabOrder = 3
          Value = 0
        end
        object PerOneLifeEdit: TSpinEdit
          Left = 152
          Top = 24
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 4
          Value = 0
        end
        object PerFiveLifeEdit: TSpinEdit
          Left = 152
          Top = 56
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 5
          Value = 0
        end
        object PerTenLifeEdit: TSpinEdit
          Left = 152
          Top = 88
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 6
          Value = 0
        end
        object PerAllLifeEdit: TSpinEdit
          Left = 152
          Top = 136
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 100
          ReadOnly = True
          TabOrder = 7
          Value = 100
        end
      end
    end
    object AttackSheet: TTabSheet
      Caption = 'Attack'
      ImageIndex = 1
      object ApplyAttackButton: TSpeedButton
        Left = 134
        Top = 186
        Width = 91
        Height = 25
        Caption = 'Apply'
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = ApplyAttackButtonClick
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 3
        Width = 225
        Height = 177
        Caption = 'Attack bonuses'
        TabOrder = 0
        object Label10: TLabel
          Left = 8
          Top = 24
          Width = 47
          Height = 13
          Caption = '+1 attack'
        end
        object Label11: TLabel
          Left = 8
          Top = 56
          Width = 47
          Height = 13
          Caption = '+5 attack'
        end
        object Label12: TLabel
          Left = 8
          Top = 87
          Width = 53
          Height = 13
          Caption = '+10 attack'
        end
        object Label13: TLabel
          Left = 11
          Top = 136
          Width = 44
          Height = 13
          Caption = 'All attack'
        end
        object Bevel7: TBevel
          Left = 16
          Top = 120
          Width = 193
          Height = 2
        end
        object Bevel8: TBevel
          Left = 144
          Top = 16
          Width = 2
          Height = 98
        end
        object Bevel9: TBevel
          Left = 144
          Top = 128
          Width = 2
          Height = 41
        end
        object OneAttackEdit: TSpinEdit
          Left = 72
          Top = 24
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 0
          Value = 0
        end
        object FiveAttackEdit: TSpinEdit
          Left = 72
          Top = 56
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 1
          Value = 0
        end
        object TenAttackEdit: TSpinEdit
          Left = 72
          Top = 87
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 2
          Value = 0
        end
        object AllAttackEdit: TSpinEdit
          Left = 72
          Top = 136
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 3000
          MinValue = 0
          ReadOnly = True
          TabOrder = 3
          Value = 0
        end
        object PerOneAttackEdit: TSpinEdit
          Left = 152
          Top = 24
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 4
          Value = 0
        end
        object PerFiveAttackEdit: TSpinEdit
          Left = 152
          Top = 56
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 5
          Value = 0
        end
        object PerTenAttackEdit: TSpinEdit
          Left = 152
          Top = 88
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 6
          Value = 0
        end
        object PerAllAttackEdit: TSpinEdit
          Left = 152
          Top = 136
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 100
          ReadOnly = True
          TabOrder = 7
          Value = 100
        end
      end
    end
    object DefenceSheet: TTabSheet
      Caption = 'Defence'
      ImageIndex = 2
      object ApplyDefenceButton: TSpeedButton
        Left = 134
        Top = 186
        Width = 91
        Height = 25
        Caption = 'Apply'
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = ApplyDefenceButtonClick
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 3
        Width = 225
        Height = 177
        Caption = 'Defence bonuses'
        TabOrder = 0
        object Label6: TLabel
          Left = 8
          Top = 24
          Width = 56
          Height = 13
          Caption = '+1 defence'
        end
        object Label7: TLabel
          Left = 8
          Top = 56
          Width = 56
          Height = 13
          Caption = '+5 defence'
        end
        object Label8: TLabel
          Left = 8
          Top = 87
          Width = 62
          Height = 13
          Caption = '+10 defence'
        end
        object Label9: TLabel
          Left = 11
          Top = 136
          Width = 53
          Height = 13
          Caption = 'All defence'
        end
        object Bevel4: TBevel
          Left = 16
          Top = 120
          Width = 193
          Height = 2
        end
        object Bevel5: TBevel
          Left = 144
          Top = 16
          Width = 2
          Height = 98
        end
        object Bevel6: TBevel
          Left = 144
          Top = 128
          Width = 2
          Height = 41
        end
        object OneDefenceEdit: TSpinEdit
          Left = 72
          Top = 24
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 0
          Value = 0
        end
        object FiveDefenceEdit: TSpinEdit
          Left = 72
          Top = 56
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 1
          Value = 0
        end
        object TenDefenceEdit: TSpinEdit
          Left = 72
          Top = 87
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 1000
          MinValue = 0
          TabOrder = 2
          Value = 0
        end
        object AllDefenceEdit: TSpinEdit
          Left = 72
          Top = 136
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 3000
          MinValue = 0
          ReadOnly = True
          TabOrder = 3
          Value = 0
        end
        object PerOneDefenceEdit: TSpinEdit
          Left = 152
          Top = 24
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 4
          Value = 0
        end
        object PerFiveDefenceEdit: TSpinEdit
          Left = 152
          Top = 56
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 5
          Value = 0
        end
        object PerTenDefenceEdit: TSpinEdit
          Left = 152
          Top = 88
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 0
          TabOrder = 6
          Value = 0
        end
        object PerAllDefenceEdit: TSpinEdit
          Left = 152
          Top = 136
          Width = 57
          Height = 22
          EditorEnabled = False
          MaxValue = 100
          MinValue = 100
          ReadOnly = True
          TabOrder = 7
          Value = 100
        end
      end
    end
  end
  object AllBonusesText: TStaticText
    Left = 164
    Top = 272
    Width = 57
    Height = 22
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
end
