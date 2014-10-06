using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Windows;
namespace WindowsApplication4
{

    public partial class Form1 : Form
    {
        MyHookClass hook;
        PictureBox[,] cassent;
        PictureBox[] people;
        PictureBox[] palatka;
        PictureBox[] zont;

        public Form1()
        {
            InitializeComponent();
        }

        
        private void Form1_Load(object sender, EventArgs e)
        {
            hook = new MyHookClass(class_1.fm1.Handle);
            hook.fact.main();
            hook.fact.newman();
            cassent = new PictureBox[4,4];
            palatka = new PictureBox[200];
            people= new PictureBox[200];
            zont = new PictureBox[1];
            textBox1.Visible = false;
            textBox2.Visible = false;
            textBox3.Text += Convert.ToString(hook.fact.zont) + "  зонт" + "\r\n" + Convert.ToString(hook.fact.ochki) + "  очки" + "\r\n" + Convert.ToString(hook.fact.drova) + "  дрова" + "\r\n" + Convert.ToString(hook.fact.palatka) + "  палатка" + "\r\n";
            textBox3.Text += Convert.ToString(hook.fact.sleep) + "  сон" + "\r\n" + Convert.ToString(hook.fact.rain) + "  дождь" + "\r\n" + Convert.ToString(hook.fact.holod) + "  холод" + "\r\n";
            if (hook.fact.zont)
                pictureBox4.Image = Image.FromFile("images/1.gif");
            if (hook.fact.ochki)
                pictureBox5.Image = Image.FromFile("images/1.gif");
            if (hook.fact.palatka)
                pictureBox6.Image = Image.FromFile("images/1.gif");
            if (hook.fact.drova)
                pictureBox7.Image = Image.FromFile("images/1.gif");



           for (int i = 0; i < 200; i++)
            {
                people[i] = new PictureBox();
                palatka[i] = new PictureBox();
                people[i].Image = Image.FromFile("images/boy_r.gif");
                palatka[i].Image = Image.FromFile("images/boy_r.gif");
                if (i < 200)
                {
                    people[i].Left = i * 1 + 20;
                    palatka[i].Left = i * 1 + 40;
                }
                people[i].Top = 250;
                people[i].Visible = true;
                people[i].Width = 40;
                people[i].Height = 100;
                people[i].Parent = pictureBox1;

                palatka[i].Top = 340;
                palatka[i].Visible = true;
                palatka[i].Width = 23;
                palatka[i].Height = 41;
                palatka[i].Parent = pictureBox1;

            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
          // pictureBox3.Image = Image.FromFile("images/" + hook.fact.message + ".gif");

            if (hook.fact.colnce)
                pictureBox1.Image = Image.FromFile("images/day.bmp");
            else
            if (hook.fact.luna)
                pictureBox1.Image = Image.FromFile("images/Night.bmp");

                if (hook.fact.rain)
                    pictureBox8.Image = Image.FromFile("images/rain.bmp");
                else
                    pictureBox8.Visible = false;


            // 50 360
            for (int i = 0; i < 200; i++)
            {
                people[i].Visible = false;
                palatka[i].Visible = false;
                label1.Text = "";
            }
            textBox4.Text = "";
            for (int i = 0; i < hook.fact.man_count;i++)
            {
                people[hook.fact.man[i].step].Visible = true;               
                if (hook.fact.man[i].step == 51)
                {
                    if ((hook.fact.ochki && hook.fact.colnce && !hook.fact.rain && !hook.fact.sleep) || (hook.fact.ochki && !hook.fact.night && !hook.fact.rain && !hook.fact.sleep))
                    {
                        textBox4.Text += "Одел очки";
                        people[hook.fact.man[i].step].Image = Image.FromFile("images/boy_ochki.gif");
                    }

                    if (hook.fact.zont && hook.fact.rain)
                    {
                        textBox4.Text += "  Одел зонт";
                        people[hook.fact.man[i].step].Image = Image.FromFile("images/boy_rain.gif");
                    }

                    if ((hook.fact.drova && hook.fact.holod && !hook.fact.rain) || (hook.fact.drova && hook.fact.night))
                    {
                        textBox4.Text += "  Развел огонь";
                        people[hook.fact.man[i].step].Width = 50;
                        people[hook.fact.man[i].step].Height = 61;
                        people[hook.fact.man[i].step].Image = Image.FromFile("images/3034.jpg");
                    }

                    if (hook.fact.palatka && hook.fact.sleep)
                    {
                        textBox4.Text += "  Разложил палатку";
                        people[hook.fact.man[i].step].Width = 100;
                        people[hook.fact.man[i].step].Height = 100;
                        people[hook.fact.man[i].step].Image = Image.FromFile("images/palatka7.jpg");
                    }
                    else
                        if (!hook.fact.palatka && hook.fact.sleep)
                        {
                            textBox4.Text += "  Уснул на земле";
                            people[hook.fact.man[i].step].Width = 100;
                            people[hook.fact.man[i].step].Height = 40;
                            people[hook.fact.man[i].step].Image = Image.FromFile("images/boy_Sleep.gif");
                        }  
                }
            }
            pictureBox2.Visible = false;
            pictureBox3.Visible = false;
                
            }

        private void textBox2_Click(object sender, EventArgs e)
        {
     //       textBox2.Text = hook.fact.log;
        }






    }
}