using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace SIMPR
{
    class Kernel
    {
//         public BasePeople human;
        public BaseLift lift;
        static public Kernel curent = null;
        System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();

        bool isStarted,             // уже работает?
             needAddHuman = false;  // надо добавить очередного человека

        public bool liftTurn;       // true - ходит лифт, false - люди


        const int addHumanInterval = 7000,
                  startHumanQuantity = 5; // сколько человек создается после начала работы

        public Kernel()
        {
            if (curent != null) throw new Exception("Ядро уже есть.");
//             Debug.WriteLine("Ядро создано.\n");
            timer.Tick += new System.EventHandler(timer_Tick);
            curent = this;
            timer.Interval = addHumanInterval;
            isStarted = false;            
        }

        // СВОЙСТВА

        public bool IsStarted
        {
            get 
            {
                Debug.WriteLine("Программа начала работу?   " + (isStarted ? "ДА" : "НЕТ") + "\n");
                return isStarted; 
            }
        }
        public bool NeedAddHuman
        {
            get 
            {
                Debug.WriteLine("Надо добавить человека?   " + (needAddHuman ? "ДА" : "НЕТ") + "\n");
                return needAddHuman; 
            }
        }
        public bool IsLiftTurn
        {
            get 
            {
                Debug.WriteLine("Ход лифта?   " + (liftTurn ? "ДА" : "НЕТ") + "\n");
                return liftTurn; 
            }
        }
        public bool IsPeopleTurn
        {
            get 
            {
                Debug.WriteLine("Ход людей?   " + (!liftTurn ? "ДА" : "НЕТ") + "\n");
                return !liftTurn; 
            }
        }
        public bool AllHumanHaveGone
        {
            get { return BasePeople.AllHumanHaveGone; }
        }
        private void timer_Tick(object sender, EventArgs e)
        {
            Debug.WriteLine("[Timer]Сработал таймер на добавление людей.\n");
            needAddHuman = true;
        }

        // ДЕЙСТВИЯ

        public void Start()
        {
            Debug.WriteLine("[C]Начало работы программы.\n");
//             isStarted = true;
            liftTurn = true;
            lift = new BaseLift();
            for (int i = 0; i < startHumanQuantity; i++)
            {
                BasePeople.Add();
                System.Threading.Thread.Sleep(12);
            }
            BasePeople.TakeAction();
//             human = BasePeople.GetCurrent();
            timer.Start();
        }
        public void AddHuman()
        {
            BasePeople.Add();
            needAddHuman = false;
        }
        public void NextHuman()
        {
            human.Next();            
        }
        public void GetPeopleTurn()
        {
            liftTurn = false;
            BasePeople.TakeAction();
        }
        public static void PeopleTurn()
        {
            curent.GetPeopleTurn();
        }
        public void GetLiftTurn()
        {
            liftTurn = true;
            BaseLift.TakeAction();
        }
        public static void LiftTurn()
        {
            curent.GetLiftTurn();
        }
        public BasePeople human
        {
            get { return BasePeople.Current; }
        }
    }
}
