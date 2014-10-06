unit Unit2;

interface

type

  TCoords = class
    constructor Create(aX: Integer; aY: Integer);
  private
    X: Integer;
    Y: Integer;
    procedure SetX(aX: Integer);
    procedure SetY(aY: Integer);
  public
    function GetX: Integer;
    function GetY: Integer;
  end;

  TMovingObject = class
    constructor Create(aX: Integer; aY: Integer; aDirection: Integer);
  private
    Coords: TCoords;
    Direction: Integer;
  public
    procedure Move;
    procedure Turn(NewDirection: Integer);
    function GetX: Integer;
    function GetY: Integer;
    function GetDirection: Integer;
    function LeftSide: Integer;
    function RightSide: Integer;
    function BackSide: Integer;
  end;

  TLabyrinth = class
    constructor Create(FileName: String);
  public
    LabMatrix: array of array of Integer;
    Coins: array of TCoords;
    Man: TMovingObject;
    Enemy: array of TMovingObject;
    function IsLeftWay(var Who: TMovingObject): Boolean;
    function IsRightWay(var Who: TMovingObject): Boolean;
    function IsForwardWay(var Who: TMovingObject): Boolean;
    function IsBackWay(var Who: TMovingObject): Boolean;
    function IsEnenyOnWay(var Who: TMovingObject; Direction: Integer): Boolean;
    function IsCashOnWay(var Who: TMovingObject; Direction: Integer): Boolean;
    function IsManOnWay(var Who: TMovingObject; Direction: Integer): Boolean;
    procedure TurnLeft(var Who: TMovingObject);
    procedure TurnRight(var Who: TMovingObject);
    procedure TurnBack(var Who: TMovingObject);
    procedure TurnRandomWay(var Who: TMovingObject);
    function IsManOnCoin: Boolean;
    function IsEnemyOnMan: Boolean;
    function AreThereCoins: Boolean;
    procedure RemoveCoin(index: Integer);
    procedure TakeCoin;
  end;

