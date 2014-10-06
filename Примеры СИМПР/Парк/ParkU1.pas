unit ParkU1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ImgList, ExtCtrls, StdCtrls;

const
  MESSAGE_STR='MyMessage';
  No=0;
  Yes=1;


type
  TForm1 = class(TForm)
    Image1: TImage;
    ImageList1: TImageList;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    ListBox1: TListBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    procedure FormCreate(Sender: TObject);
    Procedure WNDProc ( var Message: Tmessage); override;
  private
    { Private declarations }
  public
  msgSIMPR: UINT;
    { Public declarations }
  end;

Type TMen = record
     Edge : byte; //сторона квадрата, на которой человек [1,2,3,4]
     PosM : byte; //точка на которой сейчас находится [1..107]
     beg  : boolean; //начал ли игрок
     act  : boolean; //присутствует ли сейчал в парке
     obh  : boolean; //обходит ли кого либо
     PosO : byte; //номер шага обхода
     Prop : boolean; //пропускаем ли кого то
     PosP : byte; // шаг пропуска
     IndE : array [1..4] of byte; //Номер картинки на стороне 1,2,3,4
     SmX  : Integer; // Смещение по Х
     SmY  : Integer; // Смещение по У
     colK : byte; // количество пройденных кругов
     NE   : byte; // начальная сторона
     NP   : byte; // Начальная точка
            end;
Type TPeople = array [1..3] of TMen;
var
  Form1: TForm1;
  mens : TPeople;
  stor : byte; //задание начальной стороны человека
  mp   : byte; //задание случайной позиции человека
  hod  : byte; // кто последний ходил
  met12  : Integer; // Метрики, для сохранения
  Omet12 : Integer; //      расстояния между людьми
  met13  : Integer; // Если они уменьшаются, то люди приближаются
  Omet13 : Integer; // --//--
  met23  : Integer; // --//--
  Omet23 : Integer; // --//--
  flag   : boolean; //просто флаг
  last   : integer; //кто последний ходил
  count  : integer; //сколько раз подряд


implementation

{$R *.dfm}
//процедура задержки
procedure Delay(msecs : Longint);
var FirstTick : longint;
begin FirstTick:=GetTickCount;
repeat Application.ProcessMessages;
until GetTickCount-FirstTick >= msecs;
end;


procedure TForm1.WndProc (var Message : TMessage);
var
res: boolean;

begin // of proc wnd
res:= false;


  If message.Msg=msgSIMPR then
     begin   //2begin
//------------------------------------------------------------------------------
                                 //   Условия
//------------------------------------------------------------------------------
      If message.WParamHi=0 then
       begin

 case  message.WParamLo of               //Выбор таблиц условий

//------------------------------Таблица № 1  Условия---------------------------
    1: begin   // 1

           case message.LParam of
             1:  begin                         //никого нет
                  if ((mens[1].beg=false )and
                      (mens[2].beg=false )and
                      (mens[3].beg=false)) then res := true;

                 end;

             2:  begin                         //есть 1й человек
                 res := mens[1].beg;
                 end;
             3:  begin                         //есть 2й человек
                 res := mens[2].beg;
                 end;
             4:  begin                         //есть 3й человек
                 res := mens[3].beg;
                 end;

           end;   //case Таблица 1 (условия)

       end;   //end таблицы 1 (условия)
