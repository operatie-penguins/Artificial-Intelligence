using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace RabbitWolf
{
	public partial class Form1 : Form
	{
		string[,] matr;
        bool wasCarrot;
		MyHookClass mhk;
		bool start;
		public int ind;

        public class Index
        {
            public int i;
            public int j;
        }

		public Form1( )
		{
			InitializeComponent();
            mhk = new MyHookClass(this);
		}

        public void Form1_Load(object sender, EventArgs e)
		{
			
			matr = new string[10, 10]
			    {   {"f", "c", "0", "c", "0", "0", "f", "0", "f", "wb"} ,
					{"0", "0", "f", "0", "f", "0", "0", "0", "0", "0"} ,
					{"0", "f", "0", "0", "0", "f", "0", "f", "0", "f"} ,
					{"0", "0", "0", "f", "0", "0", "0", "0", "c", "0"} ,
					{"f", "c", "c", "0", "f", "0", "c", "f", "0", "c"} ,
					{"0", "0", "f", "0", "0", "0", "0", "0", "f", "f"} ,
					{"0", "f", "0", "0", "f", "c", "f", "0", "0", "0"} ,
					{"0", "0", "c", "0", "0", "0", "0", "0", "c", "f"} ,
					{"c", "f", "0", "f", "0", "0", "0", "f", "c", "0"} ,
					{"rt", "0", "f", "0", "c", "f", "0", "0", "f", "0"}
			    };
			LoadTable();
		}

        public void LoadTable()
        {
			start = false;
			comboBox1.SelectedIndex = 0;
            dataGridView1.Rows.Add(10);
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    string s = matr[i, j];
                    if (s != "0")
                    {
                        if (s == "c")
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Carrot.bmp");
                        if (s == "f")
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Wall.bmp");
                        if (s == "rt")
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("RabbitTop.bmp");
                        if (s == "wb")
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("WolfBottom.bmp");

                    }
                }
            }
        }

        public void DrawCell(int rowIndex, int columnIndex, string pict, string pologenie)
		{
			dataGridView1.Rows[rowIndex].Cells[columnIndex].Value = new Bitmap(pict);
			matr[rowIndex, columnIndex] = pologenie;
        }

        #region "Действия"
        private Index Find(string who)
        {
            Index ind = new Index();
            ind.i = ind.j = -1;
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (matr[i, j].Substring(0, 1) == who)
                    {
                        ind.i = i;
                        ind.j = j;
                        return ind;
                    }
                }
            }
            return ind;
        }

        private void TurnLeft(string who, string whoFull)
		{
            Index ind = new Index(); 
            ind = Find(who);
            int i = ind.i;
            int j = ind.j;
            if (matr[i, j] == who + "r")
            {
                DrawCell(i, j, whoFull + "Top.bmp", who + "t");
                return;
            }
            if (matr[i, j] == who + "l")
            {
                DrawCell(i, j, whoFull + "Bottom.bmp", who + "b");
                return;
            }
            if (matr[i, j] == who + "t")
            {
                DrawCell(i, j, whoFull + "Left.bmp", who + "l");
                return;
            }
            if (matr[i, j] == who + "b")
            {
                DrawCell(i, j, whoFull + "Right.bmp", who + "r");
                return;
            }
		}

        public void TurnLeftRabbit()
        {
            TurnLeft("r", "Rabbit");
        }

        public void TurnLeftWolf()
        {
            TurnLeft("w", "Wolf");
        }

        private void TurnRight(string who, string whoFull)
        {
            Index ind = new Index();
            ind = Find(who);
            int i = ind.i;
            int j = ind.j;
            if (matr[i, j] == who + "r")
            {
                DrawCell(i, j, whoFull + "Bottom.bmp", who + "b");
                return;
            }
            if (matr[i, j] == who + "l")
            {
                DrawCell(i, j, whoFull + "Top.bmp", who + "t");
                return;
            }
            if (matr[i, j] == who + "t")
            {
                DrawCell(i, j, whoFull + "Right.bmp", who + "r");
                return;
            }
            if (matr[i, j] == who + "b")
            {
                DrawCell(i, j, whoFull + "Left.bmp", who + "l");
                return;
            }
        }

        public void TurnRightRabbit()
        {
            TurnRight("r", "Rabbit");
        }

        public void TurnRightWolf()
        {
            TurnRight("w", "Wolf");
        }

        private void TurnBack(string who, string whoFull)
        {
            Index ind = new Index();
            ind = Find(who);
            int i = ind.i;
            int j = ind.j;
            if (matr[i, j] == who + "r")
            {
                DrawCell(i, j, whoFull + "Left.bmp", who + "l");
                return;
            }
            if (matr[i, j] == who + "l")
            {
                DrawCell(i, j, whoFull + "Right.bmp", who + "r");
                return;
            }
            if (matr[i, j] == who + "t")
            {
                DrawCell(i, j, whoFull + "Bottom.bmp", who + "b");
                return;
            }
            if (matr[i, j] == who + "b")
            {
                DrawCell(i, j, whoFull + "Top.bmp", who + "t");
                return;
            }
        }

        public void TurnBackRabbit()
        {
            TurnBack("r", "Rabbit");
        }

        public void TurnBackWolf()
        {
            TurnBack("w", "Wolf");
        }

        public void TurnLeftRightRabbit()
        {
            Random r = new Random();
            int n = r.Next(0, 2);
            if (n == 0)
                TurnLeft("r", "Rabbit");
            else
                TurnRight("r", "Rabbit");
        }

        public void TurnLeftRightWolf()
        {
            Random r = new Random();
            int n = r.Next(0, 2);
            if (n == 0)
                TurnLeft("w", "Wolf");
            else
                TurnRight("w", "Wolf");
        }

        public void TurnRightNotTurnRabbit()
        {
            Random r = new Random();
            int n = r.Next(0, 2);
            if (n == 0)
                TurnRight("r", "Rabbit");
        }

        public void TurnRightNotTurnWolf()
        {
            Random r = new Random();
            int n = r.Next(0, 2);
            if (n == 0)
                TurnRight("w", "Wolf");
        }

        public void TurnLeftNotTurnRabbit()
        {
            Random r = new Random();
            int n = r.Next(0, 2);
            if (n == 0)
                TurnLeft("r", "Rabbit");
        }

        public void TurnLeftNotTurnWolf()
        {
            Random r = new Random();
            int n = r.Next(0, 2);
            if (n == 0)
                TurnLeft("w", "Wolf");
        }

        public void TurnLeftRightNotTurnWolf()
        {
            Random r = new Random();
            int n = r.Next(0, 3);
            if (n == 0)
                TurnLeft("w", "Wolf");
            else
                TurnRight("w", "Wolf");
        }

        public void TurnLeftRightNotTurnRabbit()
        {
            Random r = new Random();
            int n = r.Next(0, 3);
            if (n == 0)
                TurnLeft("r", "Rabbit");
            else
                TurnRight("r", "Rabbit");
        }

        private bool CheckWolf(int i, int j)
        {
            string p = matr[i,j];
            if ((p == "wr") || (p == "wl") || (p == "wt") || (p == "wb"))
                return true;
            return false;
        }

        public void StepRabbit()
        {
            Index ind = new Index();
            ind = Find("r");
            int i = ind.i;
            int j = ind.j;
            string p = matr[i, j];

            DrawCell(i, j, "Grass.bmp", "0");
            if (p == "rl")
            {
                if (CheckWolf(i, j - 1))
                    DrawCell(i, j - 1, "WolfRight.bmp", "wr");
                else
                    DrawCell(i, j - 1, "RabbitLeft.bmp", "rl");
                return;
            }
            if (p == "rr")
            {
                if(CheckWolf(i,j+1))
                    DrawCell(i, j + 1, "WolfLeft.bmp", "wl");
                else
                    DrawCell(i, j + 1, "RabbitRight.bmp", "rr");
                return;
            }
            if (p == "rt")
            {
                if(CheckWolf(i-1,j))
                    DrawCell(i - 1, j, "WolfBottom.bmp", "wb");
                else
                    DrawCell(i - 1, j, "RabbitTop.bmp", "rt");
                return;
            }
            if (p == "rb")
            {
                if(CheckWolf(i+1, j))
                    DrawCell(i + 1, j, "WolfTop.bmp", "wt");
                else
                    DrawCell(i + 1, j, "RabbitBottom.bmp", "rb");
                return;
            }
        }

        public void StepWolf()
        {
            Index ind = new Index();
            ind = Find("w");
            int i = ind.i;
            int j = ind.j;
            string p = matr[i, j];
            if (wasCarrot == true)
                DrawCell(i, j, "Carrot.bmp", "c");
            else
                DrawCell(i, j, "Grass.bmp", "0");
            wasCarrot = false;

            if (p == "wl")
            {
                if (matr[i, j - 1] == "c")
                    wasCarrot = true;
                DrawCell(i, j - 1, "WolfLeft.bmp", "wl");
                return;
            }
            if (p == "wr")
            {
                if (matr[i, j + 1] == "c")
                    wasCarrot = true;
                DrawCell(i, j + 1, "WolfRight.bmp", "wr");
                return;
            }
            if (p == "wt")
            {
                if(matr[i-1, j] == "c")
                    wasCarrot = true;
                DrawCell(i - 1, j, "WolfTop.bmp",  "wt");
                return;
            }
            if (p == "wb")
            {
                if(matr[i+1, j] == "c")
                    wasCarrot = true;
                DrawCell(i + 1, j, "WolfBottom.bmp", "wb");
                return;
            }
        }

		public void Sleep( )
		{
			for (int i = 0; i < 10; i++)
			{
				Thread.Sleep(10);
				Application.DoEvents();
			}
		}
        #endregion


        #region "Условия"
        public IntPtr IsCarrotElse()
		{
            Index ind = Find("c");
            if(ind.i == -1)
			    return new IntPtr(0);
			return new IntPtr(1);
		}

        public IntPtr IsRabbitWolfTogether()
        {
            Index ind = Find("r");
            if (ind.i == -1)
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsRabbitEaten()
        {
            Index ind = Find("r");
            if (ind != null)
                return new IntPtr(0);
            return new IntPtr(1);
        }

		public IntPtr IsCarrotRight()
		{
            Index ind = new Index(); 
            ind = Find("r");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "rr")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rl")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rt")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rb")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1] == "c")
                        return new IntPtr(1);
                }
            }
			return new IntPtr(0);
		}

        public IntPtr IsCarrotLeft()
        {
            Index ind = new Index();
            ind = Find("r");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "rr")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rl")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rt")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rb")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1] == "c")
                        return new IntPtr(1);
                }
            }
            return new IntPtr(0);
        }

        public IntPtr IsCarrotInFront()
        {
            Index ind = new Index();
            ind = Find("r");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "rr")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rl")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rt")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j] == "c")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "rb")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j] == "c")
                        return new IntPtr(1);
                }
            }
            return new IntPtr(0);
        }

        public IntPtr IsRabbitRight()
        {
            Index ind = new Index();
            ind = Find("w");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "wr")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wl")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wt")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wb")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            return new IntPtr(0);
        }

        public IntPtr IsRabbitLeft()
        {
            Index ind = new Index();
            ind = Find("w");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "wr")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wl")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wt")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wb")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            return new IntPtr(0);
        }

        public IntPtr IsRabbitInFront()
        {
            Index ind = new Index();
            ind = Find("w");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "wr")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wl")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wt")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wb")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            return new IntPtr(0);
        }

        public IntPtr IsRabbitBack()
        {
            Index ind = new Index();
            ind = Find("w");
            int i = ind.i;
            int j = ind.j;
            if (matr[i,j] == "wr")
            {
                if (j - 1 >= 0)
                {
                    if (matr[i, j - 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wl")
            {
                if (j + 1 < 10)
                {
                    if (matr[i, j + 1].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wt")
            {
                if (i + 1 < 10)
                {
                    if (matr[i + 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            if (matr[i, j] == "wb")
            {
                if (i - 1 >= 0)
                {
                    if (matr[i - 1, j].Substring(0, 1) == "r")
                        return new IntPtr(1);
                }
            }
            return new IntPtr(0);
        }

        private bool IsWallInFront(string who)
        {
            Index ind = new Index();
            ind = Find(who);
            int i = ind.i;
            int j = ind.j;
            if (matr[i, j] == who + "r")
            {
                if ((j + 1 > 9) || (matr[i, j + 1] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "l")
            {
                if ((j - 1 < 0) || (matr[i, j - 1] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "t")
            {
                if ((i - 1 < 0) || (matr[i - 1, j] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "b")
            {
                if ((i + 1 > 9) || (matr[i + 1, j] == "f"))
                    return true;
            }
            return false;
        }

        public IntPtr IsWallInFrontRabbit()
        {
            if (IsWallInFront("r"))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsWallInFrontWolf()
        {
            if (IsWallInFront("w"))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        private bool IsWallRight(string who)
        {
            Index ind = new Index();
            ind = Find(who);
            int i = ind.i;
            int j = ind.j;
            if (matr[i, j] == who + "r")
            {
                if ((i + 1 > 9) || (matr[i + 1, j] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "l")
            {
                if ((i-1 < 0) || (matr[i - 1, j] == "f"))
                    return true;
            }
            if ((matr[i, j] == who + "t"))
            {
                if ((j + 1 > 9) || matr[i, j + 1] == "f")
                    return true;
            }
            if (matr[i, j] == who + "b")
            {
                if ((j-1 < 0) || (matr[i, j - 1] == "f"))
                    return true;
            }
            return false;
        }

        public IntPtr IsWallRightRabbit()
        {
            if (IsWallRight("r"))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsWallRightWolf()
        {
            if (IsWallRight("w"))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        private bool IsWallLeft(string who)
        {
            Index ind = new Index();
            ind = Find(who);
            int i = ind.i;
            int j = ind.j;
            
            //// Это добавил я, может надо по другому!..
            //if(( i == 0) || ( j == 0))
            //    return false;
            
            if (matr[i, j] == who + "r")
            {
                if ((i - 1 < 0) || (matr[i - 1, j] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "l")
            {
                if ((i + 1 > 9) || (matr[i + 1, j] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "t")
            {
                if ((j - 1 < 0) || (matr[i, j - 1] == "f"))
                    return true;
            }
            if (matr[i, j] == who + "b")
            {
                if ((j + 1 > 9) || (matr[i, j + 1] == "f"))
                    return true;
            }
            return false;
        }

        public IntPtr IsWallLeftRabbit()
        {
            if (IsWallLeft("r"))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsWallLeftWolf()
        {
            if (IsWallLeft("w"))
                return new IntPtr(1);
            return new IntPtr(0);
        }

		public IntPtr IsReady()
		{
			if (start)
				return new IntPtr(1);
			return new IntPtr(0);
		}

        #endregion

		private void button1_Click(object sender, EventArgs e)
		{
			ind = Convert.ToInt32(comboBox1.SelectedItem);
			start = true;
		}
    }
}
