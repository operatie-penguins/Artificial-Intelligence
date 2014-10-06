unit ClassUnit;

interface

uses StatusUnit;

type
  TAimType = (atCage, atBonus, atLife, atAttack, atDefence, atMonster, atHero, atExit);
  TMoveDirection = (mdUp, mdDown, mdRight, mdLeft);
  TDirection = set of TMoveDirection;
  
  TFieldPoint = record
    x, y : ShortInt;
  end;
  TMoveMatrix = array[1..8] of TFieldPoint;

  TGlobalAim = (gaBonus, gaMonster, gaExit);
  TGlobalAimes = set of TGlobalAim;

  TField = class;

  TCreatureClass = class of TCreature;
  TCreature = class
    protected
      FLife : integer;
      FAttack : integer;
      FDefence : integer;
      FMaxLife : integer;
      FMaxAttack : integer;
      FMaxDefence : integer;
      FCoords : TFieldPoint;
      FAimCoords : TFieldPoint;
      FNeedCoords : TFieldPoint;
      FAim : TAimType;
      FMoveMatrix : TMoveMatrix;
      FField : TField;
      function IncLife ( const Value : integer ) : integer;
      function IncAttack ( const Value : integer ) : integer;
      function IncDefence ( const Value : integer ) : integer;
      function IncMaxLife ( const Value : integer ) : integer;
      function IncMaxAttack ( const Value : integer ) : integer;
      function IncMaxDefence ( const Value : integer ) : integer;
      function GetMoveCage ( Index : byte ) : TObject;
    public
      StatusForm : TStatusForm;
      property Life : integer read FLife;
      property Attack : integer read FAttack;
      property Defence : integer read FDefence;
      property MaxLife : integer read FMaxLife;
      property MaxAttack : integer read FMaxAttack;
      property MaxDefence : integer read FMaxDefence;
      property Coords : TFieldPoint read FCoords;
      property Aim : TAimType read FAim;
      property AimCoords : TFieldPoint read FAimCoords write FAimCoords;
      property MoveCage [ Index : byte ] : TObject read GetMoveCage;
      property MoveMatrix : TMoveMatrix read FMoveMatrix;
      function IncreaseLife ( const Value : integer = 1 ) : integer;
      function DecreaseLife ( const Value : integer = 1 ) : integer;
      function IncreaseAttack ( const Value : integer = 1 ) : integer;
      function DecreaseAttack ( const Value : integer = 1 ) : integer;
      function IncreaseDefence ( const Value : integer = 1 ) : integer;
      function DecreaseDefence ( const Value : integer = 1 ) : integer;
      procedure Move ( const Where : TDirection ); overload;
      procedure Move ( const incX, incY : integer ); overload;
      procedure FindAim ( const AimType : TAimType ; FindNearest : boolean = true );
      procedure CreateMoveMatrix ( const Where : TDirection );
      procedure GenerateCreature;
      constructor Create ( const Field : TField );
      function IsUpAim : boolean;
      function IsDownAim : boolean;
      function IsLeftAim : boolean;
      function IsRightAim : boolean;
      function NeedCage : TObject;
      function IsAimReached : boolean;
  end;

  THeroClass = class of THero;
  THero = class ( TCreature )
     public
       GlobalAimes : TGlobalAimes;
       IsAimChanging : boolean;
       function IsFewLife : boolean;
       function IsFewDefence : boolean;
       procedure SetMaxLife ( const Value : integer );
       procedure SetMaxDefence ( const Value : integer );
       procedure SetMaxAttack ( const Value : integer );
       function IncreaseMaxLife ( const Value : integer ) : integer;
       function IncreaseMaxAttack ( const Value : integer ) : integer;
       function IncreaseMaxDefence ( const Value : integer ) : integer;
  end;

  TMonsterClass = class of TMonster;
  TMonster = class ( TCreature )
    public
      MissTurnCount : integer;
      procedure SetMaxLife ( const Value : integer );
      procedure SetMaxAttack ( const Value : integer );
      procedure SetMaxDefence ( const Value : integer );
  end;

  TObstacleClass = class of TObstacle;
  TObstacle = class
    private
      FField : TField;
      FCoords : TFieldPoint;
    public
      property Coords : TFieldPoint read FCoords;
      procedure GenerateObstacle;
      constructor Create ( const Field : TField );
  end;

  TExitClass = class of TExit;
  TExit = class
    private
      FField : TField;
      FCoords : TFieldPoint;
    public
      property Coords : TFieldPoint read FCoords;
      procedure GenerateExit;
      constructor Create ( const Field : TField );
  end;

  TBonusClass = class of TBonus;
  TBonus = class
    protected
      FField : TField;
      FCoords : TFieldPoint;
    public
      StatusForm : TStatusForm;
      BonusValue : byte;
      property Coords : TFieldPoint read FCoords;
      procedure ApplyBonus ( const Creature : TCreature ); virtual; abstract;
  end;

  TLifeBonusClass = class of TLifeBonus;
  TLifeBonus = class ( TBonus )
    public
      procedure ApplyBonus ( const Creature : TCreature ); override;
      procedure GenerateLifeBonus;
      constructor Create ( const Field : TField; const Value : byte );
  end;

  TAttackBonusClass = class of TAttackBonus;
  TAttackBonus = class ( TBonus )
    public
      procedure ApplyBonus ( const Creature : TCreature ); override;
      procedure GenerateAttackBonus;
      constructor Create ( const Field : TField; const Value : byte );
  end;

  TDefenceBonusClass = class of TDefenceBonus;
  TDefenceBonus = class ( TBonus )
    public
      procedure ApplyBonus ( const Creature : TCreature ); override;
      procedure GenerateDefenceBonus;
      constructor Create ( const Field : TField; const Value : byte );
  end;

  TPointerArray = array[-1..100, -1..100] of TObject;

  TField = class
    private
      FFieldMatrix : TPointerArray;
      function GetFieldObject ( const X, Y : ShortInt ) : TObject;
      procedure SetFieldObject ( const X, Y : ShortInt; const Value : TObject );
    public
      FieldWidth : ShortInt;
      FieldHeight : ShortInt;
      property FieldMatrix [ const X, Y : ShortInt ] : TObject
        read GetFieldObject
        write SetFieldObject; default;
      function FindNearestObject ( const What : TClass; const WhereTo : TFieldPoint ) : TFieldPoint;
      procedure ClearField;
  end;

  TBattleTurn = class
    public
      StatusForm : TStatusForm;
      touche : boolean;
      defenceOut : boolean;
      lifeOut : boolean;
      contreattack : boolean;
      Attacker : TCreature;
      Defender : TCreature;
      function DeadByFirstAttack : boolean;
      procedure CountAll;
      procedure D_DefenceOut;
      procedure D_LifeOut;
      procedure A_AttackOut;
      procedure A_LifeOut;
  end;