//
//-------------(Условия)Таблица №2 - Распределитель парка-----------------------
    2: begin   // 2

           case message.LParam of
               1:  begin                       //никто не ходил
                   if hod=0 then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;


                   end;
               2:  begin                       //ходил 1й
                   if hod=1 then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;

                   end;
               3:  begin                       //ходил 2й
                   if hod=2 then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;

                   end;
               4:  begin                       //ходил 3й
                   if hod=3 then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;

                   end;
               5:  begin                       //в парке есть 1й
                   if mens[1].act=true then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;

                   end;
               6:  begin                       //в парке есть 2й
                   if mens[2].act=true then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;

                   end;
               7:  begin                       //в парке есть 3й
                   if mens[3].act=true then res := true;
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;

                   end;
               8:  begin                       //удалены все
                   if ((mens[1].act=false)and
                       (mens[2].act=false)and
                       (mens[3].act=false))then res := true;

                  ListBox1.Items.Clear;        //необходимо для отладки
                  label1.Caption:=IntToStr(met12);
                  label2.Caption:=IntToStr(met13);
                  label3.Caption:=IntToStr(met23);
                  label4.Caption:=IntToStr(omet12);
                  label5.Caption:=IntToStr(omet13);
                  label6.Caption:=IntToStr(omet23);
                   if count>=30 then begin
                      mens[1].Prop:= false;
                      mens[2].Prop:= false;
                      mens[3].Prop:= false;
                      mens[1].PosP:=0;
                      mens[2].PosP:=0;
                      mens[3].PosP:=0;
                   end;
                   end;


           end; //case Таблица 2 (условия)
       end; // end таблицы 2 (условия)
//
//-------------Таблица №3(Условия) Человек1 ------------------------------------
    3: begin   // 3

           case message.LParam of    //c3
               1:  begin                       //на пути никого нет

               //расстояние между 1 и 2, 1 и 3 большое или 1 и 3 находятся на разных сторонах парка
                   if ((met12>30)and((met13>40)or(mens[1].Edge<>mens[3].Edge) ))then res := true;

               //расстояние между 1 и 2 маленькое, но они расходятся и расстояние между 1 и 3 большое, или 1 и 3 расходятся
                   if  (((met12<30)and(Omet12-met12<0))and
                         ((met13>40)or (Omet13-met13<0))) then res := true;

               //расстояние между 1 и 3 маленькое, но они расходятся и расстояние между 1 и 2 большое, или 1 и 2 расходятся
                   if  (((met13<40)and(Omet13-met13<0))and
                         ((met12>30)or (Omet12-met12<0))) then res := true;
                   ListBox1.Items.Add('ч1 у1 ='+BoolToStr(res)); //для отладки
                   end;

               2:  begin                       //на пути человек 2
                   if  (met12<=30) then res := true;
                   ListBox1.Items.Add('ч1 у2 ='+BoolToStr(res));
                   end;

               3:  begin                       //на пути человек 3
                   if  (((met13<=40)and(mens[1].PosM+mens[3].PosM<107)and
                   (mens[1].Edge=mens[3].Edge))) then res := true;
                   ListBox1.Items.Add('ч1 у3 ='+BoolToStr(res));
                  label1.Caption:=IntToStr(met12);
                  label2.Caption:=IntToStr(met13);
                  label3.Caption:=IntToStr(met23);
                  label4.Caption:=IntToStr(omet12);
                  label5.Caption:=IntToStr(omet13);
                  label6.Caption:=IntToStr(omet23);

                   end;

               4:  begin                       //человек 2 ближе человека 3
                   if met12<met13 then res := true;
                   ListBox1.Items.Add('ч1 у4 ='+BoolToStr(res));
                   end;

               5:  begin                       //человек 3 ближе человека 2
                   if met13<met12 then res := true;
                   ListBox1.Items.Add('ч1 у5 ='+BoolToStr(res));

                   end;

               6:  begin                       //Обходит?
                   res := Mens[1].obh;
                   ListBox1.Items.Add('ч1 у6 ='+BoolToStr(res));

                   end;

               7:  begin                       //Пропускает?
                   res := Mens[1].Prop;
                   ListBox1.Items.Add('ч1 у7 ='+BoolToStr(res));

                   end;


               8:  begin                       //начальная ли точка
                   if ((Mens[1].NE = Mens[1].Edge) and
                       (Mens[1].NP = Mens[1].PosM)) then res := true;
                       ListBox1.Items.Add('ч1 у8 ='+BoolToStr(res));

                   end;

               9:  begin                       //все ли круги?
                   if Mens[1].colK=4 then res := true;
                   ListBox1.Items.Add('ч1 у9 ='+BoolToStr(res));

                   end;

           end; //case Таблица 3 (условия)
       end; // end таблицы 3 (условия)
