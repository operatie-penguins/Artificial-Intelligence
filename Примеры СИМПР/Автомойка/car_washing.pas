unit car_washing;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, JPEG, ExtCtrls, Menus, StdCtrls, RotImg;

Const
  MESSAGE_STR = 'car-washing_facility';
  Yes = 1;
  No = 0;

  step = 10;

  put = '\images\';
  putbmp = '\images\bmp\';
  REDCAR_RIGHT = putbmp + 'redright.bmp';
  REDCAR_LEFT = putbmp + 'redleft1.bmp';
  YELLOWCAR_RIGHT = put + 'yeright.jpg';
  YELLOWCAR_LEFT = putbmp + 'yeleft1.bmp';
  BLACKCAR_RIGHT = put + 'blright.jpg';
  BLACKCAR_LEFT = putbmp + 'blleft1.bmp';
  TURQUOISECAR_RIGHT = put + 'turight.jpg';
  TURQUOISECAR_LEFT = put + 'tuleft.jpg';

  GREENSV = putbmp + 'grsv.bmp';
  REDSV = putbmp + 'redsv.bmp';

type
  numLine = (A, B, main);

  PCar = ^TCar;
  TCar = record
            status: (onRoad, beforeW, insideW, afterW, gone);
            moving: (toLeft, toRight, toUp, toDown);
            isDirty: boolean;
            isWash: boolean; // признак того, "помылась" ли машина
            steps: byte;
            road: numLine;
            image: TRotateImage;
            next: PCar;
         end;

  TfrmCarWashing = class(TForm)
    Image1: TImage;
    svLeft: TImage;
    svRight: TImage;
    Image4: TImage;
    MainMenu1: TMainMenu;
    mnuFile: TMenuItem;
    pmnuStop: TMenuItem;
    pmnuExit: TMenuItem;
    N1: TMenuItem;
    pmnuAbout: TMenuItem;
    Button1: TButton;
    Button2: TButton;
    Memo1: TMemo;
    TimerCome: TTimer;
    Label1: TLabel;
    Button3: TButton;
    TimerIntoB: TTimer;
    TimerIntoA: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure WndProc(var Message: TMessage); override;
    procedure pmnuStopClick(Sender: TObject);
    procedure pmnuExitClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure TimerComeTimer(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure TimerIntoATimer(Sender: TObject);
    procedure TimerIntoBTimer(Sender: TObject);
    procedure pmnuAboutClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }

    msgSIMPR: UINT;
    isProgramStop: boolean;

    mCars: PCar; // список машин
    mLengthCar: byte; // длина списка
    mCurrentCar: byte; // номер текущей машины списка
    mCarCurr, mCarEnd: PCar;    // адреса текущего, последнего машин
    carIntoA, carIntoB: PCar;

    lineA, lineB: byte; // кол-во машин в очередях
    signalA, signalB: boolean; // светофор красный или зеленый (true - зеленый)

    procedure addCar(aCar: TCar);
    procedure delCar();
    procedure deleteAllCars();
    procedure nextCar();
    procedure moving();
    procedure movingIntoW();
    procedure movingPass();
    procedure wait();
    procedure signalOnGreen();
    procedure signalOnRed();

    procedure carTurnToRight();
    procedure carTurnToLeft();
  end;

var
  frmCarWashing: TfrmCarWashing;

implementation

uses about;

{$R *.dfm}

{
  Добавление машины в список
}
procedure TfrmCarWashing.addCar(aCar: TCar);
var car: PCar;
begin
  New(car);
  car^ := aCar;
  car^.next := Nil;
  if mCars <> Nil then begin
    mCarEnd.next := car;
    mCarEnd := car;
    inc(mLengthCar);
  end
    else begin
      mCars := car;
      mCarEnd := car;
      mCarCurr := car;
      mCurrentCar := 1;
      mLengthCar := 1;
    end;
end;

