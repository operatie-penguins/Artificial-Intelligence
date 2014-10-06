using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace WindowsApplication9 // не забудьте поменять на свой namespace //
{

        
    public class MyHookClass : NativeWindow
    {
        public string MESSAGE1 = "";
        public string MESSAGE2 = "";
        public string MESSAGE3 = "";
        public string MESSAGE4 = "";
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]//обработчик сообщений
        static extern uint RegisterWindowMessage(string lpString);

        public customer CUST = new customer();
        uint simpr;
        public string log = "";

        public MyHookClass(IntPtr hWnd)
        {
            simpr = RegisterWindowMessage("MyMessage"); // регистрируем своё сообщение
            this.AssignHandle(hWnd);
        }
        protected override void WndProc(ref Message m) // в эту функцию приходят все сообщения от СИМПРА
        {
            
            if (m.Msg == simpr)
            {
                int wparamhi, wparamlo, wparam;
                int lParam = Convert.ToInt32("" + m.LParam);
                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;

                if (wparamhi == 0)//условия
                {
                    m.Result = new IntPtr(0);
                    if (lParam == 1)// таблица 1 условие 1, lparam - № условия
                    {
                        if (CUST.FINEX == finex.fine)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 2)// таблица 1 условие 2, lparam - № условия
                    {
                        if (CUST.FINEX == finex.exellent)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 3)// таблица 1 условие 3, lparam - № условия
                    {
                        if (CUST.SEASON == season.winter)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 4)// таблица 1 условие 4, lparam - № условия
                    {
                        if (CUST.SEASON == season.spring)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 5)// таблица 1 условие 5, lparam - № условия
                    {
                        if (CUST.SEASON == season.summer)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 6)// таблица 1 условие 6, lparam - № условия
                    {
                        if (CUST.SEASON == season.autumn)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 7)// таблица 1 условие 7, lparam - № условия
                    {
                        if (CUST.MON == 1000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 8)// таблица 1 условие 8, lparam - № условия
                    {
                        if (CUST.MON == 2000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 9)// таблица 1 условие 9, lparam - № условия
                    {
                        if (CUST.MON == 3000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 10)// таблица 1 условие 10, lparam - № условия
                    {
                        if (CUST.MON == 4000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 11)// таблица 1 условие 11, lparam - № условия
                    {
                        if (CUST.MON == 5000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 12)// таблица 1 условие 12, lparam - № условия
                    {
                        if (CUST.MON == 6000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 13)// таблица 1 условие 13, lparam - № условия
                    {
                        if (CUST.MON == 7000)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }

//                    else if (lParam == 14)// таблица 1 условие 14, lparam - № условия
  //                  {
    //                    //if (CUST.MON > 0)
      //                  {
        //                    m.Result = new IntPtr(1);
          //              }
            //        }
                    else if (lParam == 14)// таблица 1 условие 15, lparam - № условия
                    {
                        if (CUST.x == 227 || CUST.x == 360 || CUST.x == 500)//
                        {
                            m.Result = new IntPtr(1);
                        }
                    }
                    else if (lParam == 15)// таблица 1 условие 14, lparam - № условия
                    {
                        if (CUST.MON == 0)
                        {
                            m.Result = new IntPtr(1);
                        }
                    }

                }
                else if (wparamhi == 1)//действия
                {
                    if (lParam == 1)// таблица 1, lparam - № действия
                    {
                        CUST.MON -= 3000;
                        MESSAGE1 = "покупатель купил пуховик";
                        

                        if (CUST.MON == 0)
                        {
                            MESSAGE4 = "деньги закончились пойду домой";
                            CUST.KOORDINATE.KOOR = CUST.KOORDINATE.KOOR1;
                        }

                    }
                    if (lParam == 2)// таблица 1, lparam - № действия
                    {
                        CUST.MON -= 2000;

                        MESSAGE2 = "покупатель купил ветровку";
                        

                        
                        if (CUST.MON == 0)
                        {
                            MESSAGE4 = "деньги закончились пойду домой";
                            CUST.KOORDINATE.KOOR = CUST.KOORDINATE.KOOR1;
                        }

                    }
                    if (lParam == 3)// таблица 1, lparam - № действия
                    {
                        CUST.MON -= 1000;
                        MESSAGE3 = "покупатель купил футболку";
                        

                        if (CUST.MON == 0)
                        {
                            MESSAGE4 = "деньги закончились пойду домой";
                            CUST.KOORDINATE.KOOR = CUST.KOORDINATE.KOOR1;
                        }

                    }
                    if (lParam == 4)// таблица 1, lparam - № действия
                    {
                        MESSAGE4 = "покупатель ничего не купил";
                        
                    }
                    if (lParam == 5)// таблица 1, lparam - № действия
                    {
                        MESSAGE4 = "покупатель идет домой";
                        CUST.KOORDINATE.KOOR = CUST.KOORDINATE.KOOR1;
                    }
                    if (lParam == 6)// таблица 1, lparam - № действия
                    {
                        MESSAGE4 = "покупатель идет в другой магазин";
                        CUST.KOORDINATE.KOOR = CUST.KOORDINATE.KOOR2;
                    }
                    CUST.KOORDINATE.position++;
                    CUST.x = CUST.KOORDINATE.KOOR[CUST.KOORDINATE.position].X;
                    CUST.y = CUST.KOORDINATE.KOOR[CUST.KOORDINATE.position].Y;
                    if (CUST.KOORDINATE.position == CUST.KOORDINATE.KOOR.Length - 1)////2
                    {
                        CUST = new customer();
                        MESSAGE4 = "пошел следующий покупатель";
                        MESSAGE3 = "";
                        MESSAGE2 = "";
                        MESSAGE1 = "";
                    }
                    Application.DoEvents();
                    m.Result = new IntPtr(1);
                    Thread.Sleep(500);
                }
                log = " 0у,1д(" + wparamhi + ")__№( " + lParam + ") __" + m.Result + "\r\n" + log;
            
            }
            else
            {
                base.WndProc(ref m); // для всех действий не связанных с СИМПР возвращаем управление программе
            }
        }
    }
}