//
//-------------Таблица №4(Условия) - Человек 2 ---------------------------------
    4: begin   // 4

           case message.LParam of
               1:  begin                       //на пути никого нет
                   if ((met12>30)and(met23>30))then res := true;
                   if  (((met12<30)and(Omet12-met12<0))and
                         ((met23>30)or (Omet23-met23<0))) then res := true;
                   if  (((met23<30)and(Omet23-met23<0))and
                         ((met12>30)or (Omet12-met12<0))) then res := true;
                   ListBox1.Items.Add('ч2 у1 ='+BoolToStr(res));
                   end;
               2:  begin                       //на пути человек 1
                   if  (met12<=30) then res := true;
                   ListBox1.Items.Add('ч2 у2 ='+BoolToStr(res));
                   end;
               3:  begin                       //на пути человек 3
                   if  (met23<=30) then res := true;
                   ListBox1.Items.Add('ч2 у3 ='+BoolToStr(res));
                   end;
               4:  begin                       //все ли шаги?
                     case mens[2].NE of
                       1: begin
                          if Image3.Top<33 then res:= true;

                          end;
                       2: begin
                          if Image3.Top>247 then res := true;
                          end;
                       3: begin
                          if Image3.Left<90 then res := true;

                          end;
                       4: begin
                          if Image3.Left>520 then res := true;
                          end;
                     end;
                 ListBox1.Items.Add('ч2 у4 ='+BoolToStr(res));
                   end;
           end; //case Таблица 4 (условия)
       end; // end таблицы 4 (условия)
//
//-------------Таблица №5(Условия) - Человек 3----------------------------------
    5: begin   // 5

           case message.LParam of
               1:  begin                       //на пути никого нет
                   if (((met13>40)or(mens[1].Edge<>mens[3].Edge) )and(met23>30))then res := true;
                   if  (((met13<40)and(Omet13-met13<0))and
                         ((met23>30)or (Omet23-met23<0))) then res := true;
                   if  (((met13<40)and(Omet13-met13<0))and
                         ((met23>30)or (Omet23-met23<0))) then res := true;
                   ListBox1.Items.Add('ч3 у1 ='+BoolToStr(res));
                   end;
               2:  begin                       //на пути человек 1
                   if  ((met13<=40)and(mens[1].Edge=mens[3].Edge)) then res := true;
                   ListBox1.Items.Add('ч3 у2 ='+BoolToStr(res));
                  label1.Caption:=IntToStr(met12);
                  label2.Caption:=IntToStr(met13);
                  label3.Caption:=IntToStr(met23);
                  label4.Caption:=IntToStr(omet12);
                  label5.Caption:=IntToStr(omet13);
                  label6.Caption:=IntToStr(omet23);
                   end;
               3:  begin                       //на пути человек 2
                   if  (met23<=30) then res := true;
                   ListBox1.Items.Add('ч3 у3 ='+BoolToStr(res));
                   end;
               4:  begin                       //начальная ли точка
                   if ((Mens[3].NE = Mens[3].Edge) and
                       (Mens[3].NP = Mens[3].PosM)) then res := true;
                   ListBox1.Items.Add('ч3 у4 ='+BoolToStr(res));
                   end;
               5:  begin                        //все ли круги
                   if Mens[3].colK=4 then res := true;
                   ListBox1.Items.Add('ч3 у5 ='+BoolToStr(res));
                   end;
               6:  begin                        //человек 2 пропускает
                   res := mens[2].Prop;
                   end;
               7:  begin                        //пропускаем?
                   res := mens[3].Prop;
                   end;
            end; //case Таблица 5 (условия)
       end; // end таблицы 5 (условия)