{
  Удаляет текущую машину
}
procedure TfrmCarWashing.delCar(); // удалить и перейти к следующему
var APrev, ANext: PCar;
begin
  if mCars <> Nil then
  begin
    if mCars = mCarCurr then // первый
    begin
      mCars := mCars.next;
      dec(mLengthCar);
      mCarCurr.image.Free;
      Dispose(mCarCurr);
      mCarCurr := mCars;
      if mLengthCar = 0 then
      begin
        mCurrentCar := 0;
        mCarEnd := mCars;
      end;
    end
    else // не первый
    begin
      APrev := mCars;
      while APrev.next <> mCarCurr do APrev := APrev.Next;
      if mCarCurr = mCarEnd then // последний
      begin
        dec(mLengthCar);
        mCurrentCar := 1;
        APrev.next := Nil;
        mCarCurr.image.Free;
        Dispose(mCarCurr);
        mCarCurr := mCars;
        mCarEnd := APrev;
      end
      else // в середине
      begin
        ANext := mCarCurr.next;
        APrev.next := ANext;
        mCarCurr.image.Free;
        Dispose(mCarCurr);
        mCarCurr := ANext;
        dec(mLengthCar);
      end;
    end;
  end;
end;

{
  Удаление всех машин из списков
}
procedure TfrmCarWashing.deleteAllCars();
begin
  while (mCars <> nil) do delCar();
end;

procedure TfrmCarWashing.nextCar();
begin
  if mCars <> nil then
  if mCarCurr.next <> nil then
  begin
    mCarCurr := mCarCurr.next;
    inc(mCurrentCar);
  end
  else
  begin
    mCarCurr := mCars;
    mCurrentCar := 1;
  end;
end;

{
  Поворот машины направо
}
procedure TfrmCarWashing.carTurnToRight();
var
  n: integer;
begin
  n := 5;
  Case mCarCurr.moving of
    toLeft: begin
              while mCarCurr.image.Angle > -90 do begin
                      if mCarCurr.image.Angle > -25 then
                        mCarCurr.image.Left := mCarCurr.image.Left - n;
                      mCarCurr.image.Top := mCarCurr.image.Top - round(n/2);
                      mCarCurr.image.Angle := mCarCurr.image.Angle - n;
                      mCarCurr.image.Repaint;
                      sleep(10);
                    end;
              mCarCurr.moving := toUp;
             end;

    toDown: begin
              while mCarCurr.image.Angle > 0 do begin
                      if mCarCurr.image.Angle > 45 then
                        mCarCurr.image.Left := mCarCurr.image.Left - n;
                      mCarCurr.image.Top := mCarCurr.image.Top + round(n/2);
                      mCarCurr.image.Angle := mCarCurr.image.Angle - n;
                      mCarCurr.image.Repaint;
                      sleep(10);
                    end;
              mCarCurr.moving := toLeft;
             end;
  end; {Case}
end;

{
  Поворот машины налево
}
procedure TfrmCarWashing.carTurnToLeft();
var
  n: integer;
begin
  n := 5;
  Case mCarCurr.moving of
    toUp: begin
            while mCarCurr.image.Angle < 0 do begin
                    if mCarCurr.image.Angle < -45 then
                      mCarCurr.image.Left := mCarCurr.image.Left - n;
                    mCarCurr.image.Top := mCarCurr.image.Top - round(n/2);
                    mCarCurr.image.Angle := mCarCurr.image.Angle + n;
                    mCarCurr.image.Repaint;
                    sleep(10);
                  end;
            mCarCurr.moving := toLeft;
          end;

    toLeft: begin;
              while mCarCurr.image.Angle < 90 do begin
                    if mCarCurr.image.Angle < 45 then
                      mCarCurr.image.Left := mCarCurr.image.Left - n;
                    mCarCurr.image.Top := mCarCurr.image.Top + round(n/2);
                    mCarCurr.image.Angle := mCarCurr.image.Angle + n;
                    mCarCurr.image.Repaint;
                    sleep(10);
                  end;
              mCarCurr.moving := toDown;
            end;
  end; {Case}