implementation

uses Math, SysUtils;

{ TCreature }

constructor TCreature.Create(const Field: TField);
var i : integer;
begin
  if Field <> nil then
    FField := Field;
  for i := 1 to 8 do
    begin
      FMoveMatrix[i].x := 0;
      FMoveMatrix[i].y := 0;
    end;
end;

procedure TCreature.CreateMoveMatrix(const Where: TDirection);
begin
  if mdUp in Where then
    begin
      if mdLeft in Where then
        begin
          FMoveMatrix[1].x := FCoords.x-1;
          FMoveMatrix[1].y := FCoords.y-1;
          FMoveMatrix[2].x := FCoords.x;
          FMoveMatrix[2].y := FCoords.y-1;
          FMoveMatrix[3].x := FCoords.x-1;
          FMoveMatrix[3].y := FCoords.y;
          FMoveMatrix[4].x := FCoords.x+1;
          FMoveMatrix[4].y := FCoords.y-1;
          FMoveMatrix[5].x := FCoords.x-1;
          FMoveMatrix[5].y := FCoords.y+1;
          FMoveMatrix[6].x := FCoords.x+1;
          FMoveMatrix[6].y := FCoords.y;
          FMoveMatrix[7].x := FCoords.x;
          FMoveMatrix[7].y := FCoords.y+1;
          FMoveMatrix[8].x := FCoords.x+1;
          FMoveMatrix[8].y := FCoords.y+1;
          if StatusForm <> nil then
            StatusForm.HeroMemo.Lines.Add('Move matrix to left-up');
        end
      else
        if mdRight in Where then
          begin
            FMoveMatrix[1].x := FCoords.x+1;
            FMoveMatrix[1].y := FCoords.y-1;
            FMoveMatrix[2].x := FCoords.x+1;
            FMoveMatrix[2].y := FCoords.y;
            FMoveMatrix[3].x := FCoords.x;
            FMoveMatrix[3].y := FCoords.y-1;
            FMoveMatrix[4].x := FCoords.x+1;
            FMoveMatrix[4].y := FCoords.y+1;
            FMoveMatrix[5].x := FCoords.x-1;
            FMoveMatrix[5].y := FCoords.y-1;
            FMoveMatrix[6].x := FCoords.x;
            FMoveMatrix[6].y := FCoords.y+1;
            FMoveMatrix[7].x := FCoords.x-1;
            FMoveMatrix[7].y := FCoords.y;
            FMoveMatrix[8].x := FCoords.x-1;
            FMoveMatrix[8].y := FCoords.y+1;
            if StatusForm <> nil then
            StatusForm.HeroMemo.Lines.Add('Move matrix to right-up');
          end
        else
          begin
            FMoveMatrix[1].x := FCoords.x;
            FMoveMatrix[1].y := FCoords.y-1;
            FMoveMatrix[2].x := FCoords.x+1;
            FMoveMatrix[2].y := FCoords.y-1;
            FMoveMatrix[3].x := FCoords.x-1;
            FMoveMatrix[3].y := FCoords.y-1;
            FMoveMatrix[4].x := FCoords.x+1;
            FMoveMatrix[4].y := FCoords.y;
            FMoveMatrix[5].x := FCoords.x-1;
            FMoveMatrix[5].y := FCoords.y;
            FMoveMatrix[6].x := FCoords.x+1;
            FMoveMatrix[6].y := FCoords.y+1;
            FMoveMatrix[7].x := FCoords.x-1;
            FMoveMatrix[7].y := FCoords.y+1;
            FMoveMatrix[8].x := FCoords.x;
            FMoveMatrix[8].y := FCoords.y+1;
            if StatusForm <> nil then
            StatusForm.HeroMemo.Lines.Add('Move matrix to up');
          end;
    end                                    
  else
    if mdDown in Where then
      begin
        if mdLeft in Where then
          begin
            FMoveMatrix[1].x := FCoords.x-1;
            FMoveMatrix[1].y := FCoords.y+1;
            FMoveMatrix[2].x := FCoords.x-1;
            FMoveMatrix[2].y := FCoords.y;
            FMoveMatrix[3].x := FCoords.x;
            FMoveMatrix[3].y := FCoords.y+1;
            FMoveMatrix[4].x := FCoords.x-1;
            FMoveMatrix[4].y := FCoords.y-1;
            FMoveMatrix[5].x := FCoords.x+1;
            FMoveMatrix[5].y := FCoords.y+1;
            FMoveMatrix[6].x := FCoords.x;
            FMoveMatrix[6].y := FCoords.y-1;
            FMoveMatrix[7].x := FCoords.x+1;
            FMoveMatrix[7].y := FCoords.y;
            FMoveMatrix[8].x := FCoords.x+1;
            FMoveMatrix[8].y := FCoords.y-1;
            if StatusForm <> nil then
              StatusForm.HeroMemo.Lines.Add('Move matrix to left-down');
          end
        else
          if mdRight in Where then
            begin
              FMoveMatrix[1].x := FCoords.x+1;
              FMoveMatrix[1].y := FCoords.y+1;
              FMoveMatrix[2].x := FCoords.x;
              FMoveMatrix[2].y := FCoords.y+1;
              FMoveMatrix[3].x := FCoords.x+1;
              FMoveMatrix[3].y := FCoords.y;
              FMoveMatrix[4].x := FCoords.x-1;
              FMoveMatrix[4].y := FCoords.y+1;
              FMoveMatrix[5].x := FCoords.x+1;
              FMoveMatrix[5].y := FCoords.y-1;
              FMoveMatrix[6].x := FCoords.x-1;
              FMoveMatrix[6].y := FCoords.y;
              FMoveMatrix[7].x := FCoords.x;
              FMoveMatrix[7].y := FCoords.y-1;
              FMoveMatrix[8].x := FCoords.x-1;
              FMoveMatrix[8].y := FCoords.y-1;
              if StatusForm <> nil then
                StatusForm.HeroMemo.Lines.Add('Move matrix to right-down');
            end
          else
            begin
              FMoveMatrix[1].x := FCoords.x;
              FMoveMatrix[1].y := FCoords.y+1;
              FMoveMatrix[2].x := FCoords.x-1;
              FMoveMatrix[2].y := FCoords.y+1;
              FMoveMatrix[3].x := FCoords.x+1;
              FMoveMatrix[3].y := FCoords.y+1;
              FMoveMatrix[4].x := FCoords.x-1;
              FMoveMatrix[4].y := FCoords.y;
              FMoveMatrix[5].x := FCoords.x+1;
              FMoveMatrix[5].y := FCoords.y;
              FMoveMatrix[6].x := FCoords.x-1;
              FMoveMatrix[6].y := FCoords.y-1;
              FMoveMatrix[7].x := FCoords.x+1;
              FMoveMatrix[7].y := FCoords.y+1;
              FMoveMatrix[8].x := FCoords.x;
              FMoveMatrix[8].y := FCoords.y-1;
              if StatusForm <> nil then
                StatusForm.HeroMemo.Lines.Add('Move matrix to down');
            end;
      end;