//------------------------------------------------------------------------------
end;  // case всех таблиц
end; //If message.WParamHi=0
//------------------------------------------------------------------------------
                                 //   Действия
//------------------------------------------------------------------------------
 if message.WParamHi=1 then
   Begin
       case message.WParamLo of  // case na tabl
//----------------------Таблица 1 действия--------------------------------------
        1:  begin      //1
              case message.LParam of
                1: begin                //поставить 1го
                   mens[1].beg:=true;   //1й начал
                   randomize;
                   stor := random(4)+1; //выбираем сторону парка
                   mens[1].Edge:= stor; //запоминаем текущую сторону
                   mp := random(100)+3; //выбираем точку стороны
                   mens[1].act:= true;  //1й активен
                   mens[1].PosM := mp;  //запоминаем текущую точку
                   mens[1].NE := stor;  //запоминаем начальную сторону
                   mens[1].NP := mp;    //запоминаем точку старта
                     case stor of            //*
                       1:begin                             //в зависимости от стороны ставим картинку на место
                          Image2.Top:= 247 - 107 + mp;
                          Image2.Left:=312 + 214- mp*2;
                          mens[1].SmX:=-2;                 //смещение шага
                          mens[1].SmY:=1;
                         end;
                       2:begin
                          Image2.Top:= 247-214+mp;
                          Image2.Left:= 312+mp*2;
                          mens[1].SmX:=2;                  //смещение шага
                          mens[1].SmY:=1;
                         end;
                       3:begin
                          Image2.Top:= 247-107-mp;
                          Image2.Left:= 312-214+mp*2;
                          mens[1].SmX:=2;                  //смещение шага
                          mens[1].SmY:=-1;
                         end;
                       4:begin
                          Image2.Top:= 247-107+mp;
                          Image2.Left:= 312-214+mp*2;
                          mens[1].SmX:=-2;                 //смещение шага
                          mens[1].SmY:=-1;
                          mens[1].PosM := 107 - mp;
                         end;
                     end;

                   ImageList1.GetBitmap(mens[1].inde[mens[1].Edge] ,Image2.Picture.Bitmap);
                   end;              //*
                2: begin                  //поставить 2го
                   mens[2].beg:=true;     //2й начал
                   randomize;
                   stor := random(4)+1;   //выбираем сторону парка
                   mens[2].Edge:= stor;   //запоминаем текущую сторону
                   mens[2].act:= true;    //2й активен
                   mens[2].PosM := 1;     //текущая точка
                   mens[2].NE:= stor;     //запоминаем начальную сторону
                   mens[2].NP := 1;       //начальная точка
                     case stor of            //*
                       1:begin                   //в зависимости от стороны ставим картинку на место
                          Image3.Top:= 247;
                          Image3.Left:= 312;
                          mens[2].SmX:=0;        //смещение шага
                          mens[2].SmY:=-1;
                         end;
                       2:begin
                          Image3.Top:= 247-214;
                          Image3.Left:= 312;
                          mens[2].SmX:=0;        //смещение шага
                          mens[2].SmY:=1;
                         end;
                       3:begin
                          Image3.Top:= 247-107;
                          Image3.Left:= 312+214;
                          mens[2].SmX:=-2;       //смещение шага
                          mens[2].SmY:=0;
                         end;
                       4:begin
                          Image3.Top:= 247-107;
                          Image3.Left:= 312-214;
                          mens[2].SmX:=2;        //смещение шага
                          mens[2].SmY:=0;
                         end;
                     end;

                   ImageList1.GetBitmap(mens[2].inde[mens[2].Edge] ,Image3.Picture.Bitmap);
                   end;
                3: begin                                 //поставить 3го
                   mens[3].beg:=true;                    //3й начал
                   randomize;
                   stor := random(4)+1;                  //выбираем сторону парка
                   mens[3].Edge:= stor;                  //запоминаем текущую сторону
                   mp := random(100)+3;                  //выбираем точку стороны
                   if mens[1].Edge=mens[3].Edge then begin     //перезадаем начальные точки
                   while (abs(mens[1].PosP-mp)<41) do
                         mp := random(100)+3;
                                                     end;
                   mens[3].act:= true;                   //3й активен
                   mens[3].PosM := mp;                   //запоминаем текущую точку
                   mens[3].NE:= stor;                    //запоминаем начальную сторону
                   mens[3].NP := mp;                     //запоминаем точку старта
                     case stor of            //*
                       1:begin                         //в зависимости от стороны ставим картинку на место
                          Image4.Top:= 247-mp;
                          Image4.Left:= 312+mp*2;
                          mens[3].SmX:=2;              //смещение шага
                          mens[3].SmY:=-1;
                         end;
                       2:begin
                          Image4.Top:= 247-107-mp;
                          Image4.Left:= 312+214-mp*2;
                          mens[3].SmX:=-2;             //смещение шага
                          mens[3].SmY:=-1;
                         end;
                       3:begin
                          Image4.Top:= 247-214+mp;
                          Image4.Left:= 312-mp*2;
                          mens[3].SmX:=-2;             //смещение шага
                          mens[3].SmY:=1;
                         end;
                       4:begin
                          Image4.Top:= 247-107+mp;
                          Image4.Left:= 312-214+mp*2;
                          mens[3].SmX:=2;              //смещение шага
                          mens[3].SmY:=1;
                         end;
                     end;

                   ImageList1.GetBitmap(mens[3].inde[mens[3].Edge] ,Image4.Picture.Bitmap);
                   end;
                4: begin                               //начать движение
          showMessage('Начинаем движение');
          met12:=trunc( sqrt(sqr(Image2.Top- Image3.Top)+sqr(Image2.Left-Image3.Left))); //считаем метрики
          met13:=trunc( sqrt(sqr(Image2.Top- Image4.Top)+sqr(Image2.Left-Image4.Left)));
          met23:=trunc( sqrt(sqr(Image3.Top- Image4.Top)+sqr(Image3.Left-Image4.Left)));
          Omet12:= met12;                             //текущие метрики
          Omet13:= met13;
          Omet23:= met23;
                   end;
              end;  //case таблицы 1
            end;  // конец таблицы 1
