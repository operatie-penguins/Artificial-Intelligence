using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication2
{
    public partial class Form1 : Form
    {
        Simpr simpr;
        int time = 0;

        public Form1()
        {
            InitializeComponent();
            timer1.Interval = 5;

            simpr = new Simpr(this.Handle);
            simpr.Auto[0] = new Automobile(); 
            simpr.pl = new Plane(); 
            // timer1.Start();
            //point = new PointF(img.Width, img.Height);
        }

        public void coord(int x1, int y1, int x2, int y2)
        {

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (simpr.start && !timer1.Enabled)
            {
                timer1.Start();
            }
            if (simpr.stop)
            {
                timer1.Stop();
            }
            for (int i = 0; i < 5; i++)
            {
                try
                {
                    if (!simpr.Auto[i].stopped)
                    {
                        e.Graphics.DrawImage(simpr.Auto[i].img, simpr.Auto[i].CurCoord.X, simpr.Auto[i].CurCoord.Y, 17, 17);
                    } else
                        if (simpr.Auto[i].Type == CarsTypes.taxi)
                        {
                            e.Graphics.DrawImage(Properties.Resources.taxi1, 1000+(i*15), 627, 17, 17);
                        } else
                            if (simpr.Auto[i].Type == CarsTypes.bus)
                            {
                                e.Graphics.DrawImage(Properties.Resources.bus2, 450, 616, 20, 20);
                            }
                    if (!simpr.pl.Stopped)
                    {
                        e.Graphics.DrawImage(simpr.pl.img, simpr.pl.CurCoord.X, simpr.pl.CurCoord.Y, 52, 52);
                    }
                    else
                        e.Graphics.DrawImage(Properties.Resources.img_stoyanka, 415, 130,80,40);
                }
                catch { }
            }

            //e.Graphics.DrawImage(img, 100, 100, 500, 500, 500, 500, 100);
            //e.Graphics.DrawEllipse(new Pen(new SolidBrush(Color.Blue)), 1270, 367, 10, 10);
            //e.Graphics.DrawEllipse(new Pen(new SolidBrush(Color.Blue)), 1206, 440, 10, 10);
            //e.Graphics.DrawEllipse(new Pen(new SolidBrush(Color.Blue)), 834, 910, 10, 10);
            //e.Graphics.DrawLine(new Pen(new SolidBrush(Color.Blue),3), 1270, 367, 834, 910);

            //e.Graphics.DrawEllipse(new Pen(new SolidBrush(Color.Blue)), 360, 479, 10, 10);
            //e.Graphics.DrawLine(new Pen(new SolidBrush(Color.Blue), 3), 834, 912, 361, 479);

            //e.Graphics.DrawEllipse(new Pen(new SolidBrush(Color.Blue)), 771, 214, 10, 10);
            //e.Graphics.DrawLine(new Pen(new SolidBrush(Color.Blue), 3), 361, 480,774,214);

            //e.Graphics.DrawLine(new Pen(new SolidBrush(Color.Blue), 3), 1206,440,774,214);

            //e.Graphics.DrawLine(new Pen(new SolidBrush(Color.Blue), 3), 17, 464, 722, 85);
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {      
            try
            {
                label1.Text = simpr.Auto[0].CurCoord.X + "," + simpr.Auto[0].CurCoord.Y + simpr.Auto[0].WantsToPark.ToString() + " " + simpr.Auto[0].Type.ToString() + " " + simpr.Auto[0].Povorot.ToString();
               // simpr.log = simpr.log.Substring(0, 1000);
            }
            catch { }
            
           // richTextBox1.Text = simpr.log;
            for (int i = 0; i < 5; i++)
            {
                try
                {
                    simpr.Auto[i].Motion();
                    simpr.pl.Motion();
                    time++;
                    if (simpr.Auto[i].CurCoord.X > 1280) simpr.Auto[i] = new Automobile();
                }
                catch { }
            }
            //if ((pl.CurCoord.X < 0 || pl.CurCoord.Y < 0) && !pl.Stopped)
            //{
            //    pl = new Plane();
            //}
            if (time == 200) simpr.Auto[1] = new Automobile();
            else if (time == 400) simpr.Auto[2] = new Automobile();
            else if (time == 600) simpr.Auto[3] = new Automobile();
            else if (time == 800) simpr.Auto[4] = new Automobile();
            else if (time == 1500) simpr.pl = new Plane();
            Invalidate();
        }

        //private void button1_Click(object sender, EventArgs e)
        //{
        //    timer1.Start();
            
        //}

        //private void button2_Click(object sender, EventArgs e)
        //{
        //    timer1.Stop();
        //}

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            label1.Text = e.X + ";" + e.Y;
        }
   
    }
}