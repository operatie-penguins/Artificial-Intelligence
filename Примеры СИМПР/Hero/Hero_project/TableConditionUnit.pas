unit TableConditionUnit;

interface

function cFirstTable ( const CondNumber : integer ) : boolean;
function cSecondTable ( const CondNumber : integer ) : boolean;
function cThirdTable ( const CondNumber : integer ) : boolean;
function cFourthTable ( const CondNumber : integer ) : boolean;
function cFifthTable ( const CondNumber : integer ) : boolean;
function cSixthTable ( const CondNumber : integer ) : boolean;
function cSeventhTable ( const CondNumber : integer ) : boolean;
function cEighthTable ( const CondNumber : integer ) : boolean;
function cNinethTable ( const CondNumber : integer ) : boolean;

implementation

uses MainUnit, ClassUnit, GameUnit;

function cFirstTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1 : Result := MainForm.Start;
    else Result := false;
  end;
end;

function cSecondTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1  : Result := (gaBonus in Game.Hero.GlobalAimes);
    2  : Result := (gaMonster in Game.Hero.GlobalAimes);
    3  : Result := Game.HasBonuses;
    4  : Result := Game.HasMonsters;
    5  : Result := Game.HasLifeBonuses;
    6  : Result := Game.HasAttackBonuses;
    7  : Result := Game.HasDefenceBonuses;
    8  : Result := Game.Hero.IsFewLife;
    9  : Result := Game.Hero.IsFewDefence;
    10 : Result := Game.Hero.IsAimChanging;
    else Result := false;
  end;
end;

function cThirdTable ( const CondNumber : integer ) : boolean;
begin
  Game.ReAimHero;
  case CondNumber of
    1  : Result := Game.Hero.IsRightAim;
    2  : Result := Game.Hero.IsLeftAim;
    3  : Result := Game.Hero.IsUpAim;
    4  : Result := Game.Hero.IsDownAim;
    5  : Result := (Game.Hero.NeedCage is TMonster);
    6  : Result := (Game.Hero.NeedCage is TObstacle);
    7  : Result := (Game.Hero.NeedCage is TBonus);
    8  : if (Game.Hero.NeedCage is TMonster) then
           Result := (Game.DeathByFirstAttack((Game.Hero.NeedCage as TMonster), Game.Hero))
         else
           Result := false;
    9  : Result := (Game.Hero.NeedCage is TExit) and (Game.Hero.Aim = atExit);
    10 : Result := Game.Hero.IsAimReached;
    else Result := false;
  end;
end;

function cFourthTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1  : Result := (Game.Hero.MoveCage[1] is TMonster);
    2  : Result := (Game.Hero.MoveCage[8] is TObstacle);
    3  : Result := (Game.Hero.MoveCage[8] is TMonster);
    4  : Result := (Game.Hero.MoveCage[8] is TBonus);
    5  : Result := (Game.Hero.MoveCage[7] is TObstacle);
    6  : Result := (Game.Hero.MoveCage[7] is TMonster);
    7  : Result := (Game.Hero.MoveCage[7] is TBonus);
    8  : Result := (Game.Hero.MoveCage[6] is TObstacle);
    9  : Result := (Game.Hero.MoveCage[6] is TMonster);
    10 : Result := (Game.Hero.MoveCage[6] is TBonus);
    11 : Result := (Game.Hero.MoveCage[5] is TObstacle);
    12 : Result := (Game.Hero.MoveCage[5] is TMonster);
    13 : Result := (Game.Hero.MoveCage[5] is TBonus);
    14 : Result := (Game.Hero.MoveCage[4] is TObstacle);
    15 : Result := (Game.Hero.MoveCage[4] is TMonster);
    16 : Result := (Game.Hero.MoveCage[4] is TBonus);
    17 : if Game.Hero.MoveCage[8] is TMonster then
           Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[8] as TCreature), Game.Hero)
         else
           if Game.Hero.MoveCage[7] is TMonster then
             Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[7] as TCreature), Game.Hero)
           else
             if Game.Hero.MoveCage[6] is TMonster then
               Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[6] as TCreature), Game.Hero)
             else
               if Game.Hero.MoveCage[5] is TMonster then
                 Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[5] as TCreature), Game.Hero)
               else
                 if Game.Hero.MoveCage[4] is TMonster then
                   Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[4] as TCreature), Game.Hero)
                 else
                   Result := false;
    else Result := false;
  end;
end;

function cFifthTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1  : Result := (Game.Hero.MoveCage[1] is TObstacle);
    2  : Result := (Game.Hero.MoveCage[2] is TObstacle);
    3  : Result := (Game.Hero.MoveCage[2] is TMonster);
    4  : Result := (Game.Hero.MoveCage[2] is TBonus);
    5  : Result := (Game.Hero.MoveCage[3] is TObstacle);
    6  : Result := (Game.Hero.MoveCage[3] is TMonster);
    7  : Result := (Game.Hero.MoveCage[3] is TBonus);
    8  : Result := (Game.Hero.MoveCage[4] is TObstacle);
    9  : Result := (Game.Hero.MoveCage[4] is TMonster);
    10 : Result := (Game.Hero.MoveCage[4] is TBonus);
    11 : Result := (Game.Hero.MoveCage[5] is TObstacle);
    12 : Result := (Game.Hero.MoveCage[5] is TMonster);
    13 : Result := (Game.Hero.MoveCage[5] is TBonus);
    14 : if Game.Hero.MoveCage[2] is TMonster then
           Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[2] as TCreature), Game.Hero)
         else
           if Game.Hero.MoveCage[3] is TMonster then
             Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[3] as TCreature), Game.Hero)
           else
             if Game.Hero.MoveCage[4] is TMonster then
               Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[4] as TCreature), Game.Hero)
             else
               if Game.Hero.MoveCage[5] is TMonster then
                 Result := Game.DeathByFirstAttack((Game.Hero.MoveCage[5] as TCreature), Game.Hero)
               else
                 Result := false;
    else Result := false;
  end;
end;

function cSixthTable ( const CondNumber : integer ) : boolean;
begin
  if Game.CurrentMonster <> nil
    then
      case CondNumber of
        1 : Result := Game.CurrentMonster.IsRightAim;
        2 : Result := Game.CurrentMonster.IsLeftAim;
        3 : Result := Game.CurrentMonster.IsUpAim;
        4 : Result := Game.CurrentMonster.IsDownAim;
        5 : Result := (Game.CurrentMonster.NeedCage is TMonster) or (Game.CurrentMonster.NeedCage is TObstacle);
        6 : Result := (Game.CurrentMonster.NeedCage is THero);
        7 : Result := Game.EofMonster;
        else Result := false;
      end
    else
      case CondNumber of
        7 : Result := true;
        else Result := false;
      end;
end;

function cSeventhTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1 : Result := (Game.CurrentMonster.MoveCage[1] is TMonster) or (Game.CurrentMonster.MoveCage[1] is TObstacle);
    2 : Result := (Game.CurrentMonster.MoveCage[2] is TMonster) or (Game.CurrentMonster.MoveCage[2] is TObstacle);
    3 : Result := (Game.CurrentMonster.MoveCage[3] is TMonster) or (Game.CurrentMonster.MoveCage[3] is TObstacle);
    4 : Result := (Game.CurrentMonster.MoveCage[4] is TMonster) or (Game.CurrentMonster.MoveCage[4] is TObstacle);
    5 : Result := (Game.CurrentMonster.MoveCage[5] is TMonster) or (Game.CurrentMonster.MoveCage[5] is TObstacle);
    6 : Result := (Game.CurrentMonster.MoveCage[6] is TMonster) or (Game.CurrentMonster.MoveCage[6] is TObstacle);
    7 : Result := (Game.CurrentMonster.MoveCage[7] is TMonster) or (Game.CurrentMonster.MoveCage[7] is TObstacle);
    8 : Result := (Game.CurrentMonster.MoveCage[8] is TMonster) or (Game.CurrentMonster.MoveCage[8] is TObstacle);
    9 : Result := (Game.CurrentMonster.MissTurnCount >= 10);
    else Result := false;
  end;
end;

function cEighthTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1 : Result := (Game.Hero.Life <= 0);
    2 : Result := (Game.BattleMonster.Life <= 0);
    3 : Result := Game.BattleTurn.touche;
    4 : Result := Game.BattleTurn.defenceOut;
    5 : Result := Game.BattleTurn.lifeOut;
    6 : Result := Game.BattleTurn.contreattack;
    else Result := false;
  end;
end;

function cNinethTable ( const CondNumber : integer ) : boolean;
begin
  case CondNumber of
    1 : Result := (Game.Hero.Life <= 0);
    2 : Result := (Game.BattleMonster.Life <= 0);
    3 : Result := Game.BattleTurn.touche;
    4 : Result := Game.BattleTurn.defenceOut;
    5 : Result := Game.BattleTurn.lifeOut;
    6 : Result := Game.BattleTurn.contreattack;
    else Result := false;
  end;
end;

end.