//----------------------Таблица 2 Действия---------------------------------------
        2:  begin
              case message.LParam of
                1: begin                       //сходить 1м
                   hod :=1;                    //ход-1му
                   if last=1 then inc(count) else begin  //проверяем кто последний ходил(если 1й-пишем сколько раз подряд)
                   last :=1;                   //последний ходил 1й
                   count :=0                   //0 раз подряд
                                                  end;

                   end;

                2: begin                       //сходить 2м
                   hod :=2;                    //ход-2му
                   if last=2 then inc(count) else begin  //проверяем кто последний ходил(если 2й-пишем сколько раз подряд)
                   last :=2;                   //последний ходил 2й
                   count :=0                   //0 раз подряд
                                                  end;

                   end;

                3: begin                       //сходить 3м
                   hod :=3;                    //ход-3му
                   if last=3 then inc(count) else begin  //проверяем кто последний ходил(если 3й-пишем сколько раз подряд)
                   last :=3;                   //последний ходил 3й
                   count :=0                   //0 раз подряд
                                                  end;

                   end;

                4: begin                       //завершить
                   ShowMessage('Прогулка окончена!');
                   end;

              end;  //case таблицы 2
            end;  // конец таблицы 2
//----------------------Действия Человек 1---------------------------------------
        3:  begin      //3
              case message.LParam of
                1: begin                     //сделать шаг
                   if last=1 then inc(count) else begin   //если до этого тоже ходил 1й
                   last :=1;                              //передаем ход 1му
                   count :=0
                                                  end;
                   //если 1й никого не обходит и не пропускает, то
                   if ((Mens[1].obh=false) and (Mens[1].Prop=false) ) then begin

                   //если точка, на которой сейчас находится не равна 107
                   if Mens[1].PosM<>107 then begin
                      //то прибавляем шаг
                      inc(Mens[1].PosM);
                      //смещаем картинку
                      Image2.Top:= Image2.Top+Mens[1].SmY;
                      Image2.Left := Image2.Left+Mens[1].SmX;
                                             end
                   else begin           //переставляем на следующую сторону
                      flag := true;
                      if ((Mens[1].Edge=1)and flag )then begin
                      Mens[1].Edge:=4;
                      flag:= false;
                                                         end;
                      if ((Mens[1].Edge=2) and flag ) then begin
                      Mens[1].Edge:=1;
                      flag:=false;
                      end;
                      if ((Mens[1].Edge=3) and flag ) then begin
                      Mens[1].Edge:=2;
                      flag := false;
                      end;
                      if ((Mens[1].Edge=4)and flag ) then begin
                      Mens[1].Edge:=3;
                      flag := false;
                      end;
                      Mens[1].PosM:=1;
                     case Mens[1].Edge of            //в зависимости от стороны задаем смещения
                       1:begin
                          mens[1].SmX:=-2;
                          mens[1].SmY:=1;
                         end;
                       2:begin
                          mens[1].SmX:=2;
                          mens[1].SmY:=1;
                         end;
                       3:begin
                          mens[1].SmX:=2;
                          mens[1].SmY:=-1;
                         end;
                       4:begin
                          mens[1].SmX:=-2;
                          mens[1].SmY:=-1;
                         end;
                     end;


                        end;
                image2.Canvas.FillRect(Image2.ClientRect);
                ImageList1.GetBitmap(mens[1].inde[mens[1].Edge] ,Image2.Picture.Bitmap);
                delay(70);
                                                             end;// не обходим не пропускаем


          Omet12:= met12;                     //переписываем текущие метрики
          Omet13:= met13;
          Omet23:= met23;
          met12:=trunc( sqrt(sqr(Image2.Top- Image3.Top)+sqr(Image2.Left-Image3.Left)));
          met13:=trunc( sqrt(sqr(Image2.Top- Image4.Top)+sqr(Image2.Left-Image4.Left)));
          met23:=trunc( sqrt(sqr(Image3.Top- Image4.Top)+sqr(Image3.Left-Image4.Left)));
                   end;

                2: begin                      //обойти
                  if Mens[1].obh = false then begin  //если еще не обходит
                    mens[1].obh:= true;
                    mens[1].PosO:=40;                //пропускаем 40 ходов
                       case mens[1].Edge of
                         1: begin                    //отодвгаем картинку на время пропуска
                            Image2.Left:=Image2.Left+25;
                            end;
                         2: begin
                            Image2.Left:=Image2.Left+25;
                            end;
                         3: begin
                            Image2.Left:=Image2.Left-25;
                            end;
                         4: begin
                            Image2.Left:=Image2.Left-25;
                            end;
                       end;
                                              end
                  else begin                  //если уже обходит
                      if mens[1].PosO>0 then mens[1].PosO := mens[1].PosO-1; //уменьшаем оставшееся число пропуска
                      if mens[1].PosO=0 then begin   //если только начал обходить
                       case mens[1].Edge of
                         1: begin                    //сдвигаем картинку
                            Image2.Left:=Image2.Left-25;
                            end;
                         2: begin
                            Image2.Left:=Image2.Left-25;
                            end;
                         3: begin
                            Image2.Left:=Image2.Left+25;
                            end;
                         4: begin
                            Image2.Left:=Image2.Left+25;
                            end;
                       end;
                       mens[1].obh:=false;           //не обходит
                                             end;


                       end;
                    delay(70);                       //ставим задержку
                   end;

                3: begin                             //пропустить
                  if Mens[1].Prop=false then begin   //если еще не пропускает
                     Mens[1].Prop := true;           //начать пропускать
                     Mens[1].PosP := 20;             //шаг пропуска
                                             end
                            else begin               //если уже пропускаем
                     if Mens[1].PosP>0 then Mens[1].PosP := Mens[1].PosP-1 //уменьшаем оставшееся число пропуска
                     else begin
                       Mens[1].Prop:= false;
                       Mens[1].PosP:= 0;
                          end;

                                 end;
                   delay(40);                        //задержка
                   end;

                4: begin                             //прибавить круг
                   inc(mens[1].colK);
                   end;

                5: begin                             //удалить
                   mens[1].act := false;             //1й не активен
                   image2.Visible:=false;
                   image2.Top:=600;
                   image2.left:=600;
                   ShowMessage('первый закончил');
                   end;

              end;  //case таблицы 3
            end;  // конец таблицы 3