end;

{
  Переключает светофор на зеленый
}
procedure TfrmCarWashing.signalOnGreen();
begin
  if (mCarCurr <> nil) and
     (mCarCurr.road = A) then
     begin
       signalA := true;
       svLeft.Picture.LoadFromFile(GetCurrentDir + GREENSV);
     end
  else if (mCarCurr <> nil) and
          (mCarCurr.road = B) then
          begin
            signalB := true;
            svRight.Picture.LoadFromFile(GetCurrentDir + GREENSV);
          end;
end;

{
  Переключает светофор на красный
}
procedure TfrmCarWashing.signalOnRed();
begin
  if (mCarCurr <> nil) and
     (mCarCurr.road = A) then
     begin
       signalA := false;
       svLeft.Picture.LoadFromFile(GetCurrentDir + REDSV);
     end
  else if (mCarCurr <> nil) and
          (mCarCurr.road = B) then
          begin
            signalB := false;
            svRight.Picture.LoadFromFile(GetCurrentDir + REDSV);
          end;
end;

{
  возвращает результат - занята ли дорога
}
function isRoadBusy(): boolean;
var
  carC: PCar;
  r: boolean;
begin
  r := false;
  with frmCarWashing do begin
    if (mCars <> nil) then begin
      carC := mCarCurr;

      while carC <> mCarEnd do begin
        if (carC.steps = 30) and
           (carC.image.Left <= 250) then
          begin
            r := true;
            break;
          end;
        carC := carC.next;
      end;

      if (mCarEnd.steps = 30) and
         (carC.image.Left <= 250) then r := true;
    end;
  end;

  isRoadBusy := r;
end;

{
  смотрит есть ли машина впереди
}
function isCarBefore(): boolean;
var
  carC: PCar;
  topPos: integer;
  r: boolean;

begin
  r := false;
  with frmCarWashing do begin
    if (mCarCurr <> nil) and (mLengthCar > 1) then begin
       topPos := mCarCurr.image.Top;

       // смотрим куда движется машинка
       case mCarCurr.moving of
         toUp: begin
                 carC := mCars;
                 while carC <> mCarCurr do begin
                   if (carC.moving = toUp) and
                      (carC.road = mCarCurr.road) and
                      (carC.image.Top + carC.image.Height >= topPos - 10) then
                          r := true;

                   carC := carC.next;
                 end;
               end;

         toDown: begin
                   carC := mCars;
                   while carC <> mCarCurr do begin
                     if (carC.moving = toDown) and
                        (carC.road = mCarCurr.road) and
                        (carC.image.Top - 15 <= topPos + mCarCurr.image.Height) then
                            r := true;

                     carC := carC.next;
                   end;
                 end;
       end; {case}
    end; {if "not nil"}
  end; {with}

  isCarBefore := r;
end;

procedure TfrmCarWashing.FormCreate(Sender: TObject);
begin
  MsgSIMPR:=RegisterWindowMessage(MESSAGE_STR);

  // признак останова программы (для симпра)
  isProgramStop := false;
  lineA := 0;
  lineB := 0;

  // начальная позиция изображений светофоров
  signalA := true;
  svLeft.Picture.LoadFromFile(GetCurrentDir + GREENSV);
  signalB := true;
  svRight.Picture.LoadFromFile(GetCurrentDir + GREENSV);

  carIntoA := nil;
  carIntoB := nil;
  mCars := Nil;
  mLengthCar:=0;
  mCurrentCar := 0;
  mCarCurr := Nil;
  mCarEnd := Nil;
end;

{
  Процедура обработки сообщений.
  Результат заносится в res
}
procedure TfrmCarWashing.WndProc(var Message: TMessage);
var
  res: boolean;
  i: byte;

