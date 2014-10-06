using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Management;
using System.Linq.Expressions;

namespace Airport
{
    public partial class Form1 : Form
    {
        MyHookClass simpr;

        static string GetWMIInfo(string path, string param)
        {
            WqlObjectQuery query = new WqlObjectQuery("SELECT * FROM " + path);
            ManagementObjectSearcher find = new ManagementObjectSearcher(query);

            string temp = "";
            foreach (ManagementObject mo in find.Get())
            {
                temp += mo[param];
            }

            return temp;
        }

        public Form1()
        {

            InitializeComponent();
            timer1.Interval = 95;
            timer1.Start();
            simpr = new MyHookClass(this.Handle);


            numericUpDown1.Value = Common.ProbIsHigh;
            numericUpDown2.Value = Common.ProbIsFat;
            numericUpDown3.Value = Common.ProbHasMetal;
            numericUpDown4.Value = Common.ProbHasPassport;
            numericUpDown5.Value = Common.ProbHasTicket;
            numericUpDown6.Value = Common.ProbHasVipCard;
            numericUpDown7.Value = Common.ProbHasLuggage;
            //numericUpDown8.Value = Common.ProbHasSuitcase;
            numericUpDown9.Value = Common.ProbHasLargeBag;
            numericUpDown10.Value = Common.ProbHasDrugs;
            numericUpDown11.Value = Common.ProbHasBomb;
            numericUpDown12.Value = Common.ProbHasDiamond;
            numericUpDown13.Value = Common.ProbHasPistol;

            Common.BackgroundSize = new Point(800,300);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            StreamWriter sw = new StreamWriter(File.Open("d:\\log.txt", FileMode.Create));
            try
            {
                sw.Write(simpr.log);
            }
            catch { }
            sw.Close();
            timer1.Stop();
        }

        private void button2_Click(object sender, EventArgs e)
        {
           
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbIsHigh = Convert.ToInt32(numericUpDown1.Value);
        }

        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbIsFat =  Convert.ToInt32(numericUpDown2.Value);
        }

        private void numericUpDown3_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasMetal =  Convert.ToInt32(numericUpDown3.Value);
        }

        private void numericUpDown4_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasPassport =  Convert.ToInt32(numericUpDown4.Value);
        }

        private void numericUpDown5_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasTicket =  Convert.ToInt32(numericUpDown5.Value);
        }

        private void numericUpDown6_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasVipCard =  Convert.ToInt32(numericUpDown6.Value);
        }

        private void numericUpDown7_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasLuggage =  Convert.ToInt32(numericUpDown7.Value);
        }

        private void numericUpDown8_ValueChanged(object sender, EventArgs e)
        {
            //Common.ProbHasSuitcase =  Convert.ToInt32(numericUpDown8.Value);
        }

        private void numericUpDown9_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasLargeBag =  Convert.ToInt32(numericUpDown9.Value);
        }

        private void numericUpDown10_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasDrugs =  Convert.ToInt32(numericUpDown10.Value);
        }

        private void numericUpDown11_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasBomb =  Convert.ToInt32(numericUpDown11.Value);
        }

        private void numericUpDown12_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasDiamond =  Convert.ToInt32(numericUpDown12.Value);
        }

        private void numericUpDown13_ValueChanged(object sender, EventArgs e)
        {
            Common.ProbHasPistol =  Convert.ToInt32(numericUpDown13.Value);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(simpr.Img, 0, 0);
            label16.Text = simpr.items;
            //GC.Collect();
        }
    }
}