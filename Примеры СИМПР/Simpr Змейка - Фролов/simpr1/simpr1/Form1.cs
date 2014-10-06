using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace simpr1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public MyHookClass myHook;

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Visible = false;
            label2.Visible = false;

            myHook = new MyHookClass(this.Handle,field.Image, rocket.Image,
                head.Image, tail.Image, wall.Image, fruit.Image);

            gamefield.Image = myHook.gmGame.Draw();

            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            gamefield.Image = myHook.gmGame.Draw();
            if (myHook.gmGame.bWin1) 
            { label1.Visible = true; }
            if (myGame.bWin)
            { label1.Visible = true; }
            else if (myHook.gmGame.bLose)
            { label2.Visible = true; }
        }
    }

    public class myGame
    {
        protected Image imgField;
        protected Image imgRocket;
        protected Image imgHead;
        protected Image imgTail;
        protected Image imgWall;
        protected Image imgFruit;
       
        public struct fldPoint
        {
            public int x;
            public int y; 
        }

        public enum NSWE
        {
            North = 1,
            South,
            West,
            East
        };

        public class Snake
        {
            protected List<fldPoint> lstSnake;

            public Snake()
            {
                lstSnake = new List<fldPoint>();

                fldPoint pntPoint = new fldPoint();
                for (int i = 5; i >= 2; i--)
                {
                    pntPoint.x = i; pntPoint.y = 10;
                    lstSnake.Add(pntPoint);
                }
            }

            public void Step(NSWE inNswe) 
            {
                List<fldPoint>.Enumerator enPoint = lstSnake.GetEnumerator();
                enPoint.MoveNext();
                fldPoint pntPnt = enPoint.Current;
                
                switch (inNswe)
                {
                    case (NSWE)1: pntPnt.y -= 1; break;
                    case (NSWE)2: pntPnt.y += 1; break;
                    case (NSWE)3: pntPnt.x -= 1; break;
                    case (NSWE)4: pntPnt.x += 1; break;
                }
                
                lstSnake.Insert(0, pntPnt);
                lstSnake.RemoveAt(lstSnake.Count - 1);
            }

            public void Grow() 
            {
                lstSnake.Add(lstSnake.Last<fldPoint>());
            }

            public void Butch(fldPoint inPnt) 
            {
                int i = lstSnake.IndexOf(inPnt);
                
                if (i >= 0)
                    for ( ; i <= lstSnake.Count - 1; ) lstSnake.RemoveAt(i);

                if (lstSnake.Count<fldPoint>() < 5)
                {
                    Grow(); Grow(); Grow(); Grow();
                }
            }

            public fldPoint[] GiveSnake() 
            {
                fldPoint[] pntArr;

                pntArr = new fldPoint[lstSnake.Count];
                lstSnake.CopyTo(pntArr);

                return pntArr;
            }
        }

        public class Rocket
        {
            protected fldPoint pntPlace;
            protected int iCount;

            public bool bStep;

            public Rocket(fldPoint inPoint)
            { pntPlace = inPoint; iCount = 0; bStep = true; }

            public void Step(NSWE inNswe) 
            {
                switch (inNswe)
                {
                    case (NSWE)1: pntPlace.y -= 1; break;
                    case (NSWE)2: pntPlace.y += 1; break;
                    case (NSWE)3: pntPlace.x -= 1; break;
                    case (NSWE)4: pntPlace.x += 1; break;
                }
            }

            public fldPoint GiveRocket()
            {
                return pntPlace;
            }

            public void New()
            {
                pntPlace.x = 2; pntPlace.y = 18;
            }

            public int GiveCount()
            {
                return iCount;
            }

            public void DecCount()
            {
                iCount--;
            }
        }

        public class Fruit
        {
            protected fldPoint pntPlace;

            public Fruit(fldPoint[] inWalls) { NewFruit(inWalls); }

            public void NewFruit(fldPoint[] inWalls) 
            {
                fldPoint pntPoint = new fldPoint();

                DateTime dt = System.DateTime.Now;
                Random rnd = new Random(dt.Millisecond + 1000 * dt.Second);
                pntPoint.x = rnd.Next(2, 29);
                pntPoint.y = rnd.Next(2, 19);

                bool bInWall = false;

                for (int i = 0; i < inWalls.Length; i++)
                    if ((pntPoint.x == inWalls[i].x) &&
                        (pntPoint.y == inWalls[i].y)) bInWall = true;

                if (bInWall) NewFruit(inWalls);
                else pntPlace = pntPoint;
                
            }

            public fldPoint GiveFruit()
            {
                return pntPlace;
            }
        }

        public List<fldPoint> lstWalls;
        public Snake snkSnake;
        public Rocket rctRocket;
        public Fruit frtFruit;

        public static bool bWin = false;
        public bool bWin1 = false;
        public bool bLose = false;

        public myGame(Image inField, Image inRocket,Image inHead, Image inTail,
                        Image inWall, Image inFruit)
        {
            imgField = inField;
            imgFruit = inFruit;
            imgHead = inHead;
            imgRocket = inRocket;
            imgTail = inTail;
            imgWall = inWall;

            snkSnake = new Snake();

            

            fldPoint pntPoint = new fldPoint();
            pntPoint.x = 2; pntPoint.y = 19;
            rctRocket = new Rocket(pntPoint);

            lstWalls = new List<fldPoint>();
            for (int i = 1; i <= 30; i++)
                for (int j = 1; j <= 20; j++)
                    if ((i == 1) || (j == 1) || (i == 30) || (j == 20))
                    {
                        pntPoint.x = i; pntPoint.y = j;
                        lstWalls.Add(pntPoint);
                    }
            for (int j = 10; j <= 16; j++)
                {
                    pntPoint.x = 14; //25
                    pntPoint.y = j;
                    lstWalls.Add(pntPoint);
                    pntPoint.x++;
                    lstWalls.Add(pntPoint);
                }
            for (int j = 24; j <= 27; j++)
            {
                pntPoint.x = j; pntPoint.y = 7;
                lstWalls.Add(pntPoint);
            }
         /*   for (int j = 5; j <= 16; j++)
                if ((j != 10)&&(j != 11))
                {
                    pntPoint.x = j + 5; pntPoint.y = j;
                    lstWalls.Add(pntPoint);
                    pntPoint.x = j + 5; pntPoint.y = 21 - j;
                    lstWalls.Add(pntPoint);
                }*/
            for (int i = 2; i <= 3; i++)
                for (int j = 18; j <= 19; j++)
                {
                    pntPoint.x = i; pntPoint.y = j;
                    lstWalls.Add(pntPoint);
                }

            fldPoint[] aWalls;
            aWalls = new fldPoint[lstWalls.Count];
            lstWalls.CopyTo(aWalls);
            
            frtFruit = new Fruit(aWalls);
        }

        public bool InWall(fldPoint pntPoint, fldPoint[] inWalls)
        {
            bool bInWall = false;

            for (int i = 0; i < inWalls.Length; i++)
                if ((pntPoint.x == inWalls[i].x) &&
                    (pntPoint.y == inWalls[i].y)) bInWall = true;

            return bInWall;
        }

        public fldPoint PointToPix(fldPoint pntPoint)
        {
            fldPoint pntPnt = new fldPoint();

            pntPnt.x = (pntPoint.x - 1) * 20;
            pntPnt.y = (pntPoint.y - 1) * 20;

            return pntPnt;
        }

        public Bitmap Draw()
        {
            Bitmap myBmp = new Bitmap(imgField);
            fldPoint[] aSnake = snkSnake.GiveSnake();

            fldPoint[] aWalls; 
            aWalls = new fldPoint[lstWalls.Count];
            lstWalls.CopyTo(aWalls);
            
            System.Drawing.Graphics myGr;
            myGr = Graphics.FromImage(myBmp);

            fldPoint pntPoint = PointToPix(frtFruit.GiveFruit());
            myGr.DrawImage(imgFruit, pntPoint.x, pntPoint.y);

            for (int i = 1; i < aSnake.Length; i++)
            {
                pntPoint = PointToPix(aSnake[i]);
                myGr.DrawImage(imgTail, pntPoint.x, pntPoint.y);
            }
            
            pntPoint = PointToPix(aSnake[0]);
            myGr.DrawImage(imgHead, pntPoint.x, pntPoint.y);
            
            for (int i = 0; i < aWalls.Length; i++)
            {
                pntPoint = PointToPix(aWalls[i]);
                myGr.DrawImage(imgWall, pntPoint.x, pntPoint.y);
            }

            pntPoint = PointToPix(rctRocket.GiveRocket());
            myGr.DrawImage(imgRocket, pntPoint.x, pntPoint.y);
  
            return myBmp;
        }
    }

    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        public myGame gmGame;

        uint simpr;

        public MyHookClass(IntPtr hWnd, Image inField, Image inRocket,Image inHead, 
                Image inTail, Image inWall, Image inFruit)
        {
            simpr = RegisterWindowMessage("MyMessage"); // регистрируем своё сообщение
            this.AssignHandle(hWnd);


            gmGame = new myGame(inField, inRocket, inHead, inTail, inWall, inFruit);

        }

        protected override void WndProc(ref Message m) // в эту функцию приходят все сообщения от СИМПРА
        {

            int wparamhi, wparamlo, wparam;
            int lParam = Convert.ToInt32("" + m.LParam);

            if (m.Msg == simpr)
            {

                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;

                if (wparamhi == 0)//условия
                {
                    if (wparamlo == 1)// таблица 1 
                    {
                        if (lParam == 1)// таблица 1 условие 1
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntTail = gmGame.snkSnake.GiveSnake()[1];
                            
                            if ((pntHead.x == pntTail.x) && (pntHead.y < pntTail.y))
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);//0
                        }
                        else if (lParam == 2)// таблица 1 условие 2
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntTail = gmGame.snkSnake.GiveSnake()[1];

                            if ((pntHead.x == pntTail.x) && (pntHead.y > pntTail.y))
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);
                        }
                        else if (lParam == 3)// таблица 1 условие 3
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntTail = gmGame.snkSnake.GiveSnake()[1];

                            if ((pntHead.y == pntTail.y) && (pntHead.x < pntTail.x))
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0); 
                        }
                        else if (lParam == 4)// таблица 1 условие 4
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntTail = gmGame.snkSnake.GiveSnake()[1];

                            if ((pntHead.y == pntTail.y) && (pntHead.x > pntTail.x))
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);//0
                        }
                        else if (lParam == 5)// таблица 1 условие 5
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntFruit = gmGame.frtFruit.GiveFruit();

                            if (pntHead.y > pntFruit.y)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);//0
                        }
                        else if (lParam == 6)// таблица 1 условие 6
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntFruit = gmGame.frtFruit.GiveFruit();

                            if (pntHead.y < pntFruit.y)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);//0
                        }
                        else if (lParam == 7)// таблица 1 условие 7
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntFruit = gmGame.frtFruit.GiveFruit();

                            if ((pntHead.y == pntFruit.y) && (pntHead.x > pntFruit.x))
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0); 
                        }
                        else if (lParam == 8)// таблица 1 условие 8
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntFruit = gmGame.frtFruit.GiveFruit();

                            if ((pntHead.y == pntFruit.y) && (pntHead.x < pntFruit.x))
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);
                        }
                        else if (lParam == 9)// таблица 1 условие 9
                        {
                            //свободность
                            myGame.fldPoint pntPoint = gmGame.snkSnake.GiveSnake()[0];
                            pntPoint.y--;

                            myGame.fldPoint[] aWalls;
                            aWalls = new myGame.fldPoint[gmGame.lstWalls.Count];
                            gmGame.lstWalls.CopyTo(aWalls);
                            myGame.fldPoint[] aSnake;
                            aSnake = new myGame.fldPoint[600];
                            aSnake = gmGame.snkSnake.GiveSnake();

                            if ((gmGame.InWall(pntPoint, aWalls)) || 
                                (gmGame.InWall(pntPoint, aSnake)))
                                m.Result = new IntPtr(0);//0
                            else m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 10)// таблица 1 условие 10
                        {
                            myGame.fldPoint pntPoint = gmGame.snkSnake.GiveSnake()[0];
                            pntPoint.y++;

                            myGame.fldPoint[] aWalls;
                            aWalls = new myGame.fldPoint[gmGame.lstWalls.Count];
                            gmGame.lstWalls.CopyTo(aWalls);
                            myGame.fldPoint[] aSnake;
                            aSnake = new myGame.fldPoint[600];
                            aSnake = gmGame.snkSnake.GiveSnake();

                            if ((gmGame.InWall(pntPoint, aWalls)) ||
                                (gmGame.InWall(pntPoint, aSnake)))
                                m.Result = new IntPtr(0);
                            else m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 11)// таблица 1 условие 11
                        {
                            myGame.fldPoint pntPoint = gmGame.snkSnake.GiveSnake()[0];
                            pntPoint.x--;

                            myGame.fldPoint[] aWalls;
                            aWalls = new myGame.fldPoint[gmGame.lstWalls.Count];
                            gmGame.lstWalls.CopyTo(aWalls);
                            myGame.fldPoint[] aSnake;
                            aSnake = new myGame.fldPoint[600];
                            aSnake = gmGame.snkSnake.GiveSnake();

                            if ((gmGame.InWall(pntPoint, aWalls)) ||
                                (gmGame.InWall(pntPoint, aSnake)))
                                m.Result = new IntPtr(0);
                            else m.Result = new IntPtr(1); 
                        }
                        else if (lParam == 12)// таблица 1 условие 12
                        {
                            myGame.fldPoint pntPoint = gmGame.snkSnake.GiveSnake()[0];
                            pntPoint.x++;

                            myGame.fldPoint[] aWalls;
                            aWalls = new myGame.fldPoint[gmGame.lstWalls.Count];
                            gmGame.lstWalls.CopyTo(aWalls);
                            myGame.fldPoint[] aSnake;
                            aSnake = new myGame.fldPoint[600];
                            aSnake = gmGame.snkSnake.GiveSnake();

                            if ((gmGame.InWall(pntPoint, aWalls)) ||
                                (gmGame.InWall(pntPoint, aSnake)))
                                m.Result = new IntPtr(0);
                            else m.Result = new IntPtr(1); 
                        }
                    }
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntRocket = gmGame.rctRocket.GiveRocket();

                            if (pntHead.y < pntRocket.y)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);
                        }
                        else if (lParam == 2)
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntRocket = gmGame.rctRocket.GiveRocket();

                            if (pntHead.y > pntRocket.y)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0); 
                        }
                        else if (lParam == 3)
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntRocket = gmGame.rctRocket.GiveRocket();

                            if (pntHead.x < pntRocket.x)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0); 
                        }
                        else if (lParam == 4)
                        {
                            myGame.fldPoint pntHead = gmGame.snkSnake.GiveSnake()[0];
                            myGame.fldPoint pntRocket = gmGame.rctRocket.GiveRocket();

                            if (pntHead.x > pntRocket.x)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);
                        }
                        else if (lParam == 5)
                        {
                            if (gmGame.rctRocket.GiveCount() <= 0)
                                m.Result = new IntPtr(1);
                            else
                                m.Result = new IntPtr(0);
                        }
                        else if (lParam == 6)
                        {
                            myGame.fldPoint pntRocket = gmGame.rctRocket.GiveRocket();
                            myGame.fldPoint[] aSnake;
                            aSnake = new myGame.fldPoint[600];
                            aSnake = gmGame.snkSnake.GiveSnake();

                            if (gmGame.InWall(pntRocket, aSnake))
                                m.Result = new IntPtr(1);//0
                            else m.Result = new IntPtr(0); //1
                        }
                    }
                }
                else if (wparamhi == 1)//действия
                {
                    if (wparamlo == 1)// таблица 1 
                    {
                        if (lParam == 1)// таблица 1 действие 1
                        {
                            // действие
                            gmGame.snkSnake.Step((myGame.NSWE)1);
                        }
                        else if (lParam == 2)// таблица 1 действие 2
                        {
                            // действие
                            gmGame.snkSnake.Step((myGame.NSWE)2);
                        }
                        else if (lParam == 3)// таблица 1 действие 3
                        {
                            // действие
                            gmGame.snkSnake.Step((myGame.NSWE)3);
                        }
                        else if (lParam == 4)// таблица 1 действие 4
                        {
                            // действие
                            gmGame.snkSnake.Step((myGame.NSWE)4);
                        }
                        else if (lParam == 5)// таблица 1 действие 5
                        {
                            // действие
                            //стоим)
                        }
                        else if (lParam == 6)// таблица 1 действие 6
                        {
                            // действие
                            gmGame.snkSnake.Grow();

                            myGame.fldPoint[] aWalls;
                            aWalls = new myGame.fldPoint[gmGame.lstWalls.Count];
                            gmGame.lstWalls.CopyTo(aWalls);
                            gmGame.frtFruit.NewFruit(aWalls);
                        }
                    }
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)// таблица 2 действие 1
                        {
                            // действие
                            if (gmGame.rctRocket.bStep)
                            gmGame.rctRocket.Step((myGame.NSWE)1);
                        }
                        else if (lParam == 2)// таблица 2 действие 2
                        {
                            if (gmGame.rctRocket.bStep)
                            gmGame.rctRocket.Step((myGame.NSWE)2);
                        }
                        else if (lParam == 3)
                        {
                            if (gmGame.rctRocket.bStep)
                            gmGame.rctRocket.Step((myGame.NSWE)3);
                        }
                        else if (lParam == 4)
                        {
                            if (gmGame.rctRocket.bStep)
                            gmGame.rctRocket.Step((myGame.NSWE)4);
                        }
                        else if (lParam == 5)
                        {
                            //myGame.bWin = true;
                            gmGame.bWin1 = true;
                        }
                        else if (lParam == 6)
                        {
                            gmGame.bLose = true;
                        }
                        else if (lParam == 7)
                        {
                            gmGame.snkSnake.Butch(gmGame.rctRocket.GiveRocket());
                        }
                        else if (lParam == 8)
                        {
                            gmGame.rctRocket.New();
                        }
                        else if (lParam == 9)
                        {
                            gmGame.rctRocket.DecCount();
                        }
                        if (gmGame.rctRocket.bStep) gmGame.rctRocket.bStep = false;
                        else gmGame.rctRocket.bStep = true;
                    }

                    Application.DoEvents();
                    Thread.Sleep(200); // если у нас есть визуальное отображение, то задержку можно установить здесь                    
                    m.Result = new IntPtr(1); // ответом на запрос действия со стороны СИМПР должна быть единица
                }
            }
            else
            {
                base.WndProc(ref m); // для всех действий не связанных с СИМПР возвращаем управление программе
            }



        }
    }

}
