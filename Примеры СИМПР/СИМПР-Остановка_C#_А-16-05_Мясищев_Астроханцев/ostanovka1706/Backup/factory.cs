using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication4
{
    public class factory
    {
        public int buscount; // сколько щас в автобусе
        public int maxbus; // сколько влезает в автобус
        public int steps_do_cassa; // сколько шагов до кассы надо сделать?
        public int steps_do_ostan; // сколько шагов до остановки надо сделать?
        public int steps_posle_ostan; // сколько шагов после остановки надо сделать?
        public int max_wait; // сколько времени ждать? (в обращениях к нему)
        public int world; // автобус=0, контролёр=1, человек=2.

        ///////////////////////////////////////////
        public int k_pos;   // позиция контролёра
        public bool posend; // прошел остановку?

        ///////////////////////////////////////////
        public people[] man;
        public int man_count;
        public int active;
        public string log;
        public string fulllog;
        public int busmaxwait;
        public int buswaiting;
        public int skpoyav;
        public int vsegoppl;
        //public int vsegopplvoobshe;
        public int buswaitingvsego;
        public void main()
        {
            posend = false;
            fulllog = "";
            k_pos = 0; // позиция контролёра = -3 (до остановки)
            log = "";
            world = 0;
            buscount = 0;
            vsegoppl = 0;
            maxbus = 4; // сколько народу надо чтобы автобцс уехал
            active = 0;
            busmaxwait = 50;  //сколько автобус ждёт
            buswaitingvsego = 50; //сколько автобус ждёт копируем
            buswaiting = 0;
            steps_do_cassa = 4;
            steps_do_ostan = 4;
            steps_posle_ostan = 4;
           // vsegopplvoobshe = 10;  //сколько чнловек вообще будет
            max_wait = 40;         // сколько человек ждёт    
            skpoyav = 5;          // Частота появления людей
            man_count = 0; // щас нет людей
            man = new people[100];
            //for (int i = 0; i < 100; i++) man[i].main(steps_do_cassa, steps_do_ostan, steps_posle_ostan, max_wait);
        }       

        public void k_step()
        {
            k_pos++;
           /*f(k_pos<0)
            {
              return;
            }*/
            int i;
            int j=0;
            for(i=0;i<man_count;i++)
            {
                if(man[i].na_ostanovke)
                {
                    j++;
                }
            }
            posend =false;
            //if (k_pos > j++)
            if (k_pos == 4)
            {                
                k_pos = -2; /////////////////////////////
            }             
            return;
        }
        public bool k_bezb()
        {
            int i;
            int j = 0;
            for (i = 0; i < man_count; i++)
            {
                if (man[i].na_ostanovke)
                {
                    if (j == k_pos)
                    {
                        if (man[i].bilet == false)
                        {                                                    
                            return true;
                        }
                    }
                    j++;                    
                }                
            }            
         return false;
        }

        public bool k_before()
        {
            if (k_pos < 0) return true;
            return false;
        }

        public void k_delete()
        {
            int i;
            int j = 0;
            for (i = 0; i < man_count; i++)
            {
                if (man[i].na_ostanovke)
                {
                    if (j == k_pos)
                    {
                        deleteman(i);
                        return;
                    }
                    j++;
                }
            }            
            k_pos--;            
            k_step();            
        }
        

        public void newman()
        {
                vsegoppl++;
                man[man_count] = new people();
                man[man_count].main(steps_do_cassa, steps_do_ostan, steps_posle_ostan, max_wait);
                man_count++;
            
        }

        public void deleteman(int id)
        {
            for (int i = 0; i < man_count; i++)
            {
                if (i >= id) man[i] = man[i + 1];
            }
            man_count--;
        }

        public void next()
        {
            active++;
            if (active >= man_count) active = 0;
        }


        public class people
        {
            public bool bilet; // обелечен?                     1 
            public bool do_cassi; // ещё до кассы?              1
            public bool posle_cassi; // идёт после кассы?       0
            public bool u_ostanovki; // дошел до остановки?     0
            public bool na_ostanovke; // стоит ли в очереди?    0
            public bool posle_ostanovki; // прошел остановку    0
            public bool kraj; // дошел до до края экрана?       0
            public int  position; // позиция (шаг)              0 (до кассы 5 шагов например)    
            public int steps_do_cassa; // сколько шагов до кассы надо сделать?
            public int steps_do_ostan; // сколько шагов до остановки надо сделать?
            public int steps_posle_ostan; // сколько шагов после остановки надо сделать?
            public int max_wait; // сколько времени ждать? (в обращениях к нему)
            public int wait = 0;

            public void main(int sdc,int sdo,int spo, int mw)
            {
                steps_do_cassa = sdc;
                steps_do_ostan = sdo;
                steps_posle_ostan = spo;
                max_wait = mw;
                 //////////////////
                do_cassi = true;
                bilet = true;
                posle_cassi = false;
                na_ostanovke = false;
                u_ostanovki = false;
                kraj = false;
                posle_ostanovki = false;
                position = 0;
            }

            public bool ustal()
            {
                if (wait >= max_wait)
                {
                    goaway();
                    return true;
                }
                return false;
            }

            public bool cassa() // напротив кассы?
            {
                if (do_cassi == false) return false;
                if ((position + 1) >= steps_do_cassa) return true;
                return false;
            }

            public void step()
            {
                position++;
                if (do_cassi)
                {
                    if (position >= steps_do_cassa)
                    {
                        // прошел кассу, теперь идёт после кассы
                        do_cassi = false;
                        position = 0;
                        posle_cassi = true;
                    }
                }
                else if(posle_cassi&&!na_ostanovke&&!posle_ostanovki)
                {
                    if (position >= steps_do_ostan)
                    {
                        // дошел до остановки
                        u_ostanovki = true;
                        position = 0;
                    }
                }
                else if (posle_ostanovki)
                {
                    if (position >= steps_posle_ostan)
                    {                        
                        // дошел до края экрана
                        posle_ostanovki = false;
                        kraj = true;
                    }
                }
            }

            public void goaway() // задолбало ждать
            {
                na_ostanovke = false;
                u_ostanovki = false;
                posle_cassi = true;
                posle_ostanovki = true;
            }

            
            public void waitforbus() // встать на остановку
            {
                na_ostanovke = true;
            }

            public void nobilet()
            {
                bilet = false;
            }
            
        }

    }
}