begin
  // если получили сообщение
  if message.Msg = msgSIMPR then begin
    res := false;

    if message.WParamHi = 0 then begin
      // УСЛОВИЕ
      case message.WParamLo of
        // таблица 1
        1: begin
             case message.LParam of
              1: begin // условие 1
                   res := isProgramStop;
                   if res then memo1.Lines.Add('условие 11  YES')
                      else memo1.Lines.Add('условие 11  NO');
                 end;
             end; {case}
           end;

        // таблица 2
        2: begin
             case message.LParam of
               1: begin // условие 1
                    if mLengthCar > 0 then res := true;
                    if res then memo1.Lines.Add('условие 21  YES')
                      else memo1.Lines.Add('условие 21  NO');
                  end;
               2: begin // условие 2
                    if (mCarCurr <> nil) and
                       (mCarCurr.status = onRoad) then res := true;
                    if res then memo1.Lines.Add('условие 22  YES')
                      else memo1.Lines.Add('условие 22  NO');
                  end;
               3: begin // условие 3
                    if (mCarCurr <> nil) and
                       ((mCarCurr.status = beforeW) or
                        (mCarCurr.status = insideW)) then res := true;
                    if res then memo1.Lines.Add('условие 23  YES')
                      else memo1.Lines.Add('условие 23  NO');
                  end;
               4: begin // условие 4
                    if (mCarCurr <> nil) and
                       (mCarCurr.status = afterW) then res := true;
                    if res then memo1.Lines.Add('условие 24  YES')
                      else memo1.Lines.Add('условие 24  NO');
                  end;
             end; {case}
           end;

        // таблица 3
        3: begin
             case message.LParam of
               1: begin // условие 1
                    if (mCarCurr <> nil) and
                       (mCarCurr.steps <= 10) then res := true;
                    if res then memo1.Lines.Add('условие 31  YES')
                      else memo1.Lines.Add('условие 31  NO');
                  end;
               2: begin // условие 2
                    if (mCarCurr <> nil) and
                       (mCarCurr.steps = 10) then res := true;
                    if res then memo1.Lines.Add('условие 32  YES')
                      else memo1.Lines.Add('условие 32  NO');
                  end;
               3: begin // условие 3
                    if (mCarCurr <> nil) and
                       (mCarCurr.isDirty) then res := true;
                    if res then memo1.Lines.Add('условие 33  YES')
                      else memo1.Lines.Add('условие 33  NO');
                  end;
               4: begin // условие 4
                    if ((lineA + lineB) < 6) then res := true;
                    if res then memo1.Lines.Add('условие 34  YES')
                      else memo1.Lines.Add('условие 34  NO');
                  end;
               5: begin // условие 5
                    if (lineA < lineB) then res := true;
                    if res then memo1.Lines.Add('условие 35  YES')
                      else memo1.Lines.Add('условие 35  NO');
                  end;
             end; {case}
           end;

        // таблица 4
        4: begin
             case message.LParam of
               1: begin // условие 1
                    if (mCarCurr <> nil) and
                       (mCarCurr.status = beforeW) then res := true;
                    if res then memo1.Lines.Add('условие 41  YES')
                      else memo1.Lines.Add('условие 41  NO');
                  end;
               2: begin // условие 2
                    if (mCarCurr <> nil) and
                       (mCarCurr.steps = 20) then res := true;
                    if res then memo1.Lines.Add('условие 42  YES')
                      else memo1.Lines.Add('условие 42  NO');
                  end;
               3: begin // условие 3
                    res := isCarBefore();
                    if res then memo1.Lines.Add('условие 43  YES')
                      else memo1.Lines.Add('условие 43  NO');
                  end;
               4: begin // условие 4
                    if (mCarCurr <> nil) then
                      if ((mCarCurr.road = A) and (not signalA)) or
                         ((mCarCurr.road = B) and (not signalB)) then res := true;
                    if res then memo1.Lines.Add('условие 44  YES')
                      else memo1.Lines.Add('условие 44  NO');
                  end;
               5: begin // условие 5
                    if (mCarCurr <> nil) and
                       (mCarCurr.status = insideW) then res := true;
                    if res then memo1.Lines.Add('условие 45  YES')
                      else memo1.Lines.Add('условие 45  NO');
                  end;
               6: begin // условие 6
                    if (mCarCurr <> nil) and
                       (mCarCurr.isWash) then res := true;
                    if res then memo1.Lines.Add('условие 46  YES')
                      else memo1.Lines.Add('условие 46  NO');
                  end;
             end; {case}
           end;

        // таблица 5
        5: begin
             case message.LParam of
               1: begin // условие 1
                    if (mCarCurr <> nil) and
                       (mCarCurr.steps = 50) then res := true;
                    if res then memo1.Lines.Add('условие 51  YES')
                      else memo1.Lines.Add('условие 51  NO');
                  end;
               2: begin
                    res := isCarBefore();
                    if res then memo1.Lines.Add('условие 52  YES')
                      else memo1.Lines.Add('условие 52  NO');
                  end;
               3: begin // условие 3
                    if not isRoadBusy() then res := true;
                    if res then memo1.Lines.Add('условие 53  YES')
                      else memo1.Lines.Add('условие 53  NO');
                  end;
             end; {case}
           end;
      end; {case}
    end;

    if message.WParamHi = 1 then begin
      // ДЕЙСТВИЕ
      case message.WParamLo of
        // таблица 2
        2: begin
             case message.LParam of
               1: begin
                    wait();
                    memo1.Lines.Add('действие 21 ждать YES');
                  end;
             end; {Case}
           end;

        // таблица 3
        3: begin
             case message.LParam of
               1: begin
                    moving();
                    memo1.Lines.Add('действие 31 ехать YES');
                  end;
               2: begin
                    //movingPass();
                    moving();
                    if mCarCurr <> nil then mCarCurr.steps := 30;
                    memo1.Lines.Add('действие 32 проехать мимо YES');
                  end;
               3: begin
                    for i := 1 to 4 do moving();
                    carTurnToRight();
                    if (mCarCurr <> nil) then begin
                      mCarCurr.status := beforeW;
                      mCarCurr.road := A;
                    end;
                    inc(lineA);
                    memo1.Lines.Add('действие 33 повернуть на А YES');
                  end;
               4: begin
                    carTurnToRight();
                    if (mCarCurr <> nil) then begin
                      mCarCurr.status := beforeW;
                      mCarCurr.road := B;
                    end;
                    inc(lineB);
                    memo1.Lines.Add('действие 34 повернуть на В YES');
                  end;
               5: begin
                    nextCar();
                    memo1.Lines.Add('действие 35 след. по списку машина YES');
                  end;
             end; {case}
           end;

        // таблица 4
        4: begin
             case message.LParam of
               1: begin
                    moving();
                    memo1.Lines.Add('действие 41 ехать YES');
                  end;
               2: begin
                    wait();
                    memo1.Lines.Add('действие 42 ждать YES');
                  end;
               3: begin
                    movingIntoW();
                    memo1.Lines.Add('действие 43 заехать на мойку YES');
                  end;
               4: begin
                    signalOnRed();
                    memo1.Lines.Add('действие 43 перекл. св. на кр. YES');
                  end;
               5: begin
                    if (mCarCurr <> nil) then begin
                      mCarCurr.status := afterW;
                      mCarCurr.isDirty := false;
                      mCarCurr.isWash := true;

                      for i := 0 to 5 do moving();

                      if (mCarCurr.road = A) then dec(lineA)
                        else if (mCarCurr.road = B) then dec(lineB);
                    end;
                    memo1.Lines.Add('действие 43 выехать из мойки YES');
                  end;
               6: begin
                    signalOnGreen();
                    memo1.Lines.Add('действие 43 перекл. св. на зел. YES');
                  end;
               7: begin
                    nextCar();
                    memo1.Lines.Add('действие 43 след. по списку М YES');
                  end;
             end; {case}
           end;

        // таблица 5
        5: begin
             case message.LParam of
               1: begin
                    moving();
                    memo1.Lines.Add('действие 51 ехать YES');
                  end;
               2: begin
                    wait();
                    memo1.Lines.Add('действие 52 ждать YES');
                  end;
               3: begin
                    if (mCarCurr <> nil) then begin
                      if (mCarCurr.road = B) then
                        for i :=1 to 5 do moving()
                      else if (mCarCurr.road = A) then
                        for i := 1 to 8 do moving();
                      carTurnToRight();
                      mCarCurr.status := onRoad;
                    end;
                    memo1.Lines.Add('действие 53 повернуть на гл. дорогу YES');
                  end;
               4: begin
                    nextCar();
                    memo1.Lines.Add('действие 54 след. по списку М YES');
                  end;
             end; {case}
           end;
      end; {case}

      res := true;
    end;

    if res then
      message.Result := Yes
    else
      message.Result := No;
  end
    else
      inherited;