//---------------------Действия человек 2---------------------------------------
        4:  begin      //4
              case message.LParam of
                1: begin                             //сделать шаг
                   if last=2 then inc(count) else begin    //если до этого тоже ходил 2й
                   last :=2;                               //передаем ход 2му
                   count :=0
                                                  end;
                   //если никого не пропускает
                   if  (Mens[2].Prop=false) then begin
                      //смещаем картинку
                      Image3.Top:= Image3.Top+Mens[2].SmY;
                      Image3.Left := Image3.Left+Mens[2].SmX;
                      delay(40);               //задержка

                                                 end;// не обходим не пропускаем

          Omet12:= met12;          //переписываем метрики
          Omet13:= met13;
          Omet23:= met23;
          met12:=trunc( sqrt(sqr(Image2.Top- Image3.Top)+sqr(Image2.Left-Image3.Left)));
          met13:=trunc( sqrt(sqr(Image2.Top- Image4.Top)+sqr(Image2.Left-Image4.Left)));
          met23:=trunc( sqrt(sqr(Image3.Top- Image4.Top)+sqr(Image3.Left-Image4.Left)));

                   end;

                2: begin                   //пропустить
                  if Mens[2].Prop=false then begin    //если еще не пропускает
                     Mens[2].Prop := true;            //начал пропускать
                     Mens[2].PosP := 20;              //шаг пропуска
                                             end
                            else begin                //если уже пропускает
                     if Mens[2].Posp>0 then Mens[2].Posp := Mens[2].Posp-1   //уменьшаем оставшееся число пропуска
                     else begin
                       Mens[2].Prop:= false;
                       Mens[2].Posp:= 0;
                          end;

                                 end;
                   delay(40);                         //задержка
                   end;

                3: begin                              //удалить
                   mens[2].act := false;
                   image3.Visible:=false;
                   ShowMessage('Второй закончил');
                   image3.Top:=600;
                   image3.left:=600;
                   end;

              end;  //case таблицы 4
            end;  // конец таблицы 4
