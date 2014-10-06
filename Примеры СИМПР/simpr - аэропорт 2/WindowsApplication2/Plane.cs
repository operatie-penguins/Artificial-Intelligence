using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace WindowsApplication2
{
    public class Plane
    {
        //public Bitmap img = Properties.Resources.img1;
        public Bitmap img = Properties.Resources.img_posadka;
        public CurrentCoord CurCoord = new CurrentCoord();
        public double K = -0.54;
        public int B = 473;
        public Point Angar1 = new Point(482, 213);
        //public Point Angar2 = new Point(596, 148);
        public bool Stopped = false;

        public bool Angar1Free = true;
        public bool Angar2Free = true;
        public Timer timer3 = new Timer();
        public int step = 1;
        public bool WantsToFly = false; 

        public Plane()
        {
            CurCoord.X = 0;
            CurCoord.Y = 473;
            timer3.Tick += new EventHandler(timer3_Tick);
            timer3.Interval = 10000;
        }

        void timer3_Tick(object sender, EventArgs e)
        {
            step = -1;
            timer3.Stop();
            Angar1Free = true;
            Stopped = false;
            WantsToFly = true;
            }

        public void StopInAngar()
        {
            Angar1Free = false;
            Stopped = true;
            step = 0;
            img = Properties.Resources.img_vzlet;
        }

        public void Wait()
        {
            timer3.Start();
        }

        public void Motion()
        {
            CurCoord.X += step;
            CurCoord.Y = (int)(K * CurCoord.X + B);
            if (Angar1Free && CurCoord.X == Angar1.X)
            {
                //Появляется картинка
                StopInAngar();
                Wait();
            }
            if (CurCoord.X < -50)
            {
                step = 1;
                img = Properties.Resources.img_posadka;
            }
        }
    }
}
