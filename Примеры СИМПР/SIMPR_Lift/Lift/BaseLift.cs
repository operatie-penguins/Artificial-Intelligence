using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Drawing;

namespace SIMPR
{
    enum LiftState
    {
        MovingDown = -1,
        Neutral = 0,
        MovingUp = 1
    } 
    enum DoorState {Close, Open}

    class BaseLift
    {
        static BaseLift curLift;    // ссылка на лифт (для класса People)

        public const int TopFloor = 5; // № верхнего этажа

        protected LiftState State = LiftState.Neutral;
        protected DoorState Doors = DoorState.Close;

        protected int curFloor = 1;      // текущий этаж
        protected int targetFloor = 0;   // этаж, на который надо попасть
                                         // 0 - нет цели
        
        int[] CallCar = new int[TopFloor + 1];  // Массив,  i-ая  ячейка  которого  содержит  true,  
                                      // если  от  какого-либо  из пассажиров  кабины  поступал вызов
                                      // для  движения  на  i-й  этаж,  и  false –  в противном случае  
        
        int[] CallUp = new int[TopFloor + 1];   // Массив,  i-ая  ячейка  которого  содержит  true,  
                                                  // если  с  i-го  этажа  поступал вызов на движение вверх 

        int[] CallDown = new int[TopFloor + 1]; // Массив,  i-ая  ячейка  которого  содержит  true,  
                                                  // если  с  i-го  этажа  поступал вызов на движение вниз 

        #region ===== Constructor =====
        public BaseLift()
        {
            Debug.WriteLine("Лифт создан.\n");
            if (curLift == null) curLift = this;
            else throw new InvalidOperationException("Lift already exist.");
        }
        #endregion


        #region ===== Условия из таблицы 2 SIMPR =====
        //      ====================================

        public bool IsIdle
        {
            get 
            {
                Debug.WriteLine(Name + " стоит?   " + (State == LiftState.Neutral ? "ДА" : "НЕТ") + "\n");
                return State == LiftState.Neutral; 
            }
        }
        public bool IsMovingUp 
        {
            get 
            {                                
                Debug.WriteLine(Name + " едет вверх?   " + (State == LiftState.MovingUp ? "ДА" : "НЕТ") + "\n");
                return State == LiftState.MovingUp; 
            }
        }
        public bool IsMovingDown
        {
            get 
            { 
                Debug.WriteLine(Name + " едет вниз?   " + (State == LiftState.MovingDown ? "ДА" : "НЕТ") + "\n");
                return State == LiftState.MovingDown; 
            }
        }
        public bool IsDoorsOpen
        {
            get 
            { 
                Debug.WriteLine(Name + ". Двери открыты?   " + (Doors == DoorState.Open ? "ДА" : "НЕТ") + "\n");
                return Doors == DoorState.Open; 
            }
        }
        public bool IsGroundFloor
        {
            get 
            { 
                Debug.WriteLine(Name + " на нижнем этаже?   " + (curFloor == 1 ? "ДА" : "НЕТ") + "\n");
                return curFloor == 1; 
            }
        }
        public bool HaveTarget
        {
            get 
            { 
                Debug.WriteLine(Name + " имеет цель?   " + (targetFloor != 0 ? "ДА" : "НЕТ") + "\n");
                return targetFloor != 0; 
            }
        }
        public bool IsTargetBelow
        {
            get 
            {
                bool tmp;
                if (targetFloor == 0) tmp = false;
                else tmp = targetFloor < curFloor;
                Debug.WriteLine(Name + ". Цель внизу?   " + (tmp ? "ДА" : "НЕТ") + "\n");
                return tmp; 
            }
        }
        public bool IsTargetAbove
        {
            get 
            { 
                Debug.WriteLine(Name + ". Цель вверху?   " + (targetFloor > curFloor ? "ДА" : "НЕТ") + "\n");
                return targetFloor > curFloor; 
            }
        }
        public bool IsTargetFloor
        {
            get 
            {
                Debug.WriteLine(Name + ". Цель на этом этаже?   " + (targetFloor == curFloor ? "ДА" : "НЕТ") + "\n");
                return targetFloor == curFloor; 
            }
        }
        #endregion


        #region ===== Действия из таблицы 2 СИМПР =====
        //      =====================================
        public void Stay()
        {
            Debug.WriteLine("[A]Лифт стоит на " + curFloor + " этаже.\n");
            State = LiftState.Neutral;
        }
        public void MoveUp()
        {
            if (curFloor == TopFloor)
                throw new InvalidOperationException("Лифт поехал на чердак");
            Debug.WriteLine("[Move]" + curFloor + " этаж. Лифт едет вверх.\n");
            State = LiftState.MovingUp;
            curFloor++;
        }
        public void MoveDown()
        {
            if (curFloor == 0)
                throw new InvalidOperationException("Лифт поехал в подвал");
            Debug.WriteLine("[Move]" + curFloor + " этаж. Лифт едет вниз.\n");
            State = LiftState.MovingDown;
            curFloor--;
        }
        public void OpenDoors()
        {
            Debug.WriteLine("[Doors]Двери открылись.\n");
            Doors = DoorState.Open;            
        }
        public void CloseDoors()
        {
            Debug.WriteLine("[Doors]Двери закрылись.\n");
            Doors = DoorState.Close;
            //if (State == LiftState.MovingDown) CallDown[curFloor] = false;  // ???
            //if (State == LiftState.MovingUp) CallUp[curFloor] = false;  // ???
//             CallCar[curFloor] = false;
        }
        public int GetTarget()
        {
            switch (State)
            {
                case LiftState.Neutral:
                    //if (CallUp[curFloor])
                    //{
                    //    Debug.WriteLine("[Target]Получена следующая цель: " + curFloor + " этаж (сейчас).  [1]\n"); //1
                    //    return targetFloor = curFloor;
                    //}
                    for (int i = curFloor; i <= TopFloor; i++)
                        if (CallCar[i]!=0 || CallUp[i]!=0)
                        {
                            Debug.WriteLine("[Target]Получена следующая цель: " + i + " этаж.  [2]\n"); //2
                            State = LiftState.MovingUp;
                            return targetFloor = i;
                        }
                    //for (int i = TopFloor; i > 1; i--)
                    //    if (CallDown[i]!=0)
                    //    {
                    //        State = LiftState.MovingUp;
                    //        Debug.WriteLine("[Target]Получена следующая цель: " + i + " этаж.  [3]\n"); //3
                    //        return targetFloor = i;
                    //    }
                    Debug.WriteLine("[Target]У лифта нет цели.  [4]\n"); //4
                    State = LiftState.Neutral;
                    return targetFloor = 0;

                case LiftState.MovingUp:
                    for (int i = curFloor; i <= TopFloor; i++)
                        if (CallCar[i] != 0 || CallUp[i] != 0)
                        {
                            Debug.WriteLine("[Target]Получена следующая цель: " + i + " этаж.  [5]\n"); //5
                            State = LiftState.MovingUp;
                            return targetFloor = i;
                        }
                    for (int i = curFloor; i >= 1; i--)
                        if (CallCar[i] != 0 || CallDown[i] != 0)
                        {
                            State = LiftState.MovingDown;
                            Debug.WriteLine("[Target]Получена следующая цель: " + i + " этаж.  [6]\n"); //6
                            return targetFloor = i;
                        }
                    Debug.WriteLine("[Target]У лифта нет цели.  [7]\n"); //7
                    State = LiftState.MovingDown;
                    return targetFloor = 0;

                case LiftState.MovingDown:
                    for (int i = curFloor; i >= 1; i--)
                        if (CallCar[i] != 0 || CallDown[i] != 0) 
                        {
                            Debug.WriteLine("[Target]Получена следующая цель: " + i + " этаж.  [8]\n"); //8
                            return targetFloor = i;
                        }
                    for (int i = curFloor; i <= TopFloor; i++)
                        if (CallCar[i] != 0 || CallUp[i] != 0)
                        {
                            State = LiftState.MovingUp;
                            Debug.WriteLine("[Target]Получена следующая цель: " + i + " этаж.  [9]\n"); //9
                            return targetFloor = i;
                        }
                    State = LiftState.MovingDown;
                    Debug.WriteLine("[Target]У лифта нет цели.  [10]\n"); //10
                    return targetFloor = 0;
            }            
            throw new InvalidOperationException("Ошибка GetTarget()");
        }
        #endregion


        #region ====== Другие методы и свойства ======
        //      ======================================
        static public BaseLift GetLift()
        {
            return curLift;
        }
        static public void TakeAction()
        {
//             Kernel.curent.liftTurn = false;
            Debug.WriteLine("[C]" + curLift.Name + " получил ход.\n");
        }
        public int CurFloor
        {
            get { return curFloor; }
        }
        public void Call(int num, bool up)
        {
            Debug.WriteLine("[Call]" + Name + " получил вызов: " + num + " этаж, " + (up ? "Вверх." : "Вниз.") + "\n");
            if ( up )
                CallUp[num]++;
            else
                CallDown[num]++;
        }
        public void ChooseFloor (int num)
        {
            Debug.WriteLine("[Choose]" + Name + ". В кабине выбран " + num + " этаж.\n");
            CallCar[num]++;
            GetTarget();
        }
        public string Name
        {
            get { return "Лифт(" + curFloor + ";" + targetFloor + ")"; }
        }
        static public void HaveEntered(bool up)
        {
            if (up) curLift.CallUp[curLift.curFloor]--;
            else curLift.CallDown[curLift.curFloor]--;
            curLift.GetTarget();
        }
        static public void HaveExit()
        {
            curLift.CallCar[curLift.curFloor]--;
            curLift.GetTarget();
        }
        # endregion

        #region Графика

        static Bitmap opendoor = Properties.Resources.opendoor;
        static Bitmap button = Properties.Resources.button;
        static Bitmap lamp = Properties.Resources.lamp2;
        static public void GetGraphic(Graphics g)
        {
            if (curLift.Doors == DoorState.Open)
                g.DrawImage(opendoor, 184, 786 - curLift.curFloor * 150);
            for (int i = 1; i <= 5; i++ )
                if (curLift.CallDown[i] != 0 || curLift.CallUp[i] != 0)
                    g.DrawImage(button, 124, 825 - i * 150);
            g.DrawImage(lamp, 220, 774 - curLift.curFloor * 150);
        }
        #endregion
    }
}
