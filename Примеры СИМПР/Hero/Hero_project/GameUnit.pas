unit GameUnit;

interface

uses ClassUnit, StatusUnit,
     Contnrs, Classes;

type
  TMonsterParameter = class
    Name : string;
    Life : integer;
    Attack : integer;
    Defence : integer;
    Count : integer;
  end;

  TMonsterParameterList = class (TObjectList)
    protected
      function GetItems ( Index : integer ) : TMonsterParameter;
      procedure SetItems ( Index : integer; const Value : TMonsterParameter );
    public
      procedure LoadFromFile;
      procedure SaveToFile;
      function Add(aClass: TMonsterParameter): Integer;
      function Remove(aClass: TMonsterParameter): Integer;
      function IndexOf(aClass: TMonsterParameter): Integer;
      procedure Insert(Index: Integer; aClass: TMonsterParameter);
      property Items[Index: Integer]: TMonsterParameter read GetItems write SetItems; default;
  end;

  TMonsterList = class ( TObjectList )
    protected
      function GetItems ( Index : integer ) : TMonster;
      procedure SetItems ( Index : integer; const Value : TMonster );
    public
      function Add(aClass: TMonster): Integer;
      function Remove(aClass: TMonster): Integer;
      function IndexOf(aClass: TMonster): Integer;
      procedure Insert(Index: Integer; aClass: TMonster);
      property Items[Index: Integer]: TMonster read GetItems write SetItems; default;
  end;

  TLifeBonusList = class ( TObjectList )
    protected
      function GetItems ( Index : integer ) : TLifeBonus;
      procedure SetItems ( Index : integer; const Value : TLifeBonus );
    public
      function Add(aClass: TLifeBonus): Integer;
      function Remove(aClass: TLifeBonus): Integer;
      function IndexOf(aClass: TLifeBonus): Integer;
      procedure Insert(Index: Integer; aClass: TLifeBonus);
      property Items[Index: Integer]: TLifeBonus read GetItems write SetItems; default;
  end;

  TAttackBonusList = class ( TObjectList )
    protected
      function GetItems ( Index : integer ) : TAttackBonus;
      procedure SetItems ( Index : integer; const Value : TAttackBonus );
    public
      function Add(aClass: TAttackBonus): Integer;
      function Remove(aClass: TAttackBonus): Integer;
      function IndexOf(aClass: TAttackBonus): Integer;
      procedure Insert(Index: Integer; aClass: TAttackBonus);
      property Items[Index: Integer]: TAttackBonus read GetItems write SetItems; default;
  end;

  TDefenceBonusList = class ( TObjectList )
    protected
      function GetItems ( Index : integer ) : TDefenceBonus;
      procedure SetItems ( Index : integer; const Value : TDefenceBonus );
    public
      function Add(aClass: TDefenceBonus): Integer;
      function Remove(aClass: TDefenceBonus): Integer;
      function IndexOf(aClass: TDefenceBonus): Integer;
      procedure Insert(Index: Integer; aClass: TDefenceBonus);
      property Items[Index: Integer]: TDefenceBonus read GetItems write SetItems; default;
  end;

  TObstacleList = class ( TObjectList )
    protected
      function GetItems ( Index : integer ) : TObstacle;
      procedure SetItems ( Index : integer; const Value : TObstacle );
    public
      function Add(aClass: TObstacle): Integer;
      function Remove(aClass: TObstacle): Integer;
      function IndexOf(aClass: TObstacle): Integer;
      procedure Insert(Index: Integer; aClass: TObstacle);
      property Items[Index: Integer]: TObstacle read GetItems write SetItems; default;
  end;

  TGame = class
    private
      FField : TField;
      FHero : THero;
      FMonsterList : TMonsterList;
      FLifeBonusList : TLifeBonusList;
      FAttackBonusList : TAttackBonusList;
      FDefenceBonusList : TDefenceBonusList;
      FObstacleList : TObstacleList;
      FExit : TExit;
      FBattleTurn : TBattleTurn;
    public
      CurrentMonster : TMonster;
      BattleMonster : TMonster;
      EofMonster : boolean;
      Battle : boolean;
      property Field : TField read FField;
      property Hero : THero read FHero;
      property MonsterList : TMonsterList read FMonsterList;
      property LifeBonusList : TLifeBonusList read FLifeBonusList;
      property AttackBonusList : TAttackBonusList read FAttackBonusList;
      property DefenceBonusList : TDefenceBonusList read FDefenceBonusList;
      property BattleTurn : TBattleTurn read FBattleTurn;
      procedure NextMonster;
      constructor Create;
      procedure SetFieldParameters ( const FieldWidth, FieldHeight : ShortInt; const ObstaclePercent : byte );
      procedure SetHeroParameters ( const MaxLife, MaxAttack, MaxDefence : integer; const GA : TGlobalAimes );
      procedure SetMonsterParameters ( const MonsterParameters : TMonsterParameterList );
      procedure SetLifeParameters ( const One, Five, Ten : integer );
      procedure SetAttackParameters ( const One, Five, Ten : integer );
      procedure SetDefenceParameters ( const One, Five, Ten : integer );
      function HasBonuses : boolean;
      function HasLifeBonuses : boolean;
      function HasAttackBonuses : boolean;
      function HasDefenceBonuses : boolean;
      function HasMonsters : boolean;
      procedure BeginBattle ( const C1, C2 : TCreature );
      procedure NextBattleTurn;
      procedure EndBattle;
      function DeathByFirstAttack (const C1, C2 : TCreature ) : boolean;
      procedure DeathOfMonster;
      procedure ReAimMonsters;
      procedure ReAimHero;
      procedure AssignForm ( StatusForm : TStatusForm );
      procedure UpdateField;
      procedure DeleteBonus ( C : TFieldPoint );
  end;

