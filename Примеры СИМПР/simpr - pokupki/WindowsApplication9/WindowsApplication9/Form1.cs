using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication9
{
    public partial class Form1 : Form
    {
      
        MyHookClass simpr;
        public Form1()
        {
            
            InitializeComponent();
            simpr = new MyHookClass(this.Handle);
            timer1.Interval = 100;
            timer1.Start();
            //Properties.Resources.человек.MakeTransparent();//сделать прозрачным фон человечка
        }

       
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Bitmap b = new Bitmap(795,625);
            Bitmap BITMAP = (Bitmap)Properties.Resources.человек;
            BITMAP.MakeTransparent();
            
            using (Graphics g = Graphics.FromImage(b))
            {
                g.Clear(Color.White);
                g.DrawImage(Properties.Resources._1, 0, 0);
                g.DrawImage(BITMAP, simpr.CUST.x, simpr.CUST.y);
            }
            e.Graphics.DrawImage(b,0,0);//в область экрана рисуется е
          
            textBox1.Text = simpr.CUST.FINEX.ToString();
            textBox2.Text = simpr.CUST.MON.ToString();
            textBox3.Text = simpr.CUST.SEASON.ToString();
            label1.Text = simpr.MESSAGE1;
            label2.Text = simpr.MESSAGE2;
            label3.Text = simpr.MESSAGE3;
            label4.Text = simpr.MESSAGE4;

           // richTextBox1.Text = simpr.log;
            
            
            }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

    }
}