end;

function TCreature.DecreaseAttack(const Value: integer): integer;
begin
  Result := IncAttack( -Value );
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add('Attack decrease : -'+inttostr(Value));
end;

function TCreature.DecreaseDefence(const Value: integer): integer;
begin
  Result := IncDefence (-Value);
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add('Defence decrease : -'+inttostr(Value));
end;

function TCreature.DecreaseLife(const Value: integer): integer;
begin
  Result := IncLife(-Value);
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add('Life decrease : -'+inttostr(Value));
end;

procedure TCreature.FindAim(const AimType: TAimType; FindNearest: boolean);
var RandX, RandY : ShortInt;
begin
  FAim := AimType;
  if StatusForm <> nil then
    case AimType of
      atCage    : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : cage');
      atBonus   : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : bonus');
      atLife    : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : life bonus');
      atAttack  : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : attack bonus');
      atDefence : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : defence bonus');
      atMonster : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : monster');
      atHero    : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : hero');
      atExit    : StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimType : exit');
    end;
  if FindNearest then
    begin
      case AimType of
        atCage    : FAimCoords := FField.FindNearestObject(nil, FCoords);
        atBonus   : FAimCoords := FField.FindNearestObject(TBonus, FCoords);
        atLife    : FAimCoords := FField.FindNearestObject(TLifeBonus, FCoords);
        atAttack  : FAimCoords := FField.FindNearestObject(TAttackBonus, FCoords);
        atDefence : FAimCoords := FField.FindNearestObject(TDefenceBonus, FCoords);
        atMonster : FAimCoords := FField.FindNearestObject(TMonster, FCoords);
        atHero    : FAimCoords := FField.FindNearestObject(THero, FCoords);
        atExit    : FAimCoords := FField.FindNearestObject(TExit, FCoords);
      end;
    end
  else
    begin
      case AimType of
        atCage    : begin
                      repeat
                        RandX := random(FField.FieldWidth);
                        RandY := random(FField.FieldHeight);
                      until FField.FieldMatrix[RandX, RandY] = nil;
                      FAimCoords.x := RandX;
                      FAimCoords.y := RandY;
                    end;
        atBonus   : begin
                      repeat
                        RandX := random(FField.FieldWidth);
                        RandY := random(FField.FieldHeight);
                      until FField.FieldMatrix[RandX, RandY] is TBonus;
                      FAimCoords.x := RandX;
                      FAimCoords.y := RandY;
                    end;
        atLife    : begin
                      repeat
                        RandX := random(FField.FieldWidth);
                        RandY := random(FField.FieldHeight);
                      until FField.FieldMatrix[RandX, RandY] is TLifeBonus;
                      FAimCoords.x := RandX;
                      FAimCoords.y := RandY;
                    end;
        atAttack  : begin
                      repeat
                        RandX := random(FField.FieldWidth);
                        RandY := random(FField.FieldHeight);
                      until FField.FieldMatrix[RandX, RandY] is TAttackBonus;
                      FAimCoords.x := RandX;
                      FAimCoords.y := RandY;
                    end;
        atDefence : begin
                      repeat
                        RandX := random(FField.FieldWidth);
                        RandY := random(FField.FieldHeight);
                      until FField.FieldMatrix[RandX, RandY] is TDefenceBonus;
                      FAimCoords.x := RandX;
                      FAimCoords.y := RandY;
                    end;
        atMonster : begin
                      repeat
                        RandX := random(FField.FieldWidth);
                        RandY := random(FField.FieldHeight);
                      until FField.FieldMatrix[RandX, RandY] is TMonster;
                      FAimCoords.x := RandX;
                      FAimCoords.y := RandY;
                    end;
        atHero    : begin