implementation

{ TMonsterList }

uses SysUtils;

function TMonsterList.Add(aClass: TMonster): Integer;
begin
  Result := inherited Add(aClass);
end;

function TMonsterList.GetItems(Index: integer): TMonster;
begin
  Result := TMonster(inherited GetItem (Index));
end;

function TMonsterList.IndexOf(aClass: TMonster): Integer;
begin
  Result := inherited IndexOf(aClass);
end;

procedure TMonsterList.Insert(Index: Integer; aClass: TMonster);
begin
  inherited Insert(Index, aClass);
end;

function TMonsterList.Remove(aClass: TMonster): Integer;
begin
  Result := inherited Remove(aClass);
end;

procedure TMonsterList.SetItems(Index: integer; const Value: TMonster);
begin
  inherited Items[Index] := Value;
end;

{ TLifeBonusList }

function TLifeBonusList.Add(aClass: TLifeBonus): Integer;
begin
  Result := inherited Add(aClass);
end;

function TLifeBonusList.GetItems(Index: integer): TLifeBonus;
begin
  Result := TLifeBonus(inherited GetItem(Index));
end;

function TLifeBonusList.IndexOf(aClass: TLifeBonus): Integer;
begin
  Result := inherited IndexOf(aClass);
end;

procedure TLifeBonusList.Insert(Index: Integer; aClass: TLifeBonus);
begin
  inherited Insert(Index, aClass);
end;

function TLifeBonusList.Remove(aClass: TLifeBonus): Integer;
begin
  Result := inherited Remove(aClass);
end;

procedure TLifeBonusList.SetItems(Index: integer; const Value: TLifeBonus);
begin
  inherited SetItem(Index, Value);
end;

{ TAttackBonusList }

function TAttackBonusList.Add(aClass: TAttackBonus): Integer;
begin
  Result := inherited Add(aClass);
end;

function TAttackBonusList.GetItems(Index: integer): TAttackBonus;
begin
  Result := TAttackBonus(inherited GetItem(Index));
end;

function TAttackBonusList.IndexOf(aClass: TAttackBonus): Integer;
begin
  Result := inherited IndexOf(aClass);
end;

procedure TAttackBonusList.Insert(Index: Integer; aClass: TAttackBonus);
begin
  inherited Insert(Index, aClass);
end;

function TAttackBonusList.Remove(aClass: TAttackBonus): Integer;
begin
  Result := inherited Remove(aClass);
end;

procedure TAttackBonusList.SetItems(Index: integer; const Value: TAttackBonus);
begin
  inherited SetItem(Index, Value);
end;

{ TDefenceBonusList }

function TDefenceBonusList.Add(aClass: TDefenceBonus): Integer;
begin
  Result := inherited Add(aClass);
end;

function TDefenceBonusList.GetItems(Index: integer): TDefenceBonus;
begin
  Result := TDefenceBonus(inherited GetItem(Index));
end;

