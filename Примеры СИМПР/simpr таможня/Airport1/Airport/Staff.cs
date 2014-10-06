using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace Airport
{
    public class Policeman : Human
    {
        public string log = "";
        private System.Windows.Forms.Timer timer1 = new System.Windows.Forms.Timer();
        public Policeman()
        {
            timer1.Interval = 1000;
            timer1.Tick += new EventHandler(timer1_Tick);
            Image = Common.ImagesPoliceman.Stand;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Image = Common.ImagesPoliceman.Stand;
            timer1.Stop();
        }

        public void Help()
        {
            Image = Common.ImagesPoliceman.Come;
            timer1.Start();
            Common.TableMessage = "Сотрудником аэропорта оказана необходимая помощь.";
        }

        public void CallPolice()
        {
            Help();
            Common.TableMessage = "Вызвана милиция.";
        }

        public void Check()
        {
            Help();
        }
    }

    public class SapperDog : Human
    {
        private System.Windows.Forms.Timer timer1 = new System.Windows.Forms.Timer();
        public SapperDog()
        {
            timer1.Interval = 2000;
            timer1.Tick += new EventHandler(timer1_Tick);
            Image = new System.Drawing.Bitmap(1, 1);
            Image.MakeTransparent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Image = new System.Drawing.Bitmap(1, 1); 
            timer1.Stop();
        }

        public void CallSapper()
        {
            Image = Common.ImagesDogSapper.Sapper;
            timer1.Start();
            Common.TableMessage = "Обнаружена бомба! Вызван сапер.";
        }

        public void CallDog()
        {
            Image = Common.ImagesDogSapper.Dog;
            timer1.Start();
            Common.TableMessage = "Обнаружены наркотики! Вызван сотруднк со служебной собакой.";
        }
    }
}