//                      repeat
//                        RandX := random(FField.FieldWidth);
//                        RandY := random(FField.FieldHeight);
//                      until FField.FieldMatrix[RandX, RandY] is THero;
//                      FAimCoords.x := RandX;
//                      FAimCoords.y := RandY;
                      FAimCoords := FField.FindNearestObject(THero, FCoords);
                    end;
        atExit    : begin
//                      repeat
//                        RandX := random(FField.FieldWidth);
//                        RandY := random(FField.FieldHeight);
//                      until FField.FieldMatrix[RandX, RandY] is TExit;
//                      FAimCoords.x := RandX;
//                      FAimCoords.y := RandY;
                      FAimCoords := FField.FindNearestObject(TExit, FCoords);
                    end;
      end;
    end;
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add(ClassName + ' : AimFound : x = ' + inttostr(FAimCoords.x) + ', y = ' + inttostr(FAimCoords.y));
end;

procedure TCreature.GenerateCreature;
begin
  repeat
    FCoords.x := random(FField.FieldWidth);
    FCoords.y := random(FField.FieldHeight);
  until FField.FieldMatrix[FCoords.x, FCoords.y] = nil;
  FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
end;

function TCreature.GetMoveCage(Index: byte): TObject;
begin
  Result := FField.FieldMatrix[FMoveMatrix[Index].x, FMoveMatrix[Index].y]
end;

function TCreature.IncAttack(const Value: integer): integer;
begin
  FAttack := FAttack + Value;
  if FAttack < 0 then
    FAttack := 0;
  Result := FAttack;
end;

function TCreature.IncDefence(const Value: integer): integer;
begin
  FDefence := FDefence + Value;
  if FDefence < 0 then
    FDefence := 0;
  Result := FDefence;
end;

function TCreature.IncLife(const Value: integer): integer;
begin
  FLife := FLife + Value;
  if FLife < 0 then
    FLife := 0;
  Result := FLife;
end;

function TCreature.IncMaxAttack(const Value: integer): integer;
begin
  FMaxAttack := FMaxAttack + Value;
  Result := FMaxAttack;
end;

function TCreature.IncMaxDefence(const Value: integer): integer;
begin
  FMaxDefence := FMaxDefence + Value;
  Result := FMaxDefence;
end;

function TCreature.IncMaxLife(const Value: integer): integer;
begin
  FMaxLife := FMaxLife + Value;
  Result := FMaxLife;
end;

function TCreature.IncreaseAttack(const Value: integer): integer;
begin
  Result := IncAttack(Value);
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add(ClassName + ' : Attack increase : +'+inttostr(Value));
end;

function TCreature.IncreaseDefence(const Value: integer): integer;
begin
  Result := IncDefence(Value);
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add(ClassName + ' : Defence increase : +'+inttostr(Value));
end;

