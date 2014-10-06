using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Windows;
using System.Threading;

namespace testprog
{
   public class ttest
    {
       Random RandomNumber;
        public int group;
        public int active;
        public string [] name;
        public int [] stol;
        public int [] step;
        public bool[] poz;
        public bool begin = false;
        public int[] sidtime;
        public int[] sid;
       public int scet;
        public void main()
        {
            RandomNumber = new Random();
            group = 10;
            scet = 0;
            active = 0;
            step = new int [group];
            name = new string[group];
            poz = new bool[11];
            sid = new int[group];
            sidtime = new int[group];
            for (int i = 0; i < 10; i++)
            {
                
                step[i] = 0;
                if (RandomNumber.Next(1, 5) == 2)
                    sidtime[i] = 6;
                else
                    sidtime[i] = 10;
                
                sid[i] = 0;
            }
            stol = new int[3];
            for (int i = 0; i < 3; i++)
            stol[i] = 10;

        for (int i = 0; i < 11; i++)
            poz[i] = true;

        for (int i = 0; i < 10; i++)
            if (RandomNumber.Next(1, 5) == 3)
                name[i] = "man1";
            else
                name[i] = "man2";


            
        }
        public void delgroup()
        {
             // if (group == 1) group = 0;
            //  else
            //      {
            //          for (int i = active; i < group; i++)
            //          {
             //             step[active] = step[(active + 1)];
             //             name[active] = name[(active + 1)];
             //             sid[active] = sid[(active + 1)];
             //             sidtime[active] = sidtime[(active + 1)];

              //        }
             //         group--;
             //     }
                  poz[10] = true;
                  poz[5] = true;
                  scet++;
                //  MessageBox.Show("delit" + scet);

            
        
        }
        public void st()
        {
            poz[step[active]] = true;
            step[active]++;
            poz[step[active]] = false;
            
        
        
        }
        public void next()
        {
            //MessageBox.Show("n");
            if (active == (group - 1)) active = 0;
            else active++;
        }
        
        public void wait()
        {
            sidtime[active]--;
        
        }
        public void go()
        {
            if (sid[active] == 0)
            { 
                for (int i=6; i<10; i++)
                {
                    if (poz[i] == true) { step[active] = i; poz[i]=false; i = 10; }
                    //else step[active] = 10;
                }
            }
            else if (sid[active] == 1)
            {
                sid[active] = 0;
                stol[0] = 10;
                for (int i = 6; i < 10; i++)
                {
                    if (poz[i] == true) { step[active] = i; poz[i] = false; i = 10; }
                    //else step[active] = 10;
                }
            }
            else if (sid[active] == 2)
            {
                sid[active] = 0;
                stol[1] = 10;
                for (int i = 6; i < 10; i++)
                {
                    if (poz[i] == true) { step[active] = i; poz[i] = false; i = 10; }
                   // else step[active] = 10;
                }
            }
            else if (sid[active] == 3)
            {
                sid[active] = 0;
                stol[2] = 10;
                for (int i = 6; i < 10; i++)
                {
                    if (poz[i] == true) { step[active] = i; poz[i] = false; i = 10; }
                   // else step[active] = 10;
                }
            }
            if (step[active] == 10)
            {
                MessageBox.Show("Группа " + active + "выходит через черный ход. удаляем");
                delgroup();
            
            }
            
        }



       public void seat1()
       {
           sid[active] = 1;
           stol[0] = active;
           poz[5] = true;
       
       }
       public void seat2()
       {
           sid[active] = 2;
           stol[1] = active;
           poz[5] = true;
       }
       public void seat3()
       {
           sid[active] = 3;
           stol[2] = active;
           poz[5] = true;
       }



    }
}
