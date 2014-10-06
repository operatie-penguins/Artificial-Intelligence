using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace WindowsApplication2
{
    public class Automobile
    {
        public CurrentCoord CurCoord = new CurrentCoord();

        public Bitmap img;

        public double[] K = { -1.25, 0.92, -0.65, 0.52 };
        public int[] B = { 1948, 147, 706, -189 };
        public int[] X = { 1270, 834, 360, 770, 1208 };
        public int[] Y = { 367, 910, 477, 212, 442};
        public Point[] CarIn = { new Point(1079, 604), new Point(938, 300), new Point(561, 662) };
        public Point[] CarOut = { new Point(1022, 678), new Point(938, 300), new Point(441, 552) };
        public bool WantsToPark = false;
        public bool Povorot = false;
        public bool stopped = false;
        public Timer timer2 = new Timer();
        public bool DrivenOut = false;

        public CarsTypes Type;

        public Direction Dir;

        public int StopTime = 7000;

        public int WaitTime = 0;

        private int timecount = 0;
        
        public Automobile()
        {
            Dir = Direction.EastSouth;
            CurCoord.X = X[0];
            CurCoord.Y = Y[0];
            Random rand = new Random();
            int type = rand.Next(90);
            if (type > 45) WantsToPark = true;
            type = rand.Next(90);
            
            type = rand.Next(90);
            if (type > 60) Type = CarsTypes.bus;
            else if (type > 30) Type = CarsTypes.car;
            else Type = CarsTypes.taxi;
            if (type > 45 && Type == CarsTypes.car && WantsToPark) Povorot = true;
            timer2.Tick += new EventHandler(timer2_Tick);
            timer2.Interval = 7000;
            
            if (Type == CarsTypes.car)
            {
                img = Properties.Resources.car1;
            }
            else if (Type == CarsTypes.taxi)
            {
                img = Properties.Resources.taxi1;
            }
            else if (Type == CarsTypes.bus)
            {
                img = Properties.Resources.bus1;
            }
            img.MakeTransparent();
            
        }

        void timer2_Tick(object sender, EventArgs e)
        {

            if (Type == CarsTypes.car)
            {
                CurCoord.X = CarOut[1].X;
                CurCoord.Y = CarOut[1].Y;


            }
            else if (Type == CarsTypes.taxi)
            {
                CurCoord.X = CarOut[0].X;
                CurCoord.Y = CarOut[0].Y;

            }
            else if (Type == CarsTypes.bus)
            {
                CurCoord.X = CarOut[2].X;
                CurCoord.Y = CarOut[2].Y;

            }
            stopped = false;
            DrivenOut = true;
            timer2.Stop();
        }

        public void Turn()
        {
            if (Dir == Direction.EastSouth && CurCoord.X <= X[4] && Povorot)
            {
                Dir = Direction.EastNorth;
                CurCoord.X = X[4];
                CurCoord.Y = Y[4];
                if (Type == CarsTypes.car)
                {
                    img = Properties.Resources.car4;
                }
                else if (Type == CarsTypes.taxi)
                {
                    img = Properties.Resources.taxi4;
                }
                else if (Type == CarsTypes.bus)
                {
                    img = Properties.Resources.bus4;
                }
            }
            else if (Dir == Direction.EastSouth && CurCoord.X <= X[1])
            {
                Dir = Direction.SouthWest;
                CurCoord.X = X[1];
                CurCoord.Y = Y[1];
                if (Type == CarsTypes.car)
                {
                    img = Properties.Resources.car2;
                }
                else if (Type == CarsTypes.taxi)
                {
                    img = Properties.Resources.taxi2;
                }
                else if (Type == CarsTypes.bus)
                {
                    img = Properties.Resources.bus2;
                }

            }
            else if (Dir == Direction.SouthWest && CurCoord.X <= X[2])
            {
                Dir = Direction.WestNorth;
                CurCoord.X = X[2];
                CurCoord.Y = Y[2];
                if (Type == CarsTypes.car)
                {
                    img = Properties.Resources.car3;
                }
                else if (Type == CarsTypes.taxi)
                {
                    img = Properties.Resources.taxi3;
                }
                else if (Type == CarsTypes.bus)
                {
                    img = Properties.Resources.bus3;
                }
            }
            else if (Dir == Direction.WestNorth && CurCoord.X >= X[3])
            {
                Dir = Direction.NorthEast;
                CurCoord.X = X[3];
                CurCoord.Y = Y[3];
                if (Type == CarsTypes.car)
                {
                    img = Properties.Resources.car4;
                }
                else if (Type == CarsTypes.taxi)
                {
                    img = Properties.Resources.taxi4;
                }
                else if (Type == CarsTypes.bus)
                {
                    img = Properties.Resources.bus4;
                }
            }
        }

        public void Wait()
        {
            if (WantsToPark && Type == CarsTypes.car && CurCoord.X == CarIn[1].X && Math.Abs(CurCoord.Y - CarIn[1].Y) <= 5)
            {
                stopped = true;
                Dir = Direction.NorthEast;
                timer2.Start();
            }
            else if (WantsToPark && Type == CarsTypes.taxi && CurCoord.X == CarIn[0].X && Math.Abs(CurCoord.Y - CarIn[0].Y) <= 5)
            {
                stopped = true;
                timer2.Start();
            }
            else if (WantsToPark && Type == CarsTypes.bus && CurCoord.X == CarIn[2].X && Math.Abs(CurCoord.Y - CarIn[2].Y) <= 5)
            {
                stopped = true;
                timer2.Start();
            }
        }

        public void Motion()
        {
            if (!stopped)
            {
                int index = 0;
                if (Dir == Direction.SouthWest)
                {
                    index = 1;
                    CurCoord.X--;
                }
                else if (Dir == Direction.WestNorth)
                {
                    index = 2;
                    CurCoord.X++;
                }
                else if (Dir == Direction.NorthEast)
                {
                    index = 3;
                    CurCoord.X++;
                }
                else if (Dir == Direction.EastNorth)
                {
                    index = 3;
                    CurCoord.X--;
                }
                else
                {
                    CurCoord.X--;
                }
                CurCoord.Y = (int)(K[index] * CurCoord.X + B[index]);
            }

            Turn();

            Wait();

            
        }

    }
}
