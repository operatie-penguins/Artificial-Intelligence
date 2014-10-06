using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace parking
{
    public partial class Form1 : Form
    {

        MyHookClass simpr;

        public Form1()
        {
            InitializeComponent();
            simpr = new MyHookClass(this.Handle);
            timer1.Interval = 50;
            timer1.Start();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            StreamWriter LogWriter = new StreamWriter(File.Open("log.txt", FileMode.Create));
            LogWriter.Write(simpr.log);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Invalidate();
            richTextBox1.Text = simpr.log;

            if (simpr.Car.HasSpikes) { label4.ForeColor = Color.Green; label4.Text = "Да"; }
            else { label4.ForeColor = Color.Red; label4.Text = "Нет"; }

            if (simpr.Car.IsStudent) { label5.ForeColor = Color.Green; label5.Text = "Да"; }
            else { label5.ForeColor = Color.Red; label5.Text = "Нет"; }

            if (simpr.Car.IsDirty) { label6.ForeColor = Color.Green; label6.Text = "Да"; }
            else { label6.ForeColor = Color.Red; label6.Text = "Нет"; }

            label7.Text = simpr.Car.Messages;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(Properties.Resources.фон, 0, 0);
            e.Graphics.DrawImage(simpr.Car.CarImage, simpr.Car.Position);
            if (simpr.Car.ShowTrailer) e.Graphics.DrawImage(simpr.Car.TrailerImage, simpr.Car.TrailerPosition);
        }
    }
}