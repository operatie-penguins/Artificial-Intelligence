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
        public factory fact; // завод



        public MyHookClass(IntPtr hWnd)
        {
            fact = new factory();
            // Assign the handle from the source window to this class.  
            simpr = RegisterWindowMessage("MyMessage");
            this.AssignHandle(hWnd);

        }

        protected override void WndProc(ref Message m)
        {

            if (fact.man_count == 0) fact.newman();
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
                    if (fact.man_count == 0)
                    {
                        m.Result = new IntPtr(1);
                    }
                    if (wparamlo == 1)// таблица 1 
                    {
                        if (lParam == 1)// таблица 1 условие 1
                        {
                            // Есть ли передо мной человек?
                            if (fact.active!=0)
                            {
                                //MessageBox.Show("Активный " + fact.active + " шаг впереди: " + (fact.man[fact.active - 1].step - 1) + ", шаг мой: " + fact.man[fact.active].step);
                                if ((fact.man[fact.active - 1].step - 1) == fact.man[fact.active].step) m.Result = new IntPtr(1);
                            }
                        }
                        else if (lParam == 2)// таблица 1 условие 2
                        {
                            // Стоит ли перед конторкой?
                            if (fact.man[fact.active].kontorka()) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 3)// таблица 1 условие 3
                        {
                            // Хочет взять книгу?
                            if (fact.man[fact.active].vzat) m.Result = new IntPtr(1);

                        }
                        else if (lParam == 4)// таблица 1 условие 4
                        {
                            // Хочет сдать книгу?
                            if (fact.man[fact.active].sdat) m.Result = new IntPtr(1);

                        }
                        else if (lParam == 5)// таблица 1 условие 5
                        {
                            // Стоит перед дверью?
                            if (fact.man[fact.active].door()) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 6)// таблица 1 условие 6
                        {
                            // Сделал дело? (сдал/принял книгу)
                            if (fact.man[fact.active].done) m.Result = new IntPtr(1);
                        }
                    }
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)// таблица 2 условие 1
                        {
                            //Идёт искать книгу?
                            if (fact.vzat) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 2)// таблица 2 условие 2
                        {
                            //Идёт отдать книгу?
                            if (fact.otdat()) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 3)// таблица 2 условие 3
                        {
                            //Идёт вверх?
                            if (fact.up) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 4)// таблица 2 условие 4
                        {
                            //Идёт вниз?
                            if (fact.down()) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 5)// таблица 2 условие 5
                        {
                            //Этаж совпадает с этажом книги?
                            if ((fact.b_pos - 1) == fact.b_b_stage) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 6)// таблица 2 условие 6
                        {
                            //На полке есть данная книга?
                            if (fact.books[fact.b_b_stage,fact.b_b_id])m.Result = new IntPtr(1);
                        }
                        else if (lParam == 7)// таблица 2 условие 7
                        {
                            //Этаж верхний?
                            if (fact.b_pos == 4) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 8)// таблица 2 условие 8
                        {
                            //Этаж нижний?
                            if (fact.b_pos == 1) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 9)// таблица 2 условие 9
                        {
                            //Была ли на полке нужная книга?
                            if (fact.getbook) m.Result = new IntPtr(1);
                        }
                    }
                    fact.log = "Запрос для таблицы #" + wparamlo + "; запрос условия #" + lParam + "; вернули начение: " + m.Result + "\r\n" + fact.log;
                    //if (fact.active != 0)
                    {
                      //  MessageBox.Show("Запрос для таблицы #" + wparamlo + "; запрос условия #" + lParam + "; вернули начение: " + m.Result);
                    }

                }
                else if (wparamhi == 1)//действия
                {
                    fact.log = "Запрос для таблицы #" + wparamlo + "; запрос действия #" + lParam + ";\r\n" + fact.log;
                   // MessageBox.Show("Запрос для таблицы #" + wparamlo + "; запрос действия #" + lParam);

                    if (wparamlo == 1)// таблица 1
                    {
                        if (lParam == 1)// таблица 1 действие 1
                        {
                            // шаг
                            //MessageBox.Show("Шаг для " + fact.active);
                            if (fact.man[fact.active].step == 5) fact.message = "none";
                            fact.man[fact.active].go();
                        }
                        else if (lParam == 2)// таблица 1 действие 2
                        {
                            // уйти
                            fact.deleteman(fact.active);
                        }
                        else if (lParam == 3)// таблица 1 действие 3
                        {
                            // запросить книгу
                            fact.getbook = false; // ещё не взял
                            fact.b_b_id    = fact.man[fact.active].book_number; // номер книги
                            fact.b_b_stage = fact.man[fact.active].book_stage; // номер этажа
                            fact.b_pos = 1; // на 1 этаж
                            fact.vzat = true;
                            fact.up = true;
                            fact.message = "if";
                            Application.DoEvents();
                            Thread.Sleep(300);

                        }
                        else if (lParam == 4)// таблица 1 действие 4
                        {
                            // отдать книгу

                            for (int i = 0; i < 4; i++)
                            {
                                for (int j = 0; j < 4; j++)
                                {
                                    if (fact.books[i, j] == false)
                                    {
                                        fact.man[fact.active].book_stage = i;
                                        fact.man[fact.active].book_number = j;
                                    }
                                }
                            }

                            fact.getbook = false; // ещё не взял
                            fact.b_b_id = fact.man[fact.active].book_number; // номер книги
                            fact.b_b_stage = fact.man[fact.active].book_stage; // номер этажа
                            fact.b_pos = 1; // на 1 этаж
                            fact.vzat =false;
                            fact.up = true;
                            fact.message = "carried";
                            Application.DoEvents();
                            Thread.Sleep(300);
                        }
                        else if (lParam == 5)// таблица 1 действие 5
                        {
                            // следующий
                            Random RandomNumber = new Random();
                            if (RandomNumber.Next(1, 5) == 1)
                            {
                                if (fact.man[fact.man_count - 1].step >1)fact.newman();
                            }
                            //MessageBox.Show("Next!");
                            fact.next();
                        }
                    }
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            // шаг вверх по лестнице
                            fact.b_pos++;
                        }
                        else if (lParam == 2)// таблица 2 действие 2
                        {
                            // начать спускаться вниз
                            fact.up = false;
                        }
                        else if (lParam == 3)// таблица 2 действие 3
                        {
                            // взять с полки нужную книгу
                            fact.books[fact.b_b_stage, fact.b_b_id] = false;
                            fact.getbook = true;
                        }
                        else if (lParam == 4)// таблица 2 действие 4
                        {
                            //Взять записку "Книги нет"
                            fact.getbook = false;
                        }
                        else if (lParam == 5)// таблица 2 действие 5
                        {
                            //Шаг вниз по лестнице
                            fact.b_pos--;
                        }
                        else if (lParam == 6)// таблица 2 действие 6
                        {
                            //отдать книгу
                            fact.b_pos = 0;
                            fact.message = "yourbook";
                            Application.DoEvents();
                            Thread.Sleep(300);
                            fact.man[fact.active].done = true;
                        }
                        else if (lParam == 7)// таблица 2 действие 7
                        {
                            // поставить книгу на полку
                            fact.books[fact.b_b_stage, fact.b_b_id] = true;
                            fact.getbook = true;
                        }
                        else if (lParam == 8)// таблица 2 действие 8
                        {
                            // сообщить что книги нету
                            fact.b_pos = 0;
                            fact.message = "nobook";
                            Application.DoEvents();
                            Thread.Sleep(300);

                            fact.man[fact.active].done = true;
                        }
                        else if (lParam == 9)// таблица 2 действие 9
                        {
                            // Сказать "Следующий!"
                            fact.man[fact.active].done = true;
                            fact.b_pos = 0;
                        }
                    }

                    Application.DoEvents();
                    Thread.Sleep(300);

                    m.Result = new IntPtr(1);


//                   MessageBox.Show("Для таблицы #" + wparamlo + "; действие #" + lParam + " --- Значение: " + m.Result);
                    
                
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