function TCreature.IncreaseLife(const Value: integer): integer;
begin
  Result := IncLife(Value);
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add(ClassName + ' : Life increase : +'+inttostr(Value));
end;

function TCreature.IsAimReached: boolean;
begin
  Result := (FCoords.x = FAimCoords.x) and (FCoords.y = FAimCoords.y);
end;

function TCreature.IsDownAim: boolean;
begin
  Result := (FCoords.y < FAimCoords.y);
end;

function TCreature.IsLeftAim: boolean;
begin
  Result := (FCoords.x > FAimCoords.x);
end;

function TCreature.IsRightAim: boolean;
begin
  Result := (FCoords.x < FAimCoords.x);
end;

function TCreature.IsUpAim: boolean;
begin
  Result := (FCoords.y > FAimCoords.y);
end;

procedure TCreature.Move(const incX, incY: integer);
begin
  FField.FieldMatrix[FCoords.x, FCoords.y] := nil;
  inc(FCoords.x, incX);
  inc(FCoords.y, incY);
  if not(FField.FFieldMatrix[FCoords.x, FCoords.y] is TCreature) then
    FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add(ClassName + ' : Move to: x = ' + inttostr(FCoords.x) + ', y = ' + inttostr(FCoords.y));
end;

procedure TCreature.Move(const Where: TDirection);
begin
  FField.FieldMatrix[FCoords.x, FCoords.y] := nil;
  if mdUp in Where then
    FCoords.y := FCoords.y - 1;
  if mdDown in Where then
    FCoords.y := FCoords.y + 1;
  if mdLeft in Where then
    FCoords.x := FCoords.x - 1;
  if mdRight in Where then
    FCoords.x := FCoords.x + 1;
  if not(FField.FFieldMatrix[FCoords.x, FCoords.y] is TCreature) then
    FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add(ClassName + ' : Move to: x = ' + inttostr(FCoords.x) + ', y = ' + inttostr(FCoords.y));
end;

function TCreature.NeedCage: TObject;
begin
  Result := FField.FieldMatrix[(FCoords.x + Sign(FAimCoords.x - FCoords.x)), (FCoords.y + Sign(FAimCoords.y - FCoords.y))];
end;

{ TField }

procedure TField.ClearField;
var i, j : integer;
begin
  for i := -1 to 100 do
    for j := -1 to 100 do
      FFieldMatrix[i,j] := nil;
end;

function TField.FindNearestObject(const What: TClass;
  const WhereTo: TFieldPoint): TFieldPoint;
var minDistance : Double;
    Distance : Double;
    x, y : ShortInt;