function TDefenceBonusList.IndexOf(aClass: TDefenceBonus): Integer;
begin
  Result := inherited IndexOf(aClass);
end;

procedure TDefenceBonusList.Insert(Index: Integer; aClass: TDefenceBonus);
begin
  inherited Insert(Index, aClass);
end;

function TDefenceBonusList.Remove(aClass: TDefenceBonus): Integer;
begin
  Result := inherited Remove(aClass);
end;

procedure TDefenceBonusList.SetItems(Index: integer;
  const Value: TDefenceBonus);
begin
  inherited SetItem(Index, Value);
end;

{ TObstacleList }

function TObstacleList.Add(aClass: TObstacle): Integer;
begin
  Result := inherited Add(aClass);
end;

function TObstacleList.GetItems(Index: integer): TObstacle;
begin
  Result := TObstacle(inherited GetItem(Index));
end;

function TObstacleList.IndexOf(aClass: TObstacle): Integer;
begin
  Result := inherited IndexOf(aClass);
end;

procedure TObstacleList.Insert(Index: Integer; aClass: TObstacle);
begin
  inherited Insert(Index, aClass);
end;

function TObstacleList.Remove(aClass: TObstacle): Integer;
begin
  Result := inherited Remove(aClass);
end;

procedure TObstacleList.SetItems(Index: integer; const Value: TObstacle);
begin
  inherited SetItem(Index, Value);
end;

{ TGame }

procedure TGame.AssignForm(StatusForm: TStatusForm);
var i : integer;
begin
  FHero.StatusForm := StatusForm;
  for i := 0 to FMonsterList.Count - 1 do
    FMonsterList[i].StatusForm := StatusForm;
  for i := 0 to FLifeBonusList.Count - 1 do
    FLifeBonusList[i].StatusForm := StatusForm;
  for i := 0 to FAttackBonusList.Count - 1 do
    FAttackBonusList[i].StatusForm := StatusForm;
  for i := 0 to FDefenceBonusList.Count - 1 do
    FDefenceBonusList[i].StatusForm := StatusForm; 
end;

procedure TGame.BeginBattle(const C1, C2: TCreature);
begin
  Battle := true;
  FBattleTurn := TBattleTurn.Create;
  FBattleTurn.StatusForm := FHero.StatusForm;
  FBattleTurn.StatusForm.HeroMemo.Lines.Add('Begin battle!');
  FBattleTurn.Attacker := C1;
  FBattleTurn.Defender := C2;
  if FBattleTurn.Attacker is THero then
    FBattleTurn.StatusForm.HeroMemo.Lines.Add('Attacker = Hero, Defender = Monster')
  else
    FBattleTurn.StatusForm.HeroMemo.Lines.Add('Attacker = Monster, Defender = Hero');
  FBattleTurn.CountAll;
end;

constructor TGame.Create;
var m : TMonsterParameterList;
begin
  FField := TField.Create;
  FAttackBonusList := TAttackBonusList.Create;
  FDefenceBonusList := TDefenceBonusList.Create;
  FHero := THero.Create(FField);
  FMonsterList := TMonsterList.Create;
  FLifeBonusList := TLifeBonusList.Create;
  FObstacleList := TObstacleList.Create;
  FExit := TExit.Create(FField);
  SetFieldParameters(20, 15, 5);
  SetHeroParameters(10, 10, 10, [gaExit, gaBonus]);
  m := TMonsterParameterList.Create;
  m.LoadFromFile;
  SetMonsterParameters(m);
  SetLifeParameters(3, 3, 3);
  SetAttackParameters(3, 3, 3);
  SetDefenceParameters(3, 3, 3);
  CurrentMonster := FMonsterList[0];
end;

function TGame.DeathByFirstAttack(const C1, C2: TCreature): boolean;
begin
  FBattleTurn := TBattleTurn.Create;
  FBattleTurn.Attacker := C1;
  FBattleTurn.Defender := C2;
  Result := FBattleTurn.DeadByFirstAttack;
  FBattleTurn.Free;
  FBattleTurn := nil;
end;

procedure TGame.DeathOfMonster;
var Index : integer;
begin
  if FMonsterList.IndexOf(CurrentMonster) = FMonsterList.Count - 1 then
    begin
      EofMonster := true;
      FMonsterList.Remove(CurrentMonster);
      CurrentMonster := nil;
    end
  else
    begin
      EofMonster := false;
      Index := FMonsterList.IndexOf(CurrentMonster);
      FMonsterList.Remove(CurrentMonster);
      if FMonsterList.Count = 0
        then
          begin
            EofMonster := true;
            CurrentMonster := nil;
          end
        else
          CurrentMonster := FMonsterList[Index];
    end;
