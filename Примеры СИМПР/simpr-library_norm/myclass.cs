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
        public treval fact; 



        public MyHookClass(IntPtr hWnd)
        {
            fact = new treval();
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
                                if (fact.colnce) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 2)// таблица 1 условие 2
                        {
                            if (fact.luna) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 3)// таблица 1 условие 3
                        {
                            if (fact.rain) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 4)// таблица 1 условие 4
                        {
                            if (fact.drova) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 5)// таблица 1 условие 5
                        {
                            if (fact.holod) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 6)// таблица 1 условие 6
                        {
                            if (fact.ochki) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 7)// таблица 1 условие 7
                        {
                            if (fact.palatka) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 8)// таблица 1 условие 8
                        {
                            if (fact.zont) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 9)// таблица 1 условие 9
                        {
                            if (fact.night) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 10)// таблица 1 условие 10
                        {
                            if (fact.sleep) m.Result = new IntPtr(1);
                        }
                    }
                    fact.log = "Запрос для таблицы #" + wparamlo + "; запрос условия #" + lParam + "; вернули начение: " + m.Result + "\r\n" + fact.log;
                }
                else if (wparamhi == 1)//действия
                {
                    fact.log = "Запрос для таблицы #" + wparamlo + "; запрос действия #" + lParam + ";\r\n" + fact.log;
                    if (wparamlo == 1)// таблица 1
                    {
                        if (lParam == 1)// таблица 1 действие 1
                        {
                           // MessageBox.Show("o4ki");
                            Application.DoEvents();
                            Thread.Sleep(6000);
                        }
                        else if (lParam == 2)// таблица 1 действие 2
                        {
                            // MessageBox.Show("palatka");
                            Application.DoEvents();
                            Thread.Sleep(6000);
                        }
                        else if (lParam == 3)// таблица 1 действие 3
                        {
                            // MessageBox.Show("zont");
                            Application.DoEvents();
                            Thread.Sleep(6000);
                        }
                        else if (lParam == 4)// таблица 1 действие 4
                        {
                            // MessageBox.Show("koster");
                            Application.DoEvents();
                            Thread.Sleep(6000);
                        }
                        else if (lParam == 5)// таблица 1 действие 5
                        {
                            Application.DoEvents();
                            Thread.Sleep(3000);
                            fact.luna = true;
                            if (fact.man[fact.active].step == 101)
                            {
                                fact.luna = true;
                                fact.man[fact.active].door();
                            }
                        }
                        if (lParam == 6)// таблица 1 действие 6
                        {
                            // MessageBox.Show("zemlya");
                            Application.DoEvents();
                            Thread.Sleep(6000);
                        }
                        if (lParam == 7)// таблица 1 действие 7
                        {
                            // шаг
                            if (fact.man[fact.active].step == 50*fact.stepa)
                            {
                                fact.luna = false;
                                fact.stepa = 2;
                            }
                            fact.man[fact.active].go();
                        }
                    }
                    Application.DoEvents();
                    Thread.Sleep(300);

                    m.Result = new IntPtr(1);
                }
            }
            else
            {
                base.WndProc(ref m);
            }
            }

        }
    }