implementation

  function TCoords.GetX;
  begin
    Result := X;
  end;

  function TCoords.GetY;
  begin
    Result := Y;
  end;

  procedure TCoords.SetX(aX: Integer);
  begin
    X := aX;
  end;

  procedure TCoords.SetY(aY: Integer);
  begin
    Y := aY;
  end;

  constructor TCoords.Create(aX: Integer; aY: Integer);
  begin
    self.SetX(aX);
    self.SetY(aY);
  end;

  constructor TMovingObject.Create(aX: Integer; aY: Integer; aDirection: Integer);
  begin
    Coords := TCoords.Create(aX,aY);
    Direction := aDirection;
  end;

  procedure TMovingObject.Move;
  begin
    case Direction of
      0: Dec(Coords.Y);
      1: Inc(Coords.X);
      2: Inc(Coords.Y);
      3: Dec(Coords.X);
    end;
  end;

  procedure TMovingObject.Turn(NewDirection: Integer);
  begin
    Direction := NewDirection;
  end;

  function TMovingObject.GetX;
  begin
    Result := Coords.GetX;
  end;

  function TMovingObject.GetY;
  begin
    Result := Coords.GetY;
  end;

  function TMovingObject.GetDirection;
  begin
    Result := Direction;
  end;

  function TMovingObject.LeftSide;
  begin
    if Direction = 0 then
      Result := 3
    else
      Result := Direction - 1;
  end;

  function TMovingObject.RightSide;
  begin
    if Direction = 3 then
      Result := 0
    else
      Result := Direction + 1;
  end;

  function TMovingObject.BackSide;
  begin
    case Direction of
      0: Result := 2;
      1: Result := 3;
      2: Result := 0;
      3: Result := 1;
    end;
  end;

  constructor TLabyrinth.Create(FileName: string);
  var
    f: TextFile;
    i,j: Integer;
    m, n, x, y, d: Integer;
  begin
    AssignFile(f,FileName);
    Reset(f);
    //Создаем матрицу лабиринта
    Read(f,m);
    ReadLn(f,n);
    SetLength(LabMatrix,m);
    for j := 0 to m - 1 do
      SetLength(LabMatrix[j],n);
    for i := 0 to m - 1 do
    begin
      for j := 0 to n - 1 do
        Read(f,LabMatrix[i,j]);
      ReadLn(f);
    end;
    //Создаем человечка
    Read(f,x);
    Read(f,y);
    ReadLn(f,d);
    Man := TMovingObject.Create(x,y,d);
    //Создаем врагов
    ReadLn(f,n);
    SetLength(Enemy,n);
    for i := 0 to n - 1 do
    begin
      Read(f,x);
      Read(f,y);
      ReadLn(f,d);
      Enemy[i] := TMovingObject.Create(x,y,d);
    end;
    //Создаем монетки
    ReadLn(f,n);
    SetLength(Coins,n);
    for i := 0 to n - 1 do
    begin
      Read(f,x);
      ReadLn(f,y);
      Coins[i] := TCoords.Create(x,y);
    end;
    CloseFile(f);
  end;

  function TLabyrinth.IsLeftWay(var Who: TMovingObject): Boolean;
  begin
    case Who.Direction of
      0: Result := LabMatrix[Who.GetY, Who.GetX - 1] = 1;
      1: Result := LabMatrix[Who.GetY - 1, Who.GetX] = 1;
      2: Result := LabMatrix[Who.GetY, Who.GetX + 1] = 1;
      3: Result := LabMatrix[Who.GetY + 1, Who.GetX] = 1;
    end;
  end;

  function TLabyrinth.IsRightWay(var Who: TMovingObject): Boolean;
  begin
    case Who.Direction of
      0: Result := LabMatrix[Who.GetY, Who.GetX + 1] = 1;
      1: Result := LabMatrix[Who.GetY + 1, Who.GetX] = 1;
      2: Result := LabMatrix[Who.GetY, Who.GetX - 1] = 1;
      3: Result := LabMatrix[Who.GetY - 1, Who.GetX] = 1;
    end;
  end;

  function TLabyrinth.IsForwardWay(var Who: TMovingObject): Boolean;
  begin
    case Who.Direction of
      0: Result := LabMatrix[Who.GetY - 1, Who.GetX] = 1;
      1: Result := LabMatrix[Who.GetY, Who.GetX + 1] = 1;
      2: Result := LabMatrix[Who.GetY + 1, Who.GetX] = 1;
      3: Result := LabMatrix[Who.GetY, Who.GetX - 1] = 1;
    end;
  end;

  function TLabyrinth.IsBackWay(var Who: TMovingObject): Boolean;
  begin
    case Who.Direction of
      0: Result := LabMatrix[Who.GetY + 1, Who.GetX] = 1;
      1: Result := LabMatrix[Who.GetY, Who.GetX - 1] = 1;
      2: Result := LabMatrix[Who.GetY - 1, Who.GetX] = 1;
      3: Result := LabMatrix[Who.GetY, Who.GetX + 1] = 1;
    end;
  end;

  function TLabyrinth.IsEnenyOnWay(var Who: TMovingObject; Direction: Integer): Boolean;
  var
    i, j, k: Integer;
    check: Boolean;
  begin
    case Direction of
      0:
      begin
        i := Who.GetX;
        j := Who.GetY - 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Enemy) - 1 do
            if ((i = Enemy[k].GetX) and (j = Enemy[k].GetY) and
                (Enemy[k].GetDirection <> Who.GetDirection)) then
              check := true;
          Dec(j);
        end;
        Result := check;
      end;
      1:
       begin
        i := Who.GetX + 1;
        j := Who.GetY;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Enemy) - 1 do
            if ((i = Enemy[k].GetX) and (j = Enemy[k].GetY)) then
              check := true;
          Inc(i);
        end;
        Result := check;
      end;
      2:
       begin
        i := Who.GetX;
        j := Who.GetY + 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Enemy) - 1 do
            if ((i = Enemy[k].GetX) and (j = Enemy[k].GetY)) then
              check := true;
          Inc(j);
        end;
        Result := check;
      end;
      3:
       begin
        i := Who.GetX - 1;
        j := Who.GetY;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Enemy) - 1 do
            if ((i = Enemy[k].GetX) and (j = Enemy[k].GetY)) then
              check := true;
          Dec(i);
        end;
        Result := check;
      end;
    end;
  end;

  function TLabyrinth.IsCashOnWay(var Who: TMovingObject; Direction: Integer): Boolean;
  var
    i, j, k: Integer;
    check: Boolean;
  begin
    case Direction of
      0:
      begin
        i := Who.GetX;
        j := Who.GetY - 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Coins) - 1 do
            if ((i = Coins[k].GetX) and (j = Coins[k].GetY)) then
              check := true;
          Dec(j);
        end;
        Result := check;
      end;
      1:
       begin
        i := Who.GetX + 1;
        j := Who.GetY;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Coins) - 1 do
            if ((i = Coins[k].GetX) and (j = Coins[k].GetY)) then
              check := true;
          Inc(i);
        end;
        Result := check;
      end;
      2:
       begin
        i := Who.GetX;
        j := Who.GetY + 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Coins) - 1 do
            if ((i = Coins[k].GetX) and (j = Coins[k].GetY)) then
              check := true;
          Inc(j);
        end;
        Result := check;
      end;
      3:
       begin
        i := Who.GetX - 1;
        j := Who.GetY;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Coins) - 1 do
            if ((i = Coins[k].GetX) and (j = Coins[k].GetY)) then
              check := true;
          Dec(i);
        end;
        Result := check;
      end;
      4:
      begin
        i := Who.GetX - 1;
        j := Who.GetY - 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Coins) - 1 do
            if ((i = Coins[k].GetX) and (j = Coins[k].GetY)) then
              check := true;
          Dec(i);
        end;
        Result := check;
      end;
      5:
      begin
        i := Who.GetX - 1;
        j := Who.GetY + 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          for k := 0 to Length(Coins) - 1 do
            if ((i = Coins[k].GetX) and (j = Coins[k].GetY)) then
              check := true;
          Dec(i);
        end;
        Result := check;
      end;
    end;
  end;

  function TLabyrinth.IsManOnWay(var Who: TMovingObject; Direction: Integer): Boolean;
   var
    i, j: Integer;
    check: Boolean;
  begin
    case Direction of
      0:
      begin
        i := Who.GetX;
        j := Who.GetY - 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          if ((i = Man.GetX) and (j = Man.GetY)) then
            check := true;
          Dec(j);
        end;
        Result := check;
      end;
      1:
       begin
        i := Who.GetX + 1;
        j := Who.GetY;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          if ((i = Man.GetX) and (j = Man.GetY)) then
            check := true;
          Inc(i);
        end;
        Result := check;
      end;
      2:
       begin
        i := Who.GetX;
        j := Who.GetY + 1;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          if ((i = Man.GetX) and (j = Man.GetY)) then
            check := true;
          Inc(j);
        end;
        Result := check;
      end;
      3:
       begin
        i := Who.GetX - 1;
        j := Who.GetY;
        check := false;
        while (LabMatrix[j,i] = 1) do
        begin
          if ((i = Man.GetX) and (j = Man.GetY)) then
            check := true;
          Dec(i);
        end;
        Result := check;
      end;
    end;
  end;

  procedure TLabyrinth.TurnLeft(var Who: TMovingObject);
  begin
    Who.Turn(Who.LeftSide);
  end;

  procedure TLabyrinth.TurnRight(var Who: TMovingObject);
  begin
    Who.Turn(Who.RightSide);
  end;

  procedure TLabyrinth.TurnBack(var Who: TMovingObject);
  begin
    Who.Turn(Who.BackSide);
  end;

  procedure TLabyrinth.TurnRandomWay(var Who: TMovingObject);
  var
    a: array of Integer;
  begin
    randomize;
    SetLength(a,0);
    if IsLeftWay(Who) then
    begin
      SetLength(a,Length(a)+1);
      a[Length(a)-1] := Who.LeftSide;
    end;
    if IsForwardWay(Who) then
    begin
      SetLength(a,Length(a)+1);
      a[Length(a)-1] := Who.GetDirection;
    end;
    if IsRightWay(Who) then
    begin
      SetLength(a,Length(a)+1);
      a[Length(a)-1] := Who.RightSide;
    end;
    if IsBackWay(Who) then
    begin
      SetLength(a,Length(a)+1);
      a[Length(a)-1] := Who.BackSide;
    end;
    Who.Turn(a[random(Length(a))]);
  end;

  function TLabyrinth.IsManOnCoin;
  var
    i: Integer;
    check: Boolean;
  begin
    check := false;
    for i := 0 to Length(Coins) - 1 do
      if ((Man.GetX = Coins[i].GetX) and (Man.GetY = Coins[i].GetY)) then
        check := true;
    Result := check;
  end;

  function TLabyrinth.IsEnemyOnMan;
   var
    i: Integer;
    check: Boolean;
  begin
    check := false;
    for i := 0 to Length(Enemy) - 1 do
      if ((Man.GetX = Enemy[i].GetX) and (Man.GetY = Enemy[i].GetY)) then
        check := true;
    Result := check;
  end;

  function TLabyrinth.AreThereCoins;
  begin
    Result := (Length(Coins) > 0);
  end;

  procedure TLabyrinth.RemoveCoin(index: Integer);
  var
    i: Integer;
  begin
    for i := index to Length(Coins) - 2 do
      Coins[i] := Coins[i+1];
    SetLength(Coins,Length(Coins)-1);
  end;

  procedure TLabyrinth.TakeCoin;
  var
    i: Integer;
  begin
    for i := 0 to Length(Coins) - 1 do
      if ((Man.GetX = Coins[i].GetX) and (Man.GetY = Coins[i].GetY)) then
        RemoveCoin(i);
  end;

end.