//---------------------Действия человек 3---------------------------------------
        5:  begin      //5
              case message.LParam of
                1: begin                              //сделать шаг
                   if last=3 then inc(count) else begin   //если до этого тоже ходил 3й
                   last :=3;                              //передаем ход 3му
                   count :=0
                                                  end;

                   //если никого не пропускает
                   if (Mens[3].Prop=false) then begin

                   //если точка, на которой сейчас находится не равна 107
                   if Mens[3].PosM<>107 then begin
                      //то прибавляем шаг
                      inc(Mens[3].PosM);
                      //смещаем картинку
                      Image4.Top:= Image4.Top+Mens[3].SmY;
                      Image4.Left := Image4.Left+Mens[3].SmX;
                                             end
                   else begin             //переставляем на следующую сторону
                      flag := true;
                      if ((Mens[3].Edge=1)and flag )then begin
                      Mens[3].Edge:=2;
                      flag:= false;
                                                         end;
                      if ((Mens[3].Edge=2) and flag ) then begin
                      Mens[3].Edge:=3;
                      flag:=false;
                      end;
                      if ((Mens[3].Edge=3) and flag ) then begin
                      Mens[3].Edge:=4;
                      flag := false;
                      end;
                      if ((Mens[3].Edge=4)and flag ) then begin
                      Mens[3].Edge:=1;
                      flag := false;
                      end;
                      Mens[3].PosM:=1;
                     case Mens[3].Edge of            //в зависимости от стороны задаем смещения
                       1:begin
                          mens[3].SmX:=2;
                          mens[3].SmY:=-1;
                         end;
                       2:begin
                          mens[3].SmX:=-2;
                          mens[3].SmY:=-1;
                         end;
                       3:begin
                          mens[3].SmX:=-2;
                          mens[3].SmY:=1;
                         end;
                       4:begin
                          mens[3].SmX:=2;
                          mens[3].SmY:=1;
                         end;
                     end;


                        end;
                image4.Canvas.FillRect(Image4.ClientRect);
                ImageList1.GetBitmap(mens[3].inde[mens[3].Edge] ,Image4.Picture.Bitmap);
                delay(40);                        //задержка

                                                             end;// не обходим не пропускаем


          Omet12:= met12;                //переписываем метрики
          Omet13:= met13;
          Omet23:= met23;
          met12:=trunc( sqrt(sqr(Image2.Top- Image3.Top)+sqr(Image2.Left-Image3.Left)));
          met13:=trunc( sqrt(sqr(Image2.Top- Image4.Top)+sqr(Image2.Left-Image4.Left)));
          met23:=trunc( sqrt(sqr(Image3.Top- Image4.Top)+sqr(Image3.Left-Image4.Left)));

                   end;
                2: begin                 //пропустить
                  if Mens[3].Prop=false then begin     //если еще не пропускает
                     Mens[3].Prop := true;             //начал пропускать
                     Mens[3].PosP := 20;               //шаг пропуска
                                             end
                            else begin                             //если уже пропускает
                     if Mens[3].Posp>0 then Mens[3].Posp := Mens[3].Posp-1   //уменьшаем оставшееся число пропуска
                     else begin
                       Mens[3].Prop:= false;
                       Mens[3].Posp:= 0;
                          end;

                                 end;
                   delay(40);                          //задержка
                   end;

                3: begin                               //прибавить круг
                   inc(mens[3].colK);
                   end;

                4: begin                               //удалить
                   mens[3].act := false;
                   image4.Visible:=false;
                   image4.Top:=600;
                   image4.left:=600;
                   ShowMessage('Третий закончил');
                   mens[1].Prop:=false;
                   mens[1].PosP:=0;
                   mens[2].Prop:=false;
                   mens[2].PosP:=0;

                   end;
                5: begin                               //не пропускать
                   mens[3].Prop:= false;
                   mens[3].PosP:=0;
                   end;

              end;  //case таблицы 5
            end;  // конец таблицы 5

//----------------------------------------------------

       end; // закончили
res := true;
   end;     //            действия

if res then message.result:=1 else
message.result:=0;

end // end of case  na DEISTVIYA
else inherited  WndProc(Message);
end; // end // of proc wnd
procedure TForm1.FormCreate(Sender: TObject);
var i : Integer;
begin
MsgSIMPR:= RegisterWindowMessage(MESSAGE_STR);
  for I := 1 to 3 do begin   //обнуляем флаги игроков
  mens[i].beg := false;
  mens[i].act := false;
  mens[i].obh := false;
  mens[i].Prop:= false;
                     end;
mens[1].IndE[1]:=1;           //номера картинок
mens[1].IndE[2]:=3;
mens[1].IndE[3]:=0;
mens[1].IndE[4]:=2;
mens[2].IndE[1]:=7;
mens[2].IndE[2]:=6;
mens[2].IndE[3]:=4;
mens[2].IndE[4]:=5;
mens[3].IndE[1]:=11;
mens[3].IndE[2]:=9;
mens[3].IndE[3]:=10;
mens[3].IndE[4]:=8;

hod := 0;
last := 0;
count := 0;
end;

end.
