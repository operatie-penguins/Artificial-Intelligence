using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SIMPR
{
    public partial class MainForm : Form
    { 
        MyHookClass Simpr;
        Bitmap bkg = Properties.Resources.background;
        int sec = 0;

        public MainForm()
        {
            InitializeComponent();
            Simpr = new MyHookClass(this.Handle);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close(); 

        }



        private void timer1_Tick(object sender, EventArgs e)
        {
//             button1.Text = sec.ToString();
//             Refresh();
//             Graphics g = Graphics.FromImage(BackgroundImage);

//             Graphics g = Graphics.FromImage(BackgroundImage);
//             g.Clear(BackColor);
//             g.DrawImage(Properties.Resources.background, 0, 0);
//             BaseLift.GetGraphic(g);
//             BasePeople.GetGraphic(g);
//             Invalidate();
//             label1.Text = BasePeople.HumansLeaveLift[1].ToString() + "\n" + BasePeople.tmp.ToString();
            UpdateGraphic();
            
        }
        public void UpdateGraphic()
        {
            GC.Collect();
            Graphics g = Graphics.FromImage(BackgroundImage);
            g.Clear(BackColor);
            g.DrawImage(Properties.Resources.background, 0, 0);
            BaseLift.GetGraphic(g);
            BasePeople.GetGraphic(g);
            Invalidate();

        }



        private void button2_Click(object sender, EventArgs e)
        {
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
               GC.Collect();
//             b = new Bitmap(BackgroundImage);
//             Graphics g = Graphics.FromImage(BackgroundImage);
//             g.Clear(BackColor);
//             g.DrawImage(Properties.Resources.background, 0, 0);
//             BaseLift.GetGraphic(g);
//             BasePeople.GetGraphic(g);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            timer1.Start();
            ClientSize = bkg.Size;
            
            BackgroundImage = bkg;
            Top = 20;
            Left = 100;
        }


    }
}