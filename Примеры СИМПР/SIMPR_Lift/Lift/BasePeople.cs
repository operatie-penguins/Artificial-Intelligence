using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Collections;
using System.Drawing;

namespace SIMPR
{
    class BasePeople
    {
        static List<BasePeople> All = new List<BasePeople>();   // Список со всеми людьми
        static List<BasePeople>.Enumerator Numerator;
        static Queue<BasePeople> AddQueue = new Queue<BasePeople>();
        static Queue<BasePeople> GoAwayQueue = new Queue<BasePeople>();
//         static protected BasePeople Current;     // Активный человек
        static BaseLift lift;                       // Ссылка на лифт
        static protected bool allHumanHaveGone = false;      
        static int quantity = 0;                    // Сколько всего людей было создано
        static protected int[] HumansWaitLift = new int[BaseLift.TopFloor + 1];
        public static int[] HumansLeaveLift = new int[BaseLift.TopFloor + 1];

        static public int tmp = 0;

        bool madeCall = false;      // вызвал лифт?
        bool needUp;                // надо ехать вверх?
        bool inCar = false;         // находится в кабине лифта?
        bool hasArrived = false;    // уже приехал?

        protected int endFloor, startFloor, id;

//        static int up, down; 

        #region ===== Constructors =====
        //      ========================
      
        /// <summary>
        /// Для вызова одного конструктора через другой
        /// используется вспомогательная ф-я FillFields(..)
        /// </summary>

        
        public BasePeople(int start, int end)
        {
            FillFields(start, end);
        }
        public BasePeople(bool NeedUp)  // true - вверх, false - вниз, остальное - random
        {
            FillFields(NeedUp);
        }
        public BasePeople()
        {
            FillFields();
            Debug.WriteLine("[Create]" + Name + " создан.\n");

        }

        // -----------------------------------

        private void FillFields(int start, int end) // от и до ...
        {
            if (lift == null) lift = BaseLift.GetLift(); 
            //All.Add(this); 
            AddQueue.Enqueue(this);
            id = ++quantity;
            HumansWaitLift[start]++;            
            startFloor = start;
            endFloor = end;
            needUp = (end - start) > 0;
            //Numerator = All.GetEnumerator();
            //Numerator.MoveNext();
//            if (needUp) up++; else down++;
        }
        private void FillFields(bool NeedUp) // true - вверх, false - вниз, остальное - random
        {
            int start, end;
            Random r = new Random();
            if (NeedUp)
            {
                start = 1;
                end = r.Next(2, BaseLift.TopFloor + 1);
            }
            else
            {
                start = r.Next(2, BaseLift.TopFloor + 1);
                end = 1;
            }
            FillFields(start, end);
        }
        private void FillFields() // полный рэндом. вверх/вниз - 50/50
        {
            Random r = new Random();
            FillFields(Convert.ToBoolean(r.Next(2)));
        }
        //---------------------------------------
        #endregion

        #region ===== Условия таблицы 3 СИМПР =====
        //      ===================================
        
        public bool isMadeCall
        {
            get
            {
                 Debug.WriteLine(Name + " вызвал лифт?   " + (madeCall ? "ДА" : "НЕТ") + "\n");
                return madeCall; 
            }
        }
        public bool NeedUp
        {
            get 
            {
                 Debug.WriteLine(Name + " хочет вверх?   " + (needUp ? "ДА" : "НЕТ") + "\n");
                return needUp;
            }
        }
        public bool InCar
        {
            get 
            {
                Debug.WriteLine(Name + " в кабине?   " + (inCar ? "ДА" : "НЕТ") + "\n");
                return inCar; 
            }
        }
        public bool IsEndFloor
        {
            get 
            {
                Debug.WriteLine("Лифт на нужном этаже?   " + (endFloor == lift.CurFloor ? "ДА" : "НЕТ") + "\n");
                return endFloor == lift.CurFloor; 
            }
        }
        public bool HasArrived
        {
            get 
            {
                Debug.WriteLine(Name + " уже вышел?   " + (hasArrived ? "ДА" : "НЕТ") + "\n");
                return hasArrived; 
            }
        }
        public bool LiftInSameFloor
        {
            get 
            {
                Debug.WriteLine(Name + " и лифт на одном этаже?   " + 
                    ((startFloor == BaseLift.GetLift().CurFloor) ? "ДА" : "НЕТ") + "\n");
                return startFloor == BaseLift.GetLift().CurFloor;

            }
        }
        #endregion