end;

{
  ждать
}
procedure TfrmCarWashing.wait();
begin
  sleep(10);
end;

{
  заехать на мойку
}
procedure TfrmCarWashing.movingIntoW();
begin
  if (mCarCurr <> nil) then begin
    while (mCarCurr.image.Top > 120) do begin
      mCarCurr.image.Top := mCarCurr.image.Top - step;
      mCarCurr.image.Repaint;
      sleep(20);
    end;

    mCarCurr.status := insideW;
    mCarCurr.image.Picture.LoadFromFile(GetCurrentDir + YELLOWCAR_LEFT);

    if (mCarCurr.road = A) then begin
    //  dec(lineA);
      carIntoA := mCarCurr;
      randomize();
      TimerIntoA.Interval := Round(random(8000)) + 4000;
      TimerIntoA.Enabled := true;
    end
      else if (mCarCurr.road = B) then begin
      //  dec(lineB);
        carIntoB := mCarCurr;
        randomize();
        TimerIntoB.Interval := Round(random(8000)) + 4000;
        TimerIntoB.Enabled := true;
      end;
  end;
end;

{
  процедура, реализующая действие "ехать"
}
procedure TfrmCarWashing.moving();
begin
  if (mCarCurr <> nil) then begin
    // в зависимости от направления движения, передвигаем машину
    case mCarCurr.moving of
        toLeft: begin
                  mCarCurr.image.Left := mCarCurr.image.Left - step;

                  if (mCarCurr.image.Left >= 340) and
                     (mCarCurr.image.Left <= 360) and
                     (mCarCurr.image.Top > 200) then mCarCurr.steps := 10
                  else if (mCarCurr.image.Left <= 150) and
                          (mCarCurr.image.Top < 200) and
                          (mCarCurr.road = B) then carTurnToLeft()
                  else if (mCarCurr.image.Left <= 200) and
                          (mCarCurr.image.Top < 200) and
                          (mCarCurr.road = A) then carTurnToLeft()
                  else if (mCarCurr.image.Left <= 0) then delCar();
                end;

        toUp: begin
                mCarCurr.image.Top := mCarCurr.image.Top - step;

                if (mCarCurr.image.Top <= 50) and
                   (mCarCurr.status = afterW) and
                   (mCarCurr.road = B) then carTurnToLeft()
                else if (mCarCurr.image.Top <= 90) and
                        (mCarCurr.status = afterW) and
                        (mCarCurr.road = A) then carTurnToLeft()
                else if (mCarCurr.status = beforeW) and
                        (mCarCurr.image.Top >= 210) and
                        (mCarCurr.image.Top <= 230) then mCarCurr.steps := 20;
              end;

        toDown: begin
                  mCarCurr.image.Top := mCarCurr.image.Top + step;
                  if (mCarCurr.image.Top >= 280) then mCarCurr.steps := 50;
                end;
      end; {Case}

    mCarCurr.image.Repaint;
    sleep(20);
  end;