end;

procedure TGame.DeleteBonus(C: TFieldPoint);
begin
  if Field[C.x, C.y] is TBonus then
    begin
      if Field[C.x, C.y] is TAttackBonus then
        begin
          FAttackBonusList.Remove(Field[C.x, C.y] as TAttackBonus);
          UpdateField;
        end
      else
        begin
          if Field[C.x, C.y] is TLifeBonus then
            begin
              FLifeBonusList.Remove(Field[C.x, C.y] as TLifeBonus);
              UpdateField;
            end
          else
            begin
              if Field[C.x, C.y] is TDefenceBonus then
                begin
                  FDefenceBonusList.Remove(Field[C.x, C.y] as TDefenceBonus);
                  UpdateField;
                end;
            end;
        end;
    end;
end;

procedure TGame.EndBattle;
begin
  FBattleTurn.StatusForm.HeroMemo.Lines.Add('End battle!');
  if FBattleTurn.Attacker.Life > 0 then
    FField.FieldMatrix[FBattleTurn.Attacker.Coords.x, FBattleTurn.Attacker.Coords.y] := FBattleTurn.Attacker
  else
    FField.FieldMatrix[FBattleTurn.Defender.Coords.x, FBattleTurn.Defender.Coords.y] := FBattleTurn.Defender;
  FBattleTurn.Attacker := nil;
  FBattleTurn.Defender := nil;
  FBattleTurn.Free;
  FBattleTurn := nil;
  Battle := false;
end;

function TGame.HasAttackBonuses: boolean;
begin
  Result := (FAttackBonusList.Count <> 0);
end;

function TGame.HasBonuses: boolean;
begin
  Result := HasLifeBonuses or HasAttackBonuses or HasDefenceBonuses;
end;

function TGame.HasDefenceBonuses: boolean;
begin
  Result := (FDefenceBonusList.Count <> 0);
end;

function TGame.HasLifeBonuses: boolean;
begin
  Result := (FLifeBonusList.Count <> 0);
end;

function TGame.HasMonsters: boolean;
begin
  Result := (FMonsterList.Count <> 0);
end;

procedure TGame.NextBattleTurn;
var tmp : TCreature;
begin
  tmp := FBattleTurn.Attacker;
  FBattleTurn.Attacker :=  FBattleTurn.Defender;
  FBattleTurn.Defender := tmp;
  FBattleTurn.StatusForm.HeroMemo.Lines.Add('Next battle turn!');
  if FBattleTurn.Attacker is THero then
    FBattleTurn.StatusForm.HeroMemo.Lines.Add('Attacker = Hero, Defender = Monster')
  else
    FBattleTurn.StatusForm.HeroMemo.Lines.Add('Attacker = Monster, Defender = Hero');
  FBattleTurn.CountAll;
end;

procedure TGame.NextMonster;
begin
  if EofMonster then
    begin
      if FMonsterList.Count <> 0
        then
          begin
            CurrentMonster := FMonsterList[0];
            EofMonster := false;
          end;  
    end
  else
    begin
      if FMonsterList.IndexOf(CurrentMonster) = FMonsterList.Count - 1 then
        begin
          EofMonster := true;
          CurrentMonster := nil;
        end
      else
        begin
          CurrentMonster := FMonsterList[FMonsterList.IndexOf(CurrentMonster)+1];
          EofMonster := false;
        end;
    end;
end;

procedure TGame.ReAimHero;
var i, j : integer;
    fl : boolean;
begin
  if FHero.Aim = atMonster then
    begin
      fl := false;
      if not(FField.FieldMatrix[FHero.AimCoords.x, FHero.AimCoords.y] is TMonster) then
        begin
          for i := -1 to 1 do
            for j := -1 to 1 do
              if FField[FHero.AimCoords.x+i, FHero.AimCoords.y+j] is TMonster then
                begin
                  FHero.AimCoords := (FField[FHero.AimCoords.x+i, FHero.AimCoords.y+j] as TMonster).Coords;
                  fl := true;
                end;
        end
      else
        fl := true;
      if not(fl) then
        FHero.FindAim(atMonster);
    end;