        #region ===== Действия из таблицы 3 СИМПР =====
        //      =======================================
        public void CallLift()
        {
            Debug.WriteLine("[Call]" + Name + " вызвал лифт.\n");
            lift.Call(startFloor, needUp);
            madeCall = true;
        }
        public void Enter()
        {
            Debug.WriteLine("[Enter]" + Name + " вошел в лифт.\n");
            HumansWaitLift[startFloor]--;
            inCar = true;
            ChooseFloor();
            BaseLift.HaveEntered(needUp);
        }
        public void ChooseFloor()
        {
            Debug.WriteLine("[Choose]" + Name + " выбрал " + endFloor + " этаж.\n");
            lift.ChooseFloor(endFloor);
        }
        public void Exit()
        {
            inCar = false;
            hasArrived = true;
            HumansLeaveLift[endFloor]++;
            BaseLift.HaveExit();
            Debug.WriteLine("[Exit]" + Name + " вышел из лифта на " + endFloor + " этаже.\n");
        }
        public void Wait()
        {
            Debug.WriteLine("[A]" + Name + " ждет.\n");
        }
        public void GoAway()
        {
//             tmp++;
            HumansLeaveLift[endFloor]--;
            //All.Remove(Current);
            GoAwayQueue.Enqueue(Current);
            Debug.WriteLine("[GoAway]" + Name + " ушел.\n");
        }
        public BasePeople Next()
        {
            try
            {
                allHumanHaveGone = !Numerator.MoveNext(); 
            }
            catch (System.Exception e)
            {
                allHumanHaveGone = true;
                Debug.WriteLine("[E]" + e.Message + "\n");
                Debug.WriteLine("[E]Новый пассажир пропустил ход.\n");
            }
//             Current = Numerator.Current;
            if (Current == null)
            {
                Debug.WriteLine("[A]Пассажиры закончились.\n");
                Kernel.LiftTurn();
            }
            else 
                Debug.WriteLine("[A]Выбран следущий пассажир: " + Current.Name + "\n");

            return Current;
        }
        #endregion

        #region ===== Действия и условия из таблицы 1 СИМПР =====
        //      =====================
        static public bool AllHumanHaveGone
        {
            get 
            {   //  if (Current == null) return true;
                Debug.WriteLine("Люди есть?   " + (All.Capacity == 0 ? "ДА" : "НЕТ") + "\n");
                if (All.Capacity == 0) return true;
                Debug.WriteLine("Все люди походили?   " + (allHumanHaveGone ? "ДА" : "НЕТ") + "\n");

                return allHumanHaveGone; 
            }
        }
        static public void TakeAction()
        {
            Debug.WriteLine("[C]Люди получат ход.\n");
//             Current = All.First<BasePeople>();
            while (AddQueue.Count != 0)
                All.Add(AddQueue.Dequeue());
            if (allHumanHaveGone)
            {
                //                     while (GoAwayQueue.Count != 0)
                //                         All.Remove(GoAwayQueue.Dequeue);
                foreach (BasePeople bp in GoAwayQueue)
                {
                    All.Remove(bp);
                    tmp++;
                }
                GoAwayQueue.Clear();
            }

            Numerator = All.GetEnumerator();
            Numerator.MoveNext();
        }
        #endregion

        #region ===== Другие методы и свойства =====
        //      ====================================

        // Ф-я Add(..) дублирует функциональность конструкторов
        
        static protected BasePeople Add(int start, int end)
        {
            return new BasePeople(start, end);
        }
        static public BasePeople Add (bool NeedUp)    
        {
            return new BasePeople(NeedUp);
        }
        static public BasePeople Add()
        {
            return new BasePeople();
        }
        static public BasePeople GetCurrent()
        {
            return Current;
        }
        static public BasePeople Current
        {
            get { return Numerator.Current; }
        }
        static public bool Exist
        {
            get 
            {
                 Debug.WriteLine("Люди есть?   " + (All.Capacity != 0 ? "ДА" : "НЕТ") + "\n");
                return (All.Capacity - GoAwayQueue.Count) != 0; 
            }
        }
        public string Name
        {
            get { return "Пассажир №" + id + "(" + startFloor + ";" + endFloor + ")"; }
        }
        public override string ToString()
        {
            return Name + "\n" + "Begin :" + startFloor + "\n" + "End: " + endFloor +
                "\n" + (NeedUp ? "NeedUp" : "NeedDown");
        }
        #endregion

        #region Графика

        static Bitmap man = Properties.Resources.human;
        static public void GetGraphic(Graphics g)
        {
            for (int i = 1; i <= 5; i++)
                for (int j = HumansWaitLift[i]; j > 0; j-- )
                    g.DrawImage(man, 135 - 45 * j, 803 - i * 150);

            for (int i = 1; i <= 5; i++)
                for (int j = HumansLeaveLift[i]; j > 0; j--)
                    g.DrawImage(man, 275 + 45 * j, 803 - i * 150);            
        }                 

        #endregion
    }
}
