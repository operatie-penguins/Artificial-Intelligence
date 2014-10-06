using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Timers;
using System.Threading;

namespace Airport
{
    public class Common
    {
        static public int ProbIsHigh = 20;
        static public int ProbIsFat = 40;
        static public int ProbHasMetal = 20;
        static public int ProbHasPassport = 80;
        static public int ProbHasTicket = 80;
        static public int ProbHasVipCard = 10;
        static public int ProbHasLuggage = 80;
        //static public int ProbHasSuitcase = 90;
        static public int ProbHasLargeBag = 60;
        static public int ProbHasDrugs = 20;
        static public int ProbHasBomb = 20;
        static public int ProbHasDiamond = 20;
        static public int ProbHasPistol = 30;

        static public int PassCount = 35;
        static public int PassLeft = PassCount;

        static public string TableMessage = "";
        static public bool Attention = false;

        static public bool EverybodyPassed
        {
            get
            {
                if (PassLeft == 0) return true;
                return false;
            }
        }

        static public Bitmap NewMessage(string message)
        {
            Bitmap bitmap = new Bitmap(800, 356);
            Graphics g = Graphics.FromImage(bitmap);
            g.Clear(Color.White);
            g.FillRectangle(new SolidBrush(Color.Black), 5, 30, 795, 50);
            if (message.Length > 0)
            {
                g.DrawString(message, new Font(FontFamily.GenericSansSerif, 12, FontStyle.Bold), new SolidBrush(Color.Red), 120, 40);
            }
            bitmap.MakeTransparent();
            return bitmap;
        }

        public class ImagesMan
        {
            static public Bitmap[] Enter = new Bitmap[] {
            Properties.Resources.Высокий1,
            Properties.Resources.ВысокийЧемодан1,
            Properties.Resources.ВысокийСумка1,
            Properties.Resources.Толстый1,
            Properties.Resources.ТолстыйЧемодан1,
            Properties.Resources.ТолстыйСумка1,
            Properties.Resources.МужикЧемодан1,
            Properties.Resources.МужикСумка1,
            Properties.Resources.Мужик1};

            static public Bitmap[] NearTerminal = new Bitmap[] {
            Properties.Resources.Высокий4,
            Properties.Resources.ВысокийЧемодан4,
            Properties.Resources.ВысокийСумка4,
            Properties.Resources.Толстый4,
            Properties.Resources.ТолстыйЧемодан4,
            Properties.Resources.ТолстыйСумка4,
            Properties.Resources.МужикЧемодан4,
            Properties.Resources.МужикСумка4,
            Properties.Resources.Мужик4};

            static public Bitmap[] Special = new Bitmap[] {
            Properties.Resources.Высокий5,
            Properties.Resources.Высокий5,
            Properties.Resources.Высокий5,
            Properties.Resources.Толстый4,
            Properties.Resources.Толстый4,
            Properties.Resources.Толстый4,
            Properties.Resources.Мужик4,
            Properties.Resources.Мужик4,
            Properties.Resources.Мужик4};

            static public Bitmap[] GoThrough = new Bitmap[] {
            Properties.Resources.Высокий7,
            Properties.Resources.Высокий7,
            Properties.Resources.Высокий7,
            Properties.Resources.Толстый7,
            Properties.Resources.Толстый7,
            Properties.Resources.Толстый7,
            Properties.Resources.Мужик7,
            Properties.Resources.Мужик7,
            Properties.Resources.Мужик7};

            static public Bitmap[] GoAway = new Bitmap[] {
            Properties.Resources.ВысокийВыход3,
            Properties.Resources.ВысокийВыход3,
            Properties.Resources.ВысокийВыход3,
            Properties.Resources.ТолстыйВыход3,
            Properties.Resources.ТолстыйВыход3,
            Properties.Resources.ТолстыйВыход3,
            Properties.Resources.МужикВыход3,
            Properties.Resources.МужикВыход3,
            Properties.Resources.МужикВыход3};

            static public Bitmap[] Shoot = new Bitmap[] {
            Properties.Resources.ВысокийСтрельба2,
            Properties.Resources.ВысокийСтрельба2,
            Properties.Resources.ВысокийСтрельба2,
            Properties.Resources.ТолстыйСтрельба2,
            Properties.Resources.ТолстыйСтрельба2,
            Properties.Resources.ТолстыйСтрельба2,
            Properties.Resources.МужикСтрельба2,
            Properties.Resources.МужикСтрельба2,
            Properties.Resources.МужикСтрельба2};
        }

        public class ImagesPoliceman
        {
            static public Bitmap Stand = Properties.Resources.Мент1;
            static public Bitmap Come = Properties.Resources.МентЧесть;
        }

        public class ImagesDogSapper
        {
            static public Bitmap Dog = Properties.Resources.Собака4;
            static public Bitmap Sapper = Properties.Resources.Сапер2;
        }

        static public Point BackgroundSize;
    }

    public enum Gender { Male, Female }
    public enum Height { Normal, High }
    public enum Figure { Normal, Fat }
    public enum Items { Metal, Passport, Ticket, VipCard, License }
    public enum Luggage { None, LargeBag, Drugs, Bomb, Diamond, Pistol }
    public enum Action { GoForward, GoBack, Bend, Shoot }

    

    public class Human
    {
        public Bitmap Image;
    }

    public class Device
    {
        public Bitmap Image;
    }

    public class CarryingItems
    {
        public bool Metal;
        public bool Passport;
        public bool Ticket;
        public bool VipCard;
        public bool License;

        public CarryingItems()
        {
            Metal = false;
            Passport = false;
            Ticket = false;
            VipCard = false;
            License = false;
        }

        public void Add(Items Item)
        {
            switch (Item)
            {
                case Items.Metal: { Metal = true; break; }
                case Items.Passport: { Passport = true; break; }
                case Items.Ticket: { Ticket = true; break; }
                case Items.VipCard: { VipCard = true; break; }
                case Items.License: { License = true; break; }
            }
        }
    }

    public class CarryingLuggage
    {
        public bool None;
        public bool LargeBag;
        public bool Drugs;
        public bool Bomb;
        public bool Diamond;
        public bool Pistol;

        public CarryingLuggage()
        {
            None = false;
            LargeBag = false;
            Drugs = false;
            Bomb = false;
            Diamond = false;
            Pistol = false;
        }

        public void Add(Luggage Item)
        {
            if (!None)
            {
                switch (Item)
                {
                    case Luggage.None:
                    {
                        None = true; 
                        LargeBag = false; 
                        Drugs = false; 
                        Bomb = false; 
                        Diamond = false; 
                        Pistol = false; 
                        break;
                    }
                    case Luggage.LargeBag: { LargeBag = true; break; }
                    case Luggage.Drugs: { Drugs = true; break; }
                    case Luggage.Bomb: { Bomb = true; break; }
                    case Luggage.Diamond: { Diamond = true; break; }
                    case Luggage.Pistol: { Pistol = true; break; }
                }
            }
        }
    }
}
