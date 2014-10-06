using System;
using System.Collections.Generic;
using System.Text;

namespace WindowsApplication4
{
    public class treval
    {
        public int rb, rd;
        public people[] man;
        public int man_count;
        public int active;
        public string log;
        public string message;

        Random RandomNumber;

        public bool zont;
        public bool ochki;
        public bool colnce;
        public bool luna;
        public bool rain;
        public bool drova;
        public bool holod;
        public bool palatka;
        public bool night;
        public bool sleep;
        public int stepa;

        public void main()
        {
            message = "none";
            stepa = 1;
            man_count = 0;
            luna = true;  
            man = new people[10];


            RandomNumber = new Random((int)DateTime.Now.Ticks);

            if (RandomNumber.Next(0,4) == 3)//зонт есть или нет?
                  zont = false;
                 else
                  zont = true;

              if (RandomNumber.Next(0, 4) == 3)//очки есть или нет?
                  ochki = false;
              else
                  ochki = true;

              if (RandomNumber.Next(0, 4) == 3)//дрова есть или нет?:
                  drova = false;
              else
                  drova = true;

              if (RandomNumber.Next(0, 4) == 3)//палатка есть?
                  palatka = false;
              else
                  palatka = true;
              
            if (RandomNumber.Next(0, 4) == 3)
              {
                  night = false;
                  colnce = true;
              }
              else
              {
                  night = true;
                  colnce = false;
              }
              
            if (RandomNumber.Next(0, 4) == 3)
                  rain = true;
              else
                  rain = false;
              
            if (RandomNumber.Next(0, 4) == 3)
                  holod = true;
              else
                  holod = false;
              
            if (RandomNumber.Next(0, 4) == 3)
                sleep = true;
              else
                sleep = false;
            
            
            
            holod = false;
              night = false;
            //  sleep = false;
             // drova = false;
            //  palatka = false;
            //  zont = false;
              colnce = true;

        
        }

        public void newman()
        {
            man[man_count] = new people();

            if (RandomNumber.Next(1, 4) == 1)
            {
                int stg = 0;
                int id = 0;
                
                man[man_count].main(true, stg,id);

            }
            else
            {
                rb = RandomNumber.Next(0, 4);
                rd = RandomNumber.Next(0, 4);
                man[man_count].main(false, rb, rd);

            }
            man_count++;
        }

        public void next()
        {
            active++;
            if (active >= man_count) active = 0;
        }

        public class people
        {
            public int step; 
            public void main(bool sd, int bs, int bn)
            {
            //    sdat = sd;
         //       vzat = !sd;
         //       book_number = bn;
        //        book_stage = bs;
                step = 0;
            }
            public void go()
            {
                step++;
            }

            public bool kontorka() 
            {
                if (step == 30) return true;
                return false;
            }

            public void door() 
            {
                step = 1;
            }


        }

    }
}
