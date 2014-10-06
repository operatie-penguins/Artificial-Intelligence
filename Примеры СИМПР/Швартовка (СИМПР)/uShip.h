//---------------------------------------------------------------------------

#ifndef uShipH
#define uShipH

//---------------------------------------------------------------------------

#include <ExtCtrls.hpp>
#endif

//---------------------------------------------------------------------------

//Класс корабль (наследник от TImage)
class Ship : TImage
{
  private:
    //Состояние действия корабля (0 - движение, 1 - швартовка, 2 - разгрузка,)
    int int_Status;
    //Состояние груза корабля (0 - нет груза, 1 - есть груз)
    int int_Load;
    //Назначение корабля (0 - пассажирский, 1 - грузовой)
    int int_Mission;
    //Направление движения (0 вниз - , 1 - вверх, 2 - вправо, 3 - влево,)
    int int_Direction;
    //Координата X
    int int_X;
    //Координата Y
    int int_Y;
    //Обработчик события таймер
    void __fastcall tmr_TimeTimer(TObject *Sender);
    //Флаг
    bool flgTmr;
    //Флаг хода
    bool flgStep;
    //Флаг дока
    bool flgDock;
  public:
    //Timer
    TTimer* tmr_Time;
    //Конструктор
    Ship(int int_NewStatus, int int_NewLoad, int int_NewMission, int int_NewDirection, int int_NewCordX, int int_NewCordY, TWinControl* AOwner);
    //Функция "Шаг"
    int __ShpStep(int int_StepX, int int_StepY);
    //Функция "Движение по курсу"
    int __ShpMove(int int_StepX, int int_StepY);
    //Функция "Швартовка"
    int __ShpDock(int int_StepX, int int_StepY, int int_DestinationX, int int_DestinationY, int int_DestinationW, int int_DestinationH);
    //Функция "Разгрузка"
    int __ShpUnload(int int_Time);
    //Функция возвращает состояние действия корабля
    int GetStatus();
    //Принудительное изменение состояния действия корабля
    int SetStatus(int int_NewStatus);
    //Функция возвращает состояние груза корабля
    int GetLoad();
    //Принудительное изменение состояния груза корабля
    int SetLoad(int int_NewLoad);
    //Функция возвращает назначение корабля
    int GetMission();
    //Функция возвращает направление движения корабля
    int GetDirection();
    //Принудительное изменение направления движения корабля
    int SetDirection(int int_NewDirection);
    //Принудительное изменение родительского объекта
    int SetOwner(TWinControl* AOwner);
    //Функция возвращает координату X
    int GetX();
    //Функция возвращает координату Y
    int GetY();
    //Функция устанаваливает координату X
    int SetX(int int_NewX);
    //Функция устанаваливает координату Y
    int SetY(int int_NewY);
    //Функция возвращает флаг хода
    bool GetFlgStep();
    //Принудительное изменение флага хода
    bool SetFlgStep(bool NewFlgStep);
    //Функция возвращает флаг дока
    bool GetFlgDock();
    //Принудительное изменение флага хода
    bool SetFlgDock(bool NewFlgDock);
    //Функция возвращает флаг таймера
    bool GetFlgTmr();
    //Принудительное изменение флага таймера
    bool SetFlgTmr(bool NewFlgTmr);
};