end;

procedure TGame.ReAimMonsters;
var i : integer;
begin
  for i := 0 to FMonsterList.Count - 1 do
    FMonsterList[i].FindAim(atHero);
end;

procedure TGame.SetAttackParameters(const One, Five, Ten: integer);
var i : integer;
begin
  FAttackBonusList.Clear;
  for i := 1 to One do
    FAttackBonusList.Add(TAttackBonus.Create(FField, 1));
  for i := 1 to Five do
    FAttackBonusList.Add(TAttackBonus.Create(FField, 5));
  for i := 1 to Ten do
    FAttackBonusList.Add(TAttackBonus.Create(FField, 10));
  for i := 0 to FAttackBonusList.Count - 1 do
    FAttackBonusList[i].GenerateAttackBonus;
end;

procedure TGame.SetDefenceParameters(const One, Five, Ten: integer);
var i : integer;
begin
  FDefenceBonusList.Clear;
  for i := 1 to One do
    FDefenceBonusList.Add(TDefenceBonus.Create(FField, 1));
  for i := 1 to Five do
    FDefenceBonusList.Add(TDefenceBonus.Create(FField, 5));
  for i := 1 to Ten do
    FDefenceBonusList.Add(TDefenceBonus.Create(FField, 10));
  for i := 0 to FDefenceBonusList.Count - 1 do
    FDefenceBonusList[i].GenerateDefenceBonus;
end;

procedure TGame.SetFieldParameters(const FieldWidth, FieldHeight: ShortInt;
  const ObstaclePercent: byte);
var i : integer;
begin
  if (FieldWidth >= 10) and (FieldWidth <= 100) then
    FField.FieldWidth := FieldWidth;
  if (FieldHeight >= 10) and (FieldHeight <= 100) then
    FField.FieldHeight := FieldHeight;
  FField.ClearField;
  FObstacleList.Clear;
  for i := 0 to trunc(FieldWidth*FieldHeight*ObstaclePercent/100) - 1 do
    FObstacleList.Add(TObstacle.Create(FField));
  for i := 0 to FObstacleList.Count - 1 do
    FObstacleList[i].GenerateObstacle;
  FExit.GenerateExit;
// TObject or TObstacle? забивать их в ObstacleList?    
  FField.FieldMatrix[-1,-1] := TObject.Create;
  FField.FieldMatrix[-1,FieldHeight] := TObject.Create;
  FField.FieldMatrix[FieldWidth,-1] := TObject.Create;
  FField.FieldMatrix[FieldWidth,FieldHeight] := TObject.Create;
  for i := 0 to FieldWidth - 1 do
    begin
      FField.FieldMatrix[i,-1] := TObject.Create;
      FField.FieldMatrix[i,FieldHeight] := TObject.Create;
    end;
  for i := 0 to FieldHeight - 1 do
    begin
      FField.FieldMatrix[-1,i] := TObject.Create;
      FField.FieldMatrix[FieldWidth,i] := TObject.Create;
    end; 
end;

procedure TGame.SetHeroParameters(const MaxLife, MaxAttack,
  MaxDefence: integer; const GA : TGlobalAimes );
begin
  FHero.SetMaxLife(MaxLife);
  FHero.SetMaxDefence(MaxDefence);
  FHero.SetMaxAttack(MaxAttack);
  FHero.GlobalAimes := GA;
  FHero.GenerateCreature;
end;

procedure TGame.SetLifeParameters(const One, Five, Ten: integer);
var i : integer;
begin
  FLifeBonusList.Clear;
  for i := 1 to One do
    FLifeBonusList.Add(TLifeBonus.Create(FField, 1));
  for i := 1 to Five do
    FLifeBonusList.Add(TLifeBonus.Create(FField, 5));
  for i := 1 to Ten do
    FLifeBonusList.Add(TLifeBonus.Create(FField, 10));
  for i := 0 to FLifeBonusList.Count - 1 do
    FLifeBonusList[i].GenerateLifeBonus;
end;

procedure TGame.SetMonsterParameters(
  const MonsterParameters: TMonsterParameterList);
var i : integer;
    j : integer;
    Monster : TMonster;
