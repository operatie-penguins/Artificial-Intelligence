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

        public Form1()
        {
            InitializeComponent();
        }

        
        private void Form1_Load(object sender, EventArgs e)
        {
            hook = new MyHookClass(this.Handle);
            hook.fact.main();
            hook.fact.newman();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            /*if (hook.fact.vsegoppl >= hook.fact.vsegopplvoobshe)
            {
                timer1.Enabled = false;
                MessageBox.Show("Прошли все люди: " + hook.fact.vsegoppl);
                this.Close();
                
            }*/
           
            textBox3.Text = hook.fact.log;
            int i;
            string info;
            info = "Всего на поле людей: " + hook.fact.man_count + "\r\n";
            int do_kassi = 0;
            int posle_kassi = 0;
            int na_ost = 0;
            int bilet = 0;
            int p_ost = 0;
            string inf2 = "";
            for (i = 0; i < hook.fact.man_count; i++)
            {
                inf2 += "Человек №" + i + ", находится ";
                if (hook.fact.man[i].do_cassi)
                { 
                    do_kassi++;
                    inf2 += "до кассы (шаг " + hook.fact.man[i].position +")";

                }
                if (hook.fact.man[i].posle_cassi && (!hook.fact.man[i].na_ostanovke) && (!hook.fact.man[i].posle_ostanovki))
                {
                    posle_kassi++;
                    inf2 += "после кассы (шаг " + hook.fact.man[i].position +")";
                }
                if (hook.fact.man[i].na_ostanovke)
                {
                    na_ost++;
                    inf2 += "на остановке, ждёт " + hook.fact.man[i].wait;
                }

                if (hook.fact.man[i].posle_ostanovki)
                {
                    p_ost++;
                    inf2 += "после остановки (шаг " + hook.fact.man[i].position +")";
                }
                
                
                if (hook.fact.man[i].bilet && hook.fact.man[i].na_ostanovke)
                {
                    inf2 += ", с билетом.";
                    bilet++;
                }
                else if (hook.fact.man[i].na_ostanovke)
                {
                    inf2 += ", без билета.";
                }
                inf2 += "\r\n";
            }
            info += "До кассы: " + do_kassi +"\r\n";
            info += "После кассы: " + posle_kassi + "\r\n";
            info += "На остановке: " + na_ost + "\r\n";
            info += "После остановки: " + p_ost + "\r\n";
            info += "С билетами: " + bilet + "\r\n";
            info += "Время ожидания автобуса: " + hook.fact.buswaiting + "\r\n";
            textBox1.Text = info + "\r\n\r\n" + inf2;
            label1.Text = "" + do_kassi;
            label2.Text = "" + posle_kassi;
            label3.Text = "Людей на остановке: " + na_ost;
            label4.Text = "" + p_ost;
            label5.Text = "Людей купило билет: " + bilet;            
            label7.Text = "Всего на поле людей: " + hook.fact.man_count;
            label8.Text = "Автобус ждёт: " + hook.fact.buswaiting;
            label9.Text = "Автобус ждёт всего: " + hook.fact.buswaitingvsego;
            label10.Text = "Сколько человек max ждёт: " + hook.fact.max_wait;
            label11.Text = "Людей для отправки автобуса: " + hook.fact.maxbus;
            label16.Text = "Всего людей прошло: " + hook.fact.vsegoppl;
          //  label12.Text = "Людей стоит у автобуса: " + na_ost;

            

          if (hook.fact.k_pos == -3)
            {
                pictureBox12.Visible = true;
                pictureBox13.Visible = false;
                pictureBox14.Visible = false;
                pictureBox15.Visible = false;

            }
            if (hook.fact.k_pos == -2)
            {
                pictureBox12.Visible = false;
                pictureBox13.Visible = true;
                pictureBox14.Visible = false;
                pictureBox15.Visible = false;

            }
            if (hook.fact.k_pos == -1)
            {
                pictureBox12.Visible = false;
                pictureBox13.Visible = false;
                pictureBox14.Visible = true;
                pictureBox15.Visible = false;

            }
            if (hook.fact.k_pos == 0)
            {
                pictureBox12.Visible = false;
                pictureBox13.Visible = false;
                pictureBox14.Visible = false;
                pictureBox15.Visible = true;


            }
            if (hook.fact.k_pos == 1)
            {
                pictureBox12.Visible = false;
                pictureBox13.Visible = false;
                pictureBox14.Visible = true;
                pictureBox15.Visible = false;

            }
            if (hook.fact.k_pos == 2)
            {
                pictureBox12.Visible = false;
                pictureBox13.Visible = true;
                pictureBox14.Visible = false;
                pictureBox15.Visible = false;

            }
            if (hook.fact.k_pos == 3)
            {
                pictureBox12.Visible = true;
                pictureBox13.Visible = false;
                pictureBox14.Visible = false;
                pictureBox15.Visible = false;

            }
            

            ///////////////////////////////
            if (na_ost == 0 & bilet == 0)
            {         
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = false;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false;              
            }
            if (na_ost == 1 & bilet == 0)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = false;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = true; 
            }
            if (na_ost == 1 & bilet == 1)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 2 & bilet == 0)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = false;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = true;
                pictureBox11.Visible = true; 
            }
            if (na_ost == 2 & bilet == 1)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = true;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 2 & bilet == 2)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = true;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 3 & bilet == 0)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = false;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = true;
                pictureBox10.Visible = true;
                pictureBox11.Visible = true; 
            }
            if (na_ost == 3 & bilet == 1)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = true;
                pictureBox10.Visible = true;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 3 & bilet == 2)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = true;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = true;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 3 & bilet == 3)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = true;
                pictureBox5.Visible = true;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 4 & bilet == 0)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = false;

                pictureBox7.Visible = false;
                pictureBox8.Visible = true;
                pictureBox9.Visible = true;
                pictureBox10.Visible = true;
                pictureBox11.Visible = true; 
            }
            if (na_ost == 4 & bilet == 1)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = true;
                pictureBox9.Visible = true;
                pictureBox10.Visible = true;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 4 & bilet == 2)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = true;
                pictureBox4.Visible = true;
                pictureBox5.Visible = false;
                pictureBox6.Visible = false;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = true;
                pictureBox11.Visible = true; 
            }
            if (na_ost == 4 & bilet == 3)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = true;
                pictureBox5.Visible = true;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = true;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 4 & bilet == 4)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = true;
                pictureBox4.Visible = true;
                pictureBox5.Visible = true;
                pictureBox6.Visible = true;

                pictureBox7.Visible = false;
                pictureBox8.Visible = false;
                pictureBox9.Visible = false;
                pictureBox10.Visible = false;
                pictureBox11.Visible = false; 
            }
            if (na_ost == 5)
            {
                pictureBox2.Visible = false;
                pictureBox3.Visible = false;
                pictureBox4.Visible = false;
                pictureBox5.Visible = false;
                pictureBox6.Visible = true;
            }



            string x = "";
            for (i = 0; i < hook.fact.man_count; i++)
            {
                x+="человек " + i + " - ";
                if (hook.fact.man[i].do_cassi) x += "T"; else x += "F";
                if (hook.fact.man[i].cassa()) x += "T"; else x += "F";
                if (hook.fact.man[i].posle_cassi) x += "T"; else x += "F";
                if (hook.fact.man[i].u_ostanovki) x += "T"; else x += "F";
                if (hook.fact.man[i].na_ostanovke) x += "T"; else x += "F";
                if (hook.fact.man[i].ustal()) x += "T"; else x += "F";
                if (hook.fact.man[i].posle_ostanovki) x += "T"; else x += "F";
                if (hook.fact.man[i].kraj) x += "T"; else x += "F";
                x += "\r\n";
            }

          //  x = "";
            if (hook.fact.k_before()) x += "T"; else x += "F";
            if (hook.fact.posend) x += "T"; else x += "F";
            if (hook.fact.k_bezb()) x += "T"; else x += "F";
            textBox2.Text = x + " --- " + hook.fact.k_pos; //tyt

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            // добавляем время ожидания
            int i;
            for (i = 0; i < hook.fact.man_count; i++)
            {
                if (hook.fact.man[i].na_ostanovke == true)hook.fact.man[i].wait++;
            }
            if (hook.fact.log.Length > 2000)
            {
                hook.fact.log = hook.fact.log.Substring(0, 2000);
            }
            hook.fact.buswaiting++;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_DoubleClick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            textBox3.Text = hook.fact.fulllog;
        }

        private void label16_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            
        }

    }
}