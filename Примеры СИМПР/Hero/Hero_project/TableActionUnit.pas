unit TableActionUnit;

interface

procedure aFirstTable ( const CondNumber : integer );
procedure aSecondTable ( const CondNumber : integer );
procedure aThirdTable ( const CondNumber : integer );
procedure aFourthTable ( const CondNumber : integer );
procedure aFifthTable ( const CondNumber : integer );
procedure aSixthTable ( const CondNumber : integer );
procedure aSeventhTable ( const CondNumber : integer );
procedure aEighthTable ( const CondNumber : integer );
procedure aNinethTable ( const CondNumber : integer );

implementation

uses MainUnit, ClassUnit, GameUnit;

procedure DoNothing;
begin
end;

procedure aFirstTable ( const CondNumber : integer );
begin
  case CondNumber of
    1 : DoNothing;
    2 : MainForm.StartGame;
    else DoNothing;
  end;
end;

procedure aSecondTable ( const CondNumber : integer );
begin
  Game.Hero.IsAimChanging := false;
  case CondNumber of
    1 : Game.Hero.FindAim(atLife);
    2 : Game.Hero.FindAim(atAttack);
    3 : Game.Hero.FindAim(atDefence);
    4 : Game.Hero.FindAim(atMonster);
    5 : Game.Hero.FindAim(atExit);
    6 : Game.Hero.FindAim(atBonus, false);
    7 : Game.Hero.FindAim(atMonster, false);
    8 : Game.Hero.FindAim(atCage, false);
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aThirdTable ( const CondNumber : integer );
begin
  case CondNumber of
    1  : begin
           Game.Hero.Move([mdRight, mdUp]);
           Game.ReAimMonsters;
         end;
    2  : begin
           Game.Hero.Move([mdRight, mdDown]);
           Game.ReAimMonsters;
         end;
    3  : begin
           Game.Hero.Move([mdRight]);
           Game.ReAimMonsters;
         end;
    4  : begin
           Game.Hero.Move([mdLeft, mdUp]);
           Game.ReAimMonsters;
         end;
    5  : begin
           Game.Hero.Move([mdLeft, mdDown]);
           Game.ReAimMonsters;
         end;
    6  : begin
           Game.Hero.Move([mdLeft]);
           Game.ReAimMonsters;
         end;
    7  : begin
           Game.Hero.Move([mdUp]);
           Game.ReAimMonsters;
         end;
    8  : begin
           Game.Hero.Move([mdDown]);
           Game.ReAimMonsters;
         end;
    9  : if (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] is TBonus) then
           begin
             if Game.Hero.IsAimReached then
               Game.Hero.IsAimChanging := true;
             (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] as TBonus).ApplyBonus(Game.Hero);
             Game.DeleteBonus(Game.Hero.Coords);
           end;
    10 : if (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] is TMonster) then
           begin
             Game.BattleMonster := (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] as TMonster);
             Game.CurrentMonster := Game.BattleMonster;
             Game.BeginBattle(Game.Hero, Game.BattleMonster);
           end;
    11 : Game.Hero.CreateMoveMatrix([mdRight, mdUp]);
    12 : Game.Hero.CreateMoveMatrix([mdRight, mdDown]);
    13 : Game.Hero.CreateMoveMatrix([mdRight]);
    14 : Game.Hero.CreateMoveMatrix([mdLeft, mdUp]);
    15 : Game.Hero.CreateMoveMatrix([mdLeft, mdDown]);
    16 : Game.Hero.CreateMoveMatrix([mdLeft]);
    17 : Game.Hero.CreateMoveMatrix([mdUp]);
    18 : Game.Hero.CreateMoveMatrix([mdDown]);
    19 : MainForm.EndGame(true, 'Win!');
    20 : Game.Hero.IsAimChanging := true;
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aFourthTable ( const CondNumber : integer );
begin
  case CondNumber of
    1 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[8].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[8].y));
          Game.ReAimMonsters;
        end;
    2 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[7].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[7].y));
          Game.ReAimMonsters;
        end;
    3 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[6].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[6].y));
          Game.ReAimMonsters;
        end;
    4 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[5].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[5].y));
          Game.ReAimMonsters;
        end;
    5 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[4].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[4].y));
          Game.ReAimMonsters;
        end;
    6 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[1].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[1].y));
          Game.ReAimMonsters;
        end;
    7 : if (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] is TMonster) then
          begin
            Game.BattleMonster := (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] as TMonster);
            Game.CurrentMonster := Game.BattleMonster;
            Game.BeginBattle(Game.Hero, Game.BattleMonster);
          end;
    8 : if (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] is TBonus) then
          (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] as TBonus).ApplyBonus(Game.Hero);
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aFifthTable ( const CondNumber : integer );
begin
  case CondNumber of
    1 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[2].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[2].y));
          Game.ReAimMonsters;
        end;
    2 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[3].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[3].y));
          Game.ReAimMonsters;
        end;
    3 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[4].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[4].y));
          Game.ReAimMonsters;
        end;
    4 : begin
          Game.Hero.Move((Game.Hero.Coords.x - Game.Hero.MoveMatrix[5].x), (Game.Hero.Coords.y - Game.Hero.MoveMatrix[5].y));
          Game.ReAimMonsters;
        end;
    5 : Game.Hero.IsAimChanging := true;
    6 : if (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] is TMonster) then
          begin
            Game.BattleMonster := (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] as TMonster);
            Game.CurrentMonster := Game.BattleMonster;
            Game.BeginBattle(Game.Hero, Game.BattleMonster);
          end;
    7 : if (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] is TBonus) then
          (Game.Field[Game.Hero.Coords.x, Game.Hero.Coords.y] as TBonus).ApplyBonus(Game.Hero);
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aSixthTable ( const CondNumber : integer );
begin
  case CondNumber of
    1  : Game.CurrentMonster.Move([mdRight, mdUp]);
    2  : Game.CurrentMonster.Move([mdRight, mdDown]);
    3  : Game.CurrentMonster.Move([mdRight]);
    4  : Game.CurrentMonster.Move([mdLeft, mdUp]);
    5  : Game.CurrentMonster.Move([mdLeft, mdDown]);
    6  : Game.CurrentMonster.Move([mdLeft]);
    7  : Game.CurrentMonster.Move([mdUp]);
    8  : Game.CurrentMonster.Move([mdDown]);
    9  : Game.CurrentMonster.CreateMoveMatrix([mdRight, mdUp]);
    10 : Game.CurrentMonster.CreateMoveMatrix([mdRight, mdDown]);
    11 : Game.CurrentMonster.CreateMoveMatrix([mdRight]);
    12 : Game.CurrentMonster.CreateMoveMatrix([mdLeft, mdUp]);
    13 : Game.CurrentMonster.CreateMoveMatrix([mdLeft, mdDown]);
    14 : Game.CurrentMonster.CreateMoveMatrix([mdLeft]);
    15 : Game.CurrentMonster.CreateMoveMatrix([mdUp]);
    16 : Game.CurrentMonster.CreateMoveMatrix([mdDown]);
    17 : begin
           Game.BattleMonster := Game.CurrentMonster;
           Game.BeginBattle(Game.BattleMonster, Game.Hero);
         end;
    18 : Game.NextMonster;
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aSeventhTable ( const CondNumber : integer );
begin
  case CondNumber of
    1  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[2].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[2].y));
    2  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[3].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[3].y));
    3  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[4].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[4].y));
    4  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[5].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[5].y));
    5  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[6].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[6].y));
    6  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[7].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[7].y));
    7  : Game.CurrentMonster.Move((Game.CurrentMonster.Coords.x - Game.CurrentMonster.MoveMatrix[8].x),
                                  (Game.CurrentMonster.Coords.y - Game.CurrentMonster.MoveMatrix[8].y));
    8  : inc(Game.CurrentMonster.MissTurnCount);
    9  : Game.NextMonster;
    10 : Game.DeathOfMonster;
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aEighthTable ( const CondNumber : integer );
begin
  case CondNumber of
    1 : begin
          Game.EndBattle;
          MainForm.EndGame(false, 'You were killed in a battle!');
        end;
    2 : begin
          Game.EndBattle;
          Game.DeathOfMonster;
          MainForm.WinBattle('You killed a monster!');
        end;
    3 : Game.BattleTurn.A_AttackOut;
    4 : Game.BattleTurn.D_DefenceOut;
    5 : Game.BattleTurn.D_LifeOut;
    6 : Game.BattleTurn.A_LifeOut;
    7 : Game.NextBattleTurn;
    else DoNothing;
  end;
  Game.UpdateField;
end;

procedure aNinethTable ( const CondNumber : integer );
begin
  case CondNumber of
    1 : begin
          Game.EndBattle;
          MainForm.EndGame(false, 'You were killed in a battle!');
        end;
    2 : begin
          Game.EndBattle;
          Game.DeathOfMonster;
          MainForm.WinBattle('You killed a monster!');
        end;
    3 : Game.BattleTurn.A_AttackOut;
    4 : Game.BattleTurn.D_DefenceOut;
    5 : Game.BattleTurn.D_LifeOut;
    6 : Game.BattleTurn.A_LifeOut;
    7 : Game.NextBattleTurn;
    else DoNothing;
  end;
  Game.UpdateField;
end;

end.