begin
  minDistance := 200;
  if What <> nil then
    begin
      for x := 0 to FieldWidth - 1 do
        for y := 0 to FieldHeight - 1 do
          begin
            if (FFieldMatrix[x, y] <> nil) and (FFieldMatrix[x, y] is What) then
              begin
                Distance := sqrt(sqr(WhereTo.x - x) + sqr(WhereTo.y - y));
                if Distance < MinDistance then
                  begin
                    MinDistance := Distance;
                    Result.x := x;
                    Result.y := y;
                  end;
              end;
          end;
    end
  else
    begin
      for x := 0 to FieldWidth - 1 do
        for y := 0 to FieldHeight - 1 do
          begin
            if (FFieldMatrix[x, y] = nil) then
              begin
                Distance := sqrt(sqr(WhereTo.x - x) + sqr(WhereTo.y - y));
                if Distance < MinDistance then
                  begin
                    MinDistance := Distance;
                    Result.x := x;
                    Result.y := y;
                  end;
              end;
          end;
    end
end;

function TField.GetFieldObject(const X, Y: ShortInt): TObject;
begin
  if (X>=-1) and (X<=FieldWidth) and (Y>=-1) and (Y<=FieldHeight) then
    Result := FFieldMatrix[X, Y]
  else
    Result := nil;
end;

procedure TField.SetFieldObject(const X, Y: ShortInt; const Value: TObject);
begin
  if (X>=-1) and (X<=FieldWidth) and (Y>=-1) and (Y<=FieldHeight) then
    FFieldMatrix[X, Y] := Value;
end;

{ THero }

function THero.IncreaseMaxAttack(const Value: integer): integer;
begin
  inc(FMaxAttack, Value);
  Result := FMaxAttack;
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add('Hero : Increase max attack : +' + inttostr(Value));
end;

function THero.IncreaseMaxDefence(const Value: integer): integer;
begin
  inc(FMaxDefence, Value);
  Result := FMaxDefence;
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add('Hero : Increase max defence : +' + inttostr(Value));
end;

function THero.IncreaseMaxLife(const Value: integer): integer;
begin
  inc(FMaxLife, Value);
  Result := FMaxLife;
  if StatusForm <> nil then
    StatusForm.HeroMemo.Lines.Add('Hero : Increase max life : +' + inttostr(Value));
end;

function THero.IsFewDefence: boolean;
begin
  if FDefence < FAttack then
    Result := true
  else
    Result := false;
end;

function THero.IsFewLife: boolean;
begin
  if FLife < (FMaxLife div 2) then
    Result := true
  else
    Result := false;
end;

procedure THero.SetMaxAttack(const Value: integer);
begin
  FMaxLife := Value;
  FLife := Value;
end;

procedure THero.SetMaxDefence(const Value: integer);
begin
  FMaxDefence := Value;
  FDefence := Value;
end;

procedure THero.SetMaxLife(const Value: integer);
begin
  FMaxAttack := Value;
  FAttack := Value;
end;

{ TExit }

constructor TExit.Create(const Field: TField);
begin
  if FIeld <> nil then
    FField := Field;
end;

procedure TExit.GenerateExit;
begin
  repeat
    FCoords.x := random(FField.FieldWidth);
    FCoords.y := random(FField.FieldHeight);
  until FField.FieldMatrix[FCoords.x, FCoords.y] = nil;
  FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
end;

{ TLifeBonus }

procedure TLifeBonus.ApplyBonus(const Creature: TCreature);
begin
  if Creature <> nil then
    begin
      Creature.IncreaseLife(BonusValue);
      if StatusForm <> nil then
        StatusForm.HeroMemo.Lines.Add(Creature.ClassName + ' : Apply life bonus : +' + inttostr(BonusValue));
    end;
end;

constructor TLifeBonus.Create(const Field: TField; const Value: byte);
begin
  if Field <> nil then
    FField := Field;
  BonusValue := Value;
end;

procedure TLifeBonus.GenerateLifeBonus;
begin
  repeat
    FCoords.x := random(FField.FieldWidth);
    FCoords.y := random(FField.FieldHeight);
  until FField.FieldMatrix[FCoords.x, FCoords.y] = nil;
  FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
end;

{ TObstacle }

constructor TObstacle.Create(const Field: TField);
begin
  if Field <> nil then
    FField := Field;
end;

