using System;

using System.Windows.Forms;
using System.Threading;

using System.Runtime.InteropServices;

namespace WindowsApplication4
{

    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        uint simpr;
        public factory fact; // остановка
        
        public MyHookClass(IntPtr hWnd)
        {
            fact = new factory();
            // Assign the handle from the source window to this class.  
            simpr = RegisterWindowMessage("MyMessage");
            this.AssignHandle(hWnd);
        }

        protected override void WndProc(ref Message m)
        {

            int i = 0;
            int wparamhi;
            int wparamlo;
            int wparam;
            int lParam = Convert.ToInt32("" + m.LParam);

            if (m.Msg == simpr)
            {
                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;

                if (wparamhi == 0)//условия
                {
                    m.Result = new IntPtr(0);
                    if (wparamlo == 1)// таблица 1 
                    {
                      //  if (fact.man_count == 0) fact.world = 0; // нет людей не надо проверять людей.
                        if (fact.man_count == 0)
                        {
                         fact.newman();
                            fact.world = 0;
                        }

                        if (lParam == 1)// таблица 1 условие 1
                        {
                            // автобус?
                            if(fact.world  == 0 )m.Result = new IntPtr(1); // вернуть условие 1 = TRUE
                        }
                        else if (lParam == 2)// таблица 1 условие 2
                        {
                            // контролёр?
                            if (fact.world == 1) m.Result = new IntPtr(1); // вернуть условие 1 = TRUE
                        }
                        else if (lParam == 3)// таблица 1 условие 2
                        {
                            // человек?
                            if (fact.world == 2) m.Result = new IntPtr(1); // вернуть условие 1 = TRUE
                            fact.world++;
                            if (fact.world == 3) fact.world = 0;
                        }

                    }
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)// таблица 2 условие 1
                        {
                            // достаточно людей на остановке?
                            int tmp = 0;
                            for (i = 0; i < fact.man_count; i++)
                            {
                                if (fact.man[i].na_ostanovke) tmp++;
                            }
                            if (tmp >= fact.maxbus) m.Result = new IntPtr(1); 

                        }
                        else if (lParam == 2)// таблица 2 условие 2
                        {
                            // устал ли автобус ждать?
                            if(fact.buswaiting>fact.busmaxwait)m.Result=new IntPtr(1);
                                                       
                        }
                    }
                    else if (wparamlo == 3)// таблица 2 
                    {
                        if (lParam == 1)// таблица 3 условие 1
                        {
                            /////////////////////////////////////////////////////////
                            // прошел ли начало остановки?
                            if ((fact.k_before()==false)&&(fact.posend==false)) m.Result = new IntPtr(1);
        //tyt                    MessageBox.Show("прошел начало? " + m.Result);

                        }
                        else if (lParam == 2)// таблица 3 условие 2
                        {
                            // дошел до конца остановки?
                            if (fact.posend) m.Result = new IntPtr(1);
     //tyt                       MessageBox.Show("дошел до конца остановки? " + m.Result);
                        }
                        else if (lParam == 3)// таблица 3 условие 3
                        {
                            // стоит напротив безбилетника?

                            if (fact.k_bezb()) m.Result = new IntPtr(1);
     //tyt MessageBox.Show("стоит напротив безбилетника? " + m.Result);

                        }
                    }
                    else if (wparamlo == 4)// таблица 2 
                    {
                        
                        if (lParam == 1)// таблица 2 условие 1
                        {
                            //идёт до кассы
                            if (fact.man[fact.active].do_cassi) m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 2)// таблица 2 условие 2
                        {
                            //у кассы
                            if (fact.man[fact.active].cassa()) m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 3)// таблица 2 условие 2
                        {
                            //идёт после кассы
                            if (fact.man[fact.active].posle_cassi) m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 4)// таблица 2 условие 2
                        {
                            //дошел до остановки
                            if (fact.man[fact.active].u_ostanovki)m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 5)// таблица 2 условие 2
                        {
                            // стоит ли в очереди?
                            if (fact.man[fact.active].na_ostanovke) m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 6)// таблица 2 условие 2
                        {
                            // устал ли ждать? (не накожено)
                            if(fact.man[fact.active].ustal())m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 7)// таблица 2 условие 2
                        {
                            // идёт ли после остановки
                            if (fact.man[fact.active].posle_ostanovki) m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 8)// таблица 2 условие 2
                        {
                            if (fact.man[fact.active].kraj) m.Result = new IntPtr(1); 
                        }
                    }

                    else if (wparamlo == 5)// таблица 2 
                    {
                        m.Result = new IntPtr(1);
                        Random RandomNumber = new Random();
                        if (RandomNumber.Next(1, 3) == 1)
                        {
                            m.Result = new IntPtr(0);

                        }
                    }

                   // MessageBox.Show("Для таблицы #" + wparamlo + "; условие #" + lParam + " --- Значение: " + m.Result);
                    fact.log = "Запрос для таблицы #" + wparamlo + "; запрос условия #" + lParam + "; вернули начение: " + m.Result + "\r\n" + fact.log;
                    fact.fulllog += "Запрос для таблицы #" + wparamlo + "; запрос условия #" + lParam + "; вернули начение: " + m.Result + "\r\n";

                }
                else if (wparamhi == 1)//действия
                {
                    fact.log = "Запрос для таблицы #" + wparamlo + "; запрос действия #" + lParam + ";\r\n" + fact.log; 
                    fact.fulllog += "Запрос для таблицы #" + wparamlo + "; запрос действия #" + lParam + ";\r\n";
                    if (wparamlo == 1)// таблица 2 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            fact.next(); // следующий человечек
                            Random RandomNumber = new Random();
                            if (RandomNumber.Next(1, fact.man_count * fact.skpoyav + 3) == 1) // скорость появления человечков
                            {
                        fact.newman();
                                //  MessageBox.Show("Новый человек #" + (fact.man_count-1));
                            }
                        }
                    }                    
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            fact.buswaiting = 0;
                            MessageBox.Show("Люди уехали с остановки");
                            // удалить людей на остановке
                            for (i = fact.man_count-1; i >=0 ; i--)
                            {
                                if (fact.man[i].na_ostanovke)
                                {
                                    fact.deleteman(i);                                    
                                }
                            }
                          //  MessageBox.Show("удалить всех людей с остановки");                            
                        }
                    }
                    else if (wparamlo == 3)// таблица 3 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            // шаг                 
                         //   MessageBox.Show("шаг контролёра");
                            fact.k_step();
                        }
                        else if (lParam == 2)// таблица 2 действие 2
                        {
                            MessageBox.Show("Жестко покарать безбилетника!");
                            // удалити безбилетника
                            fact.k_delete();
                           // MessageBox.Show("Жестко покарать безбилетника!");

                        }
                    }
                    else if (wparamlo == 4)// таблица 4 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            fact.man[fact.active].step();
                           // MessageBox.Show("Челове №" + fact.active + " сделать шаг до позиции " + fact.man[fact.active].position + " " + fact.man[fact.active].posle_cassi + " " + fact.man[fact.active].u_ostanovki + " " + fact.man[fact.active].posle_ostanovki  + " ");
                            // действие

                        }
                        else if (lParam == 2)// таблица 2 действие 2
                        {
                       //     MessageBox.Show("встал на остановку ");
                            // встать на остановку
                            fact.man[fact.active].waitforbus();
                        }
                        else if (lParam == 3)// таблица 2 действие 2
                        {
                            // удалить человека
                            MessageBox.Show("Сел в такси и уехал");
                            fact.deleteman(fact.active);
                        }
                    }
                    else if (wparamlo == 5)// таблица 5 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            fact.man[fact.active].nobilet();
                            //MessageBox.Show("помечен как безбилетник! ");
                        }
                        else if (lParam == 2)// таблица 2 действие 2
                        {
                            fact.man[fact.active].step();
                          //  MessageBox.Show("после кассы шаг " + fact.man[fact.active].position);

                            // действие
                        }
                    }

                    Application.DoEvents();
                    Thread.Sleep(10);

                    m.Result = new IntPtr(1);
                  //  MessageBox.Show("Для таблицы #" + wparamlo + "; действие #" + lParam + " --- Значение: " + m.Result);
                                   
                }
            }
            else
            {
                base.WndProc(ref m);
                //MessageBox.Show(m.Msg + " " + simpr);
            }
            }
        }
    }