end;

procedure TfrmCarWashing.movingPass();
begin
  if (mCarCurr <> nil) then begin
    while (mCarCurr.image.Left >= 250) do begin
      mCarCurr.image.Left := mCarCurr.image.Left - step;
      mCarCurr.image.Repaint;
      sleep(20);
    end;

    mCarCurr.steps := 30;
  end;
end;


procedure TfrmCarWashing.pmnuStopClick(Sender: TObject);
begin
  isProgramStop := true;
  TimerCome.Enabled := false;
  deleteAllCars();
end;

procedure TfrmCarWashing.pmnuExitClick(Sender: TObject);
begin
  Close();
end;

procedure TfrmCarWashing.Button1Click(Sender: TObject);
begin
  pmnuStop.Click;
end;

procedure TfrmCarWashing.Button2Click(Sender: TObject);
begin
  pmnuExit.Click;
end;

procedure TfrmCarWashing.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  pmnuStop.Click;
end;

{
  Генериреут прибывающие машины и заносит их в список.
}
procedure TfrmCarWashing.TimerComeTimer(Sender: TObject);
var
  car: TCar;
begin
    TimerCome.Enabled := False;

    if (mCarEnd <> nil) then begin
      if (mCarEnd.image.Left + mCarEnd.image.Height < 410) and
         (mLengthCar < 8) then
         begin
          // создаем машину
          car.status := onRoad;
          car.steps := 0;
          car.road := main;
          randomize();
          if (trunc(random(2)) = 0) then car.isDirty := false
            else car.isDirty := true;
          car.isWash := false; // этот параметр будет true только после выезда из мойки
          car.moving := toLeft;
          car.next := Nil;
          car.image := TRotateImage.Create(self);
          car.image.Parent := frmCarWashing;
          car.image.Left := 460;
          car.image.Top := 375;
          car.image.Angle := 0;

          // делаем разные картинки для машин с учетом загрязненности :)
          if not car.isDirty then begin
            car.image.Picture.LoadFromFile(GetCurrentDir + REDCAR_LEFT);
          end
            else begin
              car.image.Picture.LoadFromFile(GetCurrentDir + BLACKCAR_LEFT);
            end;

          car.image.Transparent := true;
          car.image.AutoSize := true;
          car.image.UniqueSize := false;
          addCar(car);

          car.image.Visible := true;

          randomize;
          TimerCome.Interval := Round(random(2000)) + 1000;
      end;
    end
    else begin
       // создаем машину
          car.status := onRoad;
          car.steps := 0;
          car.road := main;
          randomize();
          if (trunc(random(2)) = 0) then car.isDirty := false
            else car.isDirty := true;
          car.isWash := false; // этот параметр будет true только после выезда из мойки
          car.moving := toLeft;
          car.next := Nil;
          car.image := TRotateImage.Create(self);
          car.image.Parent := frmCarWashing;
          car.image.Left := 460;
          car.image.Top := 375;
          car.image.Angle := 0;

          // делаем разные картинки для машин с учетом загрязненности :)
          if not car.isDirty then begin
            car.image.Picture.LoadFromFile(GetCurrentDir + REDCAR_LEFT);
          end
            else begin
              car.image.Picture.LoadFromFile(GetCurrentDir + BLACKCAR_LEFT);
            end;

          car.image.Transparent := true;
          car.image.AutoSize := true;
          car.image.UniqueSize := false;
          addCar(car);

          car.image.Visible := true;

          randomize;
          TimerCome.Interval := Round(random(2000)) + 1000;
    end;

    TimerCome.Enabled := True;
end;

procedure TfrmCarWashing.Button3Click(Sender: TObject);
begin
  memo1.Lines.SaveToFile('log.txt');
end;

procedure TfrmCarWashing.TimerIntoATimer(Sender: TObject);
begin
  TimerIntoA.Enabled := false;
  carIntoA.isWash := true;
  carIntoA := nil;
end;

procedure TfrmCarWashing.TimerIntoBTimer(Sender: TObject);
begin
  TimerIntoB.Enabled := false;
  carIntoB.isWash := true;
  carIntoB := nil;
end;

procedure TfrmCarWashing.pmnuAboutClick(Sender: TObject);
begin
  Form1.ShowModal();
end;

end.