begin
  if MonsterParameters <> nil then
    begin
      FMonsterList.Clear;
      for i := 0 to MonsterParameters.Count - 1 do
        for j := 0 to MonsterParameters[i].Count - 1 do
          begin
            Monster := TMonster.Create(FField);
            Monster.SetMaxLife(MonsterParameters[i].Life);
            Monster.SetMaxAttack(MonsterParameters[i].Attack);
            Monster.SetMaxDefence(MonsterParameters[i].Defence);
            Monster.MissTurnCount := 0;
          //  Monster.FindAim(atHero);
            FMonsterList.Add(Monster);
          end;
      for i := 0 to FMonsterList.Count - 1 do
        begin
          FMonsterList[i].GenerateCreature;
          FMonsterList[i].FindAim(atHero);
        end;
    end;
end;

procedure TGame.UpdateField;
var i, j : integer;
begin
  for i := 0 to 99 do
    for j := 0 to 99 do
      FField[i, j] := nil;
  for i := 0 to FObstacleList.Count - 1 do
    FField[FObstacleList[i].Coords.x, FObstacleList[i].Coords.y] := FObstacleList[i];
  FField[FExit.Coords.x, FExit.Coords.y] := FExit;
  for i := 0 to FLifeBonusList.Count - 1 do
    if FField[FLifeBonusList[i].Coords.x, FLifeBonusList[i].Coords.y] = nil then
      FField[FLifeBonusList[i].Coords.x, FLifeBonusList[i].Coords.y] := FLifeBonusList[i];
  for i := 0 to FAttackBonusList.Count - 1 do
    if FField[FAttackBonusList[i].Coords.x, FAttackBonusList[i].Coords.y] = nil then
      FField[FAttackBonusList[i].Coords.x, FAttackBonusList[i].Coords.y] := FAttackBonusList[i];
  for i := 0 to FDefenceBonusList.Count - 1 do
    if FField[FDefenceBonusList[i].Coords.x, FDefenceBonusList[i].Coords.y] = nil then
      FField[FDefenceBonusList[i].Coords.x, FDefenceBonusList[i].Coords.y] := FDefenceBonusList[i];
  for i := 0 to FMonsterList.Count - 1 do
    if FField[FMonsterList[i].Coords.x, FMonsterList[i].Coords.y] = nil then
      FField[FMonsterList[i].Coords.x, FMonsterList[i].Coords.y] := FMonsterList[i];
  if FField[FHero.Coords.x, FHero.Coords.y] = nil then
      FField[FHero.Coords.x, FHero.Coords.y] := FHero;
end;

{ TMonsterParameterList }

function TMonsterParameterList.Add(aClass: TMonsterParameter): Integer;
begin
  Result := inherited Add(aClass);
end;

function TMonsterParameterList.GetItems(Index: integer): TMonsterParameter;
begin
  Result := TMonsterParameter(inherited GetItem(Index));
end;

function TMonsterParameterList.IndexOf(aClass: TMonsterParameter): Integer;
begin
  Result := inherited IndexOf(aClass);
end;

procedure TMonsterParameterList.Insert(Index: Integer;
  aClass: TMonsterParameter);
begin
  inherited Insert(Index, aClass);
end;

procedure TMonsterParameterList.LoadFromFile;
var f : TextFile;
    MonsterParameter : TMonsterParameter;
begin
  AssignFile(f, 'Monsters.txt');
  try
    reset(f);
    while not(eof(f)) do
      begin
        MonsterParameter := TMonsterParameter.Create;
        readln(f, MonsterParameter.Name);
        readln(f, MonsterParameter.Life);
        readln(f, MonsterParameter.Attack);
        readln(f, MonsterParameter.Defence);
        MonsterParameter.Count := 1;
        Add(MonsterParameter);
      end;
    CloseFile(f);
  except
    raise EAbort.Create('');
  end;
end;

function TMonsterParameterList.Remove(aClass: TMonsterParameter): Integer;
begin
  Result := inherited Remove(aClass);
end;

procedure TMonsterParameterList.SaveToFile;
var f : TextFile;
    i : integer;
begin
  AssignFile (f, 'Monsters.txt');
  try
    rewrite(f);
      for i := 0 to Count - 1 do
        begin
          writeln(Items[i].Name);
          writeln(Items[i].Life);
          writeln(Items[i].Attack);
          writeln(Items[i].Defence);
        end;
    CloseFile(f);
  except
    raise EAbort.Create('');
  end;
end;

procedure TMonsterParameterList.SetItems(Index: integer;
  const Value: TMonsterParameter);
begin
  inherited SetItem (Index, Value);
end;

end.
