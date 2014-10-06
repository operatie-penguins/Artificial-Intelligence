using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace testprog
{
    public partial class Form1 : Form
    {
        Class1 h;
        PictureBox[] people;
        public Form1()
        {
            InitializeComponent();
           // timer1.Interval = 5;
            timer1.Start();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

            h = new Class1(Program.fm1.Handle);
            people = new PictureBox[5];
            h.t.main();
            pictureBox1.Image = Image.FromFile("images/no.gif");






        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
            for (int j=0; j<10; j++)
                if (h.t.active == j)
            {
                
                if (h.t.step[h.t.active] == 1) pictureBox2.Image = Image.FromFile("images/"+h.t.name[h.t.active]+".gif");
                if (h.t.step[h.t.active] == 2) pictureBox3.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 3) pictureBox4.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 4) pictureBox5.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 5) pictureBox6.Image = Image.FromFile("images/door.gif");
                if (h.t.step[h.t.active] == 6) pictureBox10.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 7) pictureBox11.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 8) pictureBox12.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 9) pictureBox13.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");
                if (h.t.step[h.t.active] == 10) pictureBox14.Image = Image.FromFile("images/" + h.t.name[h.t.active] + ".gif");

                
            }


        if (h.t.poz[0] == true) pictureBox1.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[1] == true) pictureBox2.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[2] == true) pictureBox3.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[3] == true) pictureBox4.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[4] == true) pictureBox5.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[5] == true) pictureBox6.Image = Image.FromFile("images/door.gif");
        if (h.t.poz[6] == true) pictureBox10.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[7] == true) pictureBox11.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[8] == true) pictureBox12.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[9] == true) pictureBox13.Image = Image.FromFile("images/no.gif");
        if (h.t.poz[10] == true) pictureBox14.Image = Image.FromFile("images/no.gif");
           // textBox2.Text = textBox2.Text + h.t.log;








        if (h.t.stol[0] == 10) pictureBox7.Image = Image.FromFile("images/t1.gif");
        if (h.t.stol[0] == h.t.active) pictureBox7.Image = Image.FromFile("images/t1" + h.t.name[h.t.active] + ".gif");
        if (h.t.stol[1] == 10) pictureBox8.Image = Image.FromFile("images/t2.gif");
        if (h.t.stol[1] == h.t.active) pictureBox8.Image = Image.FromFile("images/t" + h.t.name[h.t.active] + ".gif");
        if (h.t.stol[2] == 10) pictureBox9.Image = Image.FromFile("images/t2.gif");
        if (h.t.stol[2] == h.t.active) pictureBox9.Image = Image.FromFile("images/t" + h.t.name[h.t.active] + ".gif");

        textBox1.Text = "Группа" + Convert.ToString(h.t.active+1);
        textBox2.Text = Convert.ToString(h.t.step[h.t.active])+"шаг";
        textBox3.Text = Convert.ToString(h.t.sid[h.t.active]) + "стол";
        textBox7.Text = h.t.name[h.t.active];
        textBox8.Text = Convert.ToString(h.t.sidtime[h.t.active]);
        if (h.t.stol[0] == 10) textBox4.Text = "свободен";
        else textBox4.Text = "занят";
        if (h.t.stol[1] == 10) textBox5.Text = "свободен";
        else textBox5.Text = "занят";
        if (h.t.stol[2] == 10) textBox6.Text = "свободен";
        else textBox6.Text = "занят";

                       

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {

        }

        

        

    }
}