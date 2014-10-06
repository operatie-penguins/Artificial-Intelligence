using System;
using System.Collections.Generic;
using System.Text;

namespace WindowsApplication9
{
    public class customer
    {
        public finex FINEX;
        public season SEASON;
      //  public money MONEY;
        public havemoney HAVEMONEY;
        public koor KOORDINATE = new koor();
        public int MON;
        public int x;
        public int y;

        public customer()
        {
            x = KOORDINATE.KOOR[0].X;
            y = KOORDINATE.KOOR[0].Y;
            Random RANDOM = new Random();
            int tmp;
            tmp = RANDOM.Next(2);
            if (tmp == 0)
            {
                FINEX = finex.fine;
            }
            else
            {
                FINEX = finex.exellent;
            }
            tmp = RANDOM.Next(4);
            if (tmp == 0)
            {
                SEASON = season.winter;
            }
            else if (tmp == 1)
            {
                SEASON = season.spring;
            }
            else if (tmp == 2)
            {
                SEASON = season.summer;
            }
            else if (tmp == 3)
            {
                SEASON = season.autumn;
            }
            tmp = RANDOM.Next(7);
            if (tmp == 0)
            {
                //MONEY = money.thousand1;
                MON = 1000;
            }
            else if (tmp == 1)
            {
                //MONEY = money.thousand2;
                MON = 2000;
            }
            else if (tmp == 2)
            {
                MON = 3000;
                //MONEY = money.thousand3;
            }
            else if (tmp == 3)
            {
                MON = 4000;
                //MONEY = money.thousand4;
            }
            else if (tmp == 4)
            {
                MON = 5000;
                //MONEY = money.thousand5;
            }
            else if (tmp == 5)
            {
                MON = 6000;
                //MONEY = money.thousand6;
            }
            else if (tmp == 6)
            {
                MON = 7000;
                //MONEY = money.thousand7;
            }


        }
        public int NUMBER//value 
        {
            get
            {
                //if (MONEY == money.thousand1) MON = 1000;
                //else if (MONEY == money.thousand2) MON = 2000;
                //else if (MONEY == money.thousand3) MON = 3000;
                //else if (MONEY == money.thousand4) MON = 4000;
                //else if (MONEY == money.thousand5) MON = 5000;
                //else if (MONEY == money.thousand6) MON = 6000;
                //else MON = 7000;
                return MON;
            }
            set 
            {
                MON = value;
            }             
        }
    }
}
