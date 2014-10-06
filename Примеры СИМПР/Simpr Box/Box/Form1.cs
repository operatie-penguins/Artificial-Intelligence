using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

using System.Threading;
using System.Runtime.InteropServices;
using SimprApplication;

namespace Box
{
    public partial class Form1 : Form
    {
        string[,] matr;
        string[,] mas;
        string[] masleft;
        string[] masright;
        MyHookClass mhk;
        private bool hand = false;

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            matr = new string[8, 5]
			    {   {"0", "0", "0", "0", "0"} ,
                    {"0", "0", "0", "0", "0"} ,
                    {"0", "0", "0", "0", "0"} ,
                    {"0", "0", "0", "0", "0"} ,
					{"0", "0", "0", "0", "0"} ,
                    {"0", "0", "0", "0", "0"} ,
                    {"0", "0", "0", "0", "0"} ,
                    {"0", "0", "ch", "0", "0"} ,
                };
            masright = new string[8] { "box",  "0", "box", "box", "0", "box", "box", "0" };
            masleft = new string[8] { "0", "box", "0", "box", "box", "box", "0", "box" };
            LoadTable();
            mhk = new MyHookClass(this);
        }
        public void LoadTable()
        {
            mas = new string[4, 5]; //массив кубиков
            dataGridView1.Rows.Add(4);
            Random ran = new Random();
            for (int i = 0; i < 4; i++)
            { 
                for (int j = 0; j < 5; j++)
                {
                    if (ran.Next(2) + 1 == 1)
                        mas[i, j] = "1";
                    if (ran.Next(2) + 1 == 2)
                        mas[i, j] = "2";
                    if (mas[i, j] == null)
                        mas[i, j] = "1";
                }

                }
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                        if (mas[i,j] == "1")
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("white.bmp");
                        if (mas[i,j] == "2")
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("red.bmp");
                }
            }
            // заполнение поля
            dataGridView3.Rows.Add(8);
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 5; j++)
                {

                    if (matr[i, j] == "0")
                        dataGridView3.Rows[i].Cells[j].Value = new Bitmap("fon.bmp");
                    if (matr[i,j] == "ch")
                        dataGridView3.Rows[i].Cells[j].Value = new Bitmap("back.bmp");
                    }
                }
            dataGridView3.Rows.Add(8);
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 5; j++)
                {

                    if (matr[i, j] == "0")
                        dataGridView3.Rows[i].Cells[j].Value = new Bitmap("fon.bmp");
                    if (matr[i,j] == "ch")
                        dataGridView3.Rows[i].Cells[j].Value = new Bitmap("back.bmp");
                    }
                }
            dataGridView3.Rows.Add(8);
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 5; j++)
                {

                    if (matr[i, j] == "0")
                        dataGridView3.Rows[i].Cells[j].Value = new Bitmap("fon.bmp");
                    if (matr[i,j] == "ch")
                        dataGridView3.Rows[i].Cells[j].Value = new Bitmap("back.bmp");
                    }
             }

            dataGridView2.Rows.Add(8);
            dataGridView4.Rows.Add(8);
       
            for (int i = 0; i < 8; i++)
            {
                if (masleft[i]=="box")
                dataGridView2.Rows[i].Cells[0].Value = new Bitmap("box.bmp");
                if (masright[i]=="box")
                dataGridView4.Rows[i].Cells[0].Value = new Bitmap("box.bmp");
            }

            }
            
    
            #region "Действия"
        private int NotFull(string side)
        {
            int imax = -1;

            for (int i = 0; i < 8; i++)
            {
                if (side == "right")
                {
                    if ((masright[i] == "box") || (masright[i] == "red1") || (masright[i] == "red2") || (masright[i] == "red3"))
                    {
                        if (i >= imax)
                        imax = i;
                    }
                }
                if (side == "left")
                {
                    if ((masleft[i] == "box") || (masleft[i] == "white1") || (masleft[i] == "white2") || (masleft[i] == "white3"))
                    {
                        if (i >= imax)
                        imax = i;
                    }
                }
            }
            return imax;
        }

            public void Get() //взять кубик
            {
                for (int i = 3; i >= 0; i--)
                {
                    bool fl = false;
                    for (int j = 4; j >= 0; j--)
                    {
                        if (mas[i, j] == "1")
                        {
                            matr[7, 2] = "chw";
                            dataGridView3.Rows[7].Cells[2].Value = new Bitmap("backw.bmp");
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("fon.bmp");
                            mas[i, j] = "0";
                            fl = true;
                            break;
                        }
                        if (mas[i, j] == "2")
                        {
                            matr[7, 2] = "chr";
                            dataGridView3.Rows[7].Cells[2].Value = new Bitmap("backr.bmp");
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("fon.bmp");
                            mas[i, j] = "0";
                            fl = true;
                            break;
                        }
                    }
                    if (fl == true)
                        break;
                }              
            }
            public void GoLeftSide()
            {
                matr[7, 0] = "leftw";
                dataGridView3.Rows[7].Cells[0].Value = new Bitmap("leftw.bmp");
                matr[7, 2] = "0";
                dataGridView3.Rows[7].Cells[2].Value = new Bitmap("fon.bmp");
            }
            public void GoRightSide()
            {
                matr[7, 4] = "rightr";
                dataGridView3.Rows[7].Cells[4].Value = new Bitmap("rightr.bmp");
                matr[7, 2] = "0";
                dataGridView3.Rows[7].Cells[2].Value = new Bitmap("fon.bmp");
            }
            public void GiveBoxLeft()
            {
                int ind1, ind2;
                ind1 = ind2 = -1;
                for (int i = 0; i < 8; i++)
                    {
                        if (matr[i, 0] == "leftw")
                        {
                            ind1 = i;                           
                        }
                    }
                 ind2 = NotFull("left");
                 if (ind1 == ind2)
                    {
                        matr[ind1, 0] = "left";
                        dataGridView3.Rows[ind1].Cells[0].Value = new Bitmap("left.bmp");
                        if (masleft[ind1] == "box")
                        { masleft[ind1] = "white1"; dataGridView2.Rows[ind1].Cells[0].Value = new Bitmap("white1.bmp"); }
                        else if (masleft[ind1] == "white1")
                        { masleft[ind1] = "white2"; dataGridView2.Rows[ind1].Cells[0].Value = new Bitmap("white2.bmp"); }
                        else if (masleft[ind1] == "white2")
                        { masleft[ind1] = "white3"; dataGridView2.Rows[ind1].Cells[0].Value = new Bitmap("white3.bmp"); }
                        else if (masleft[ind1] == "white3")
                        { masleft[ind1] = "white4"; dataGridView2.Rows[ind1].Cells[0].Value = new Bitmap("white4.bmp"); }
                    }            
        }
            public void GiveBoxRight()
        {
            int ind1, ind2;
            ind1 = ind2 = -1;
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 4] == "rightr")
                {
                    ind1 = i;
                }
            }
            ind2 = NotFull("right");
            if (ind1 == ind2)
            {
                matr[ind1, 4] = "right";
                dataGridView3.Rows[ind1].Cells[4].Value = new Bitmap("right.bmp");
                if (masright[ind1] == "box")
                { masright[ind1] = "red1"; dataGridView4.Rows[ind1].Cells[0].Value = new Bitmap("red1.bmp"); }
                else if (masright[ind1] == "red1")
                { masright[ind1] = "red2"; dataGridView4.Rows[ind1].Cells[0].Value = new Bitmap("red2.bmp"); }
                else if (masright[ind1] == "red2")
                { masright[ind1] = "red3"; dataGridView4.Rows[ind1].Cells[0].Value = new Bitmap("red3.bmp"); }
                else if (masright[ind1] == "red3")
                { masright[ind1] = "red4"; dataGridView4.Rows[ind1].Cells[0].Value = new Bitmap("red4.bmp"); }
            }
        }
        public void TurnRightLeftSide()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 0] == "leftw")
                {
                    matr[i, 0] = "gow";
                    dataGridView3.Rows[i].Cells[0].Value = new Bitmap("gow.bmp");
                }
            }
        }
        public void TurnLeftLeftSide()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 0] == "gow")
                {
                    matr[i, 0] = "leftw";
                    dataGridView3.Rows[i].Cells[0].Value = new Bitmap("leftw.bmp");
                }
            }
        }
        public void StepLeftSide()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 0] == "gow")
                {
                    matr[i, 0] = "0";
                    dataGridView3.Rows[i].Cells[0].Value = new Bitmap("fon.bmp");
                    matr[i-1, 0] = "gow";
                    dataGridView3.Rows[i-1].Cells[0].Value = new Bitmap("gow.bmp");
                }
            }
        }
        public void TurnRightRightSide()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 4] == "gor")
                {
                    matr[i, 4] = "rightr";
                    dataGridView3.Rows[i].Cells[4].Value = new Bitmap("rightr.bmp");
                }
            }
        }
        public void TurnLeftRightSide()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 4] == "rightr")
                {
                    matr[i, 4] = "gor";
                    dataGridView3.Rows[i].Cells[4].Value = new Bitmap("gor.bmp");
                }
            }
        }
        public void StepRightSide()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 4] == "gor")
                {
                    matr[i, 4] = "0";
                    dataGridView3.Rows[i].Cells[4].Value = new Bitmap("fon.bmp");
                    matr[i - 1, 4] = "gor";
                    dataGridView3.Rows[i - 1].Cells[4].Value = new Bitmap("gor.bmp");
                }
            }
        }
        public void TurnLeft()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 0] == "left")
                {
                    matr[i, 0] = "ch";
                    dataGridView3.Rows[i].Cells[0].Value = new Bitmap("back.bmp");
                }
            }
        }
        public void TurnRight()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 4] == "right")
                {
                    matr[i, 4] = "ch";
                    dataGridView3.Rows[i].Cells[4].Value = new Bitmap("back.bmp");
                }
            }
        }
        public void StepUpLeft()
        {
            for (int i = 0; i < 8; i++)
            {
                if (matr[i, 0] == "ch")
                {
                    matr[i+1, 0] = "ch";
                    dataGridView3.Rows[i+1].Cells[0].Value = new Bitmap("back.bmp");
                    matr[i, 0] = "0";
                    dataGridView3.Rows[i].Cells[0].Value = new Bitmap("fon.bmp");
                    break;
                }
            }              
        }
        public void StepUpRight()
        {
                for (int i = 0; i < 8; i++)
                {
                    if (matr[i, 4] == "ch")
                    {
                        matr[i + 1, 4] = "ch";
                        dataGridView3.Rows[i + 1].Cells[4].Value = new Bitmap("back.bmp");
                        matr[i, 4] = "0";
                        dataGridView3.Rows[i].Cells[4].Value = new Bitmap("fon.bmp");
                        break;
                    }
                }
        }

        public void Go()
        {
            for (int j = 0; j < 5; j++)
            {
                if ((matr[7, j] == "ch") || (matr[7, j] == "left") || (matr[7, j] == "right"))
                {
                    matr[7, j] = "0";
                    dataGridView3.Rows[7].Cells[j].Value = new Bitmap("fon.bmp");
                    matr[7, 2] = "ch";
                    dataGridView3.Rows[7].Cells[2].Value = new Bitmap("back.bmp");
                }
            }
        }
            #endregion

        #region "Условия"
        public IntPtr Box()
            {
                bool flag = false;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if ((mas[i, j] == "1") || (mas[i, j] == "2"))
                            flag = true;  
                    }
                }
                return (flag == true)? new IntPtr(1): new IntPtr(0);
            }
            public IntPtr NearHeap()
            {
                 return ((matr[7, 2] == "chr") || (matr[7, 2] == "chw")||(matr[7,2]=="ch")) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr InHands()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if ((matr[i, j] == "chr") || (matr[i, j] == "rightr") || (matr[i, j] == "gor"))
                            flag = true;
                        if ((matr[i, j] == "chw") || (matr[i, j] == "leftw") || (matr[i, j] == "gow"))
                            flag = true;
                    }
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr RedInHands()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if ((matr[i, j] == "chr") || (matr[i, j] == "rightr")||(matr[i,j] == "gor" ))
                            flag = true;
                    }
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr WhiteInHands()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if ((matr[i, j] == "chw") || (matr[i, j] == "leftw")||(matr[i,j] == "gow"))
                            flag = true;
                    }
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr LeftSide()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if ((matr[i, j] == "chw") || (matr[i, j] == "leftw") || (matr[i, j] == "gow"))
                            flag = true;
                    }
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr RightSide()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        if ((matr[i, j] == "chr") || (matr[i, j] == "rightr") || (matr[i, j] == "gor"))
                            flag = true;
                    }
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr BoxNearLeft()
            {
                bool flag = false;
                int s, k;
                    for (int i = 7; i >= 0; i--)
                    {
                        s = -1;
                        k = -1;
                        if ((matr[i, 0] == "chw") || (matr[i, 0] == "leftw") || (matr[i, 0] == "gow"))
                            s = i;
                        if ((masleft[i] == "box")||(masleft[i] == "white1")||(masleft[i] == "white2")||(masleft[i] == "white3"))
                            k = i;
                        if ((s == k)&&(s>0)&&(k>0))
                            flag = true;
                    }
                    return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
        public IntPtr BoxNearRight()
        {
            bool flag = false;
            int s, k;
            for (int i = 7; i >= 0; i--)
            {
                s = -1;
                k = -1;
                if ((matr[i, 4] == "chr") || (matr[i, 4] == "rightr") || (matr[i, 4] == "gor"))
                    s = i;
                if ((masright[i] == "box")||(masright[i] == "red1")||(masright[i] == "red2")||(masright[i] == "red3"))
                    k = i;
                if ((s == k)&&(s>0)&&(k>0))
                    flag = true;
            }
            return (flag == true) ? new IntPtr(1):new IntPtr(0);
        }
            public IntPtr LeftSideBack()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    if ((matr[i,0] == "ch")||(matr[i,0]=="left"))
                        flag = true;
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr RightSideBack()
            {
                bool flag = false;
                for (int i = 0; i < 8; i++)
                {
                    if ((matr[i, 4] == "ch")||(matr[i,4] == "right"))
                        flag = true;
                }
                return (flag == true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr Step()
            {
                bool flag = false;
                if ((matr[7, 0] == "ch") || (matr[7, 4] == "ch") || (matr[7, 0] == "left") || (matr[7, 4] == "right"))
                    flag = true;
                return (flag != true) ? new IntPtr(1) : new IntPtr(0);
            }
            public IntPtr StepBox()
            {
                return (hand != true) ? new IntPtr(1) : new IntPtr(0);
            }
        
            #endregion

            private void button1_Click(object sender, EventArgs e)
            {
                Close();
            }

        }
}