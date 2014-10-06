using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO;

namespace WindowsApplication2
{
    public class Simpr : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        public Automobile[] Auto = new Automobile[5];
        public Plane pl = new Plane();
        uint simpr;
        public int i = 0;
        public bool start = false;
        public bool stop = false;
        public string log = "";

        public Simpr(IntPtr hWnd)
        {
            simpr = RegisterWindowMessage("MyMessage"); // регистрируем своё сообщение
            this.AssignHandle(hWnd);
        }

        protected override void WndProc(ref Message m) // в эту функцию приходят все сообщения от СИМПРА
        {
            if (m.Msg == simpr)
            {
                
                if (!start) start = true;
                int wparamhi, wparamlo, wparam;
                int lParam = Convert.ToInt32("" + m.LParam);
                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;
                if (lParam == 0)
                {
                    stop = true;
                }

                if (wparamhi == 0)//условия
                {
                    //i = (i <= 3) ? i + 1 : 0;
                    m.Result = new IntPtr(0);
                    if (wparamlo == 1)// таблица 1 
                    {
                        if (lParam == 1)
                            if (i < 5) m.Result = new IntPtr(1);
                        if (lParam == 2) if (i == 5) m.Result = new IntPtr(1);
                    }
                    else if (wparamlo == 2)// таблица 2
                    {
                        switch(lParam)
                        {
                            case 1: if (Auto[i].Type == CarsTypes.car) m.Result = new IntPtr(1); break;
                            case 2: if (Auto[i].Type == CarsTypes.taxi) m.Result = new IntPtr(1); break;
                            case 3: if (Auto[i].Type == CarsTypes.bus) m.Result = new IntPtr(1); break;
                            case 4: if (Auto[i].WantsToPark) m.Result = new IntPtr(1); break;
                            case 5: if (Auto[i].Povorot) m.Result = new IntPtr(1); break;
                            case 6: if (Auto[i].Dir == Direction.EastSouth && Auto[i].CurCoord.X <= Auto[i].X[1]) m.Result = new IntPtr(1); break;
                            case 7: if (Auto[i].Dir == Direction.SouthWest && Auto[i].CurCoord.X <= Auto[i].X[2]) m.Result = new IntPtr(1); break;
                            case 8: if (Auto[i].Dir == Direction.WestNorth && Auto[i].CurCoord.X <= Auto[i].X[3]) m.Result = new IntPtr(1); break;
                            case 9: if (Auto[i].Dir == Direction.EastSouth && Auto[i].CurCoord.X <= Auto[i].X[4]) m.Result = new IntPtr(1); break;
                            case 10: if (Auto[i].CurCoord.X == Auto[i].CarIn[1].X && Math.Abs(Auto[i].CurCoord.Y - Auto[i].CarIn[1].Y) <= 5) m.Result = new IntPtr(1); break;
                            case 11: if (Auto[i].CurCoord.X == Auto[i].CarIn[0].X && Math.Abs(Auto[i].CurCoord.Y - Auto[i].CarIn[0].Y) <= 5) m.Result = new IntPtr(1); break;
                            case 12: if (Auto[i].CurCoord.X == Auto[i].CarIn[2].X && Math.Abs(Auto[i].CurCoord.Y - Auto[i].CarIn[2].Y) <= 5) m.Result = new IntPtr(1); break;
                            case 13: if (Auto[i].stopped) m.Result = new IntPtr(1); break;
                            case 14: if (Auto[i].DrivenOut) m.Result = new IntPtr(1); break;
                            case 15: if (Auto[i].CurCoord.X > 1275) m.Result = new IntPtr(1); break;
                        }
                    }
                    else if (wparamlo == 3)// таблица 3
                    {
                        switch (lParam)
                        {
                            case 1: if (pl.CurCoord.X == pl.Angar1.X) m.Result = new IntPtr(1); break;
                            case 2: if (pl.Angar1Free) m.Result = new IntPtr(1); break;
                            case 3: if (pl.Stopped) m.Result = new IntPtr(1); break;
                            case 4: if (pl.WantsToFly) m.Result = new IntPtr(1); break;
                            case 5: if (pl.CurCoord.X < -50) m.Result = new IntPtr(1); break;
                        }
                    }
                }
                else if (wparamhi == 1)//действия
                {
                    if (wparamlo == 2)// таблица 2 
                    {
                        switch (lParam)
                        {
                            case 1: break;
                            case 2: Auto[i].Turn(); break;
                            case 3: Auto[i].Wait(); break;
                            case 4: Auto[i].stopped = true; break;
                            case 5: Auto[i].stopped = true; break;
                            case 6: Auto[i] = new Automobile(); break;
                           // case 7: if (Auto[(i + 1) % 6] != null) i = (i + 1) % 6; break;


                        }
                    }
                    if (wparamlo == 3)// таблица 3
                    {
                        switch (lParam)
                        {
                            case 1: break;
                            case 2: pl.StopInAngar(); break;
                            case 3: pl.Wait(); break;
                            case 4: pl.Stopped = true; break;
                            case 5: pl.step = 1; break;
                        }
                    }
                    m.Result = new IntPtr(1); // ответом на запрос действия со стороны СИМПР должна быть единица
                    
                }
                Application.DoEvents();
                Thread.Sleep(10);
                log = "" + wparamhi + wparamlo + lParam + m.Result + "\r\n" + log;
                StreamWriter sr = new StreamWriter(File.Open("log.txt", FileMode.Create), Encoding.Default);
                sr.Write(log);
                sr.Close();
            }
            else
            {
                base.WndProc(ref m); // для всех действий не связанных с СИМПР возвращаем управление программе
            }
        }
    }
}