procedure TObstacle.GenerateObstacle;
begin
  repeat
    FCoords.x := random(FField.FieldWidth);
    FCoords.y := random(FField.FieldHeight);
  until FField.FieldMatrix[FCoords.x, FCoords.y] = nil;
  FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
end;

{ TAttackBonus }

procedure TAttackBonus.ApplyBonus(const Creature: TCreature);
begin
  if Creature <> nil then
    begin
      Creature.IncreaseAttack(BonusValue);
      if StatusForm <> nil then
        StatusForm.HeroMemo.Lines.Add(Creature.ClassName + ' : Apply attack bonus : +' + inttostr(BonusValue));
    end;
end;

constructor TAttackBonus.Create(const Field: TField; const Value: byte);
begin
  if Field <> nil then
    FField := Field;
  BonusValue := Value;
end;

procedure TAttackBonus.GenerateAttackBonus;
begin
  repeat
    FCoords.x := random(FField.FieldWidth);
    FCoords.y := random(FField.FieldHeight);
  until FField.FieldMatrix[FCoords.x, FCoords.y] = nil;
  FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
end;

{ TDefenceBonus }

procedure TDefenceBonus.ApplyBonus(const Creature: TCreature);
begin
  if Creature <> nil then
    begin
      Creature.IncreaseDefence(BonusValue);
      if StatusForm <> nil then
        StatusForm.HeroMemo.Lines.Add(Creature.ClassName + ' : Apply defence bonus : +' + inttostr(BonusValue));
    end;
end;

constructor TDefenceBonus.Create(const Field: TField; const Value: byte);
begin
  if Field <> nil then
    FField := Field;
  BonusValue := Value;
end;

procedure TDefenceBonus.GenerateDefenceBonus;
begin
  repeat
    FCoords.x := random(FField.FieldWidth);
    FCoords.y := random(FField.FieldHeight);
  until FField.FieldMatrix[FCoords.x, FCoords.y] = nil;
  FField.FieldMatrix[FCoords.x, FCoords.y] := Self;
end;

{ TMonster }

procedure TMonster.SetMaxAttack(const Value: integer);
begin
  FMaxAttack := Value;
  FAttack := Value;
end;

procedure TMonster.SetMaxDefence(const Value: integer);
begin
  FMaxDefence := Value;
  FDefence := Value;
end;

procedure TMonster.SetMaxLife(const Value: integer);
begin
  FMaxLife := Value;
  FLife := Value;
end;

{ TBattle }

procedure TBattleTurn.A_AttackOut;
begin
  Attacker.DecreaseAttack;
end;

procedure TBattleTurn.A_LifeOut;
begin
  if Defender.Attack > Attacker.Defence then
        Attacker.DecreaseLife(random(Defender.Attack - Attacker.Defence)+1)
      else
        Attacker.DecreaseLife;
end;

procedure TBattleTurn.CountAll;
begin
  touche := (random(4) >= 1);
  defenceOut := (random(4) >= 3);
  lifeOut := (Attacker.Attack > Defender.Defence);
  contreattack := (random(4) >= 3);
  if StatusForm <> nil then
    begin
      if touche then
        StatusForm.HeroMemo.Lines.Add('Touche!');
      if defenceOut then
        StatusForm.HeroMemo.Lines.Add('Defence out!');
      if lifeOut then
        StatusForm.HeroMemo.Lines.Add('Life out!');
      if contreattack then
        StatusForm.HeroMemo.Lines.Add('Contreattack!');
    end;
end;

function TBattleTurn.DeadByFirstAttack: boolean;
begin
  Result := (Attacker.Attack - Defender.Defence >= Defender.Life);
end;

procedure TBattleTurn.D_DefenceOut;
begin
  Defender.DecreaseDefence(random(Attacker.Attack)+1);
end;

procedure TBattleTurn.D_LifeOut;
begin
  Defender.DecreaseLife(random(Attacker.Attack - Defender.Defence)+1)
end;

end.
