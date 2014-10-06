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
        PictureBox[,] books;
        PictureBox[] people;

        public Form1()
        {
            InitializeComponent();
        }

        
        private void Form1_Load(object sender, EventArgs e)
        {
            hook = new MyHookClass(Program.fm1.Handle);
            hook.fact.main();
            hook.fact.newman();
            books = new PictureBox[4,4];
            people= new PictureBox[10];

            for (int i = 0; i < 10; i++)
            {
                people[i] = new PictureBox();
                people[i].Image = Image.FromFile("images/man.gif");
                if (i < 5)
                {
                    people[i].Left = i * 38 + 20;
                }
                else if (i == 5)
                {
                    people[i].Left = i * 38 + 20 + 25;

                }
                else if (i > 5)
                {
                    people[i].Left = i * 38 + 20 + 25 + 25;

                }
                people[i].Top = 340;
                people[i].Visible = true;
                people[i].Width = 23;
                people[i].Height = 41;
                people[i].Parent = pictureBox1;

            }

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    books[i, j] = new PictureBox();
                    books[i, j].Image = Image.FromFile("images/book.gif");
                        
                    books[i, j].Left = j * 70 + 220;
                    books[i, j].Top = 279-(i*46 + 71);
                    books[i, j].Visible =hook.fact.books[i,j];
                    books[i,j].Width =34;
                    books[i,j].Height=35;
                    books[i, j].Parent = pictureBox1;
                    
                }
            }



        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            pictureBox3.Image = Image.FromFile("images/" + hook.fact.message + ".gif");
            // 50 360
            for (int i = 0; i < 10; i++)
            {
                people[i].Visible = false;
                label1.Text = "";
            }
            for (int i = 0; i < hook.fact.man_count;i++)
            {
                people[hook.fact.man[i].step].Visible = true;
                if (hook.fact.man[i].step == 5)
                {
                    if(hook.fact.b_pos==0) hook.fact.updatebookan(i);
                    if (hook.fact.man[i].sdat) label1.Text = "Сдаёт"; else label1.Text = "Берёт";
                    label1.Text += " книгу с полки " + (hook.fact.man[i].book_stage+1) + " - номер " + (hook.fact.man[i].book_number+1);
                }
            }

            int pos = hook.fact.b_pos;
            if (pos == 0)
            {
                // основная;
                pictureBox2.Left = 238;
                pictureBox2.Top = 272;
            }
            else
            {
                // шкаф
                pictureBox2.Left =135;
                pictureBox2.Top = 223 - 46*(pos-1);
            }

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    books[i, j].Visible = hook.fact.books[i, j];
                }
            }

            string x = "";
                if (hook.fact.vzat)x+="T";else x+="F";
                if (hook.fact.otdat())x+="T";else x+="F";
                if (hook.fact.up)x+="T";else x+="F";
                if (hook.fact.down())x+="T";else x+="F";
                if ((hook.fact.b_pos - 1) == hook.fact.b_b_stage)x+="T";else x+="F";
                if (hook.fact.books[hook.fact.b_b_stage, hook.fact.b_b_id])x+="T";else x+="F";
                if (hook.fact.b_pos == 4)x+="T";else x+="F";
                if (hook.fact.b_pos == 1)x+="T";else x+="F";
                if (hook.fact.getbook)x+="T";else x+="F";
                //textBox1.Text = x;

                if (hook.fact.man_count > 0)
                {
                    string xx = "";
                    if (hook.fact.active != 0)
                    {
                        if ((hook.fact.man[hook.fact.active - 1].step - 1) == hook.fact.man[hook.fact.active].step) xx += "T"; else xx += "F";
                    }
                    else xx += "F";
                    if (hook.fact.man[hook.fact.active].kontorka()) xx += "T"; else xx += "F";
                    if (hook.fact.man[hook.fact.active].vzat) xx += "T"; else xx += "F";
                    if (hook.fact.man[hook.fact.active].sdat) xx += "T"; else xx += "F";
                    if (hook.fact.man[hook.fact.active].door()) xx += "T"; else xx += "F";
                    if (hook.fact.man[hook.fact.active].done) xx += "T"; else xx += "F";
                    textBox1.Text = x+ " " + xx + " " + hook.fact.active;
                }
            }



        

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void textBox2_Click(object sender, EventArgs e)
        {
            textBox2.Text = hook.fact.log;
        }






    }
}