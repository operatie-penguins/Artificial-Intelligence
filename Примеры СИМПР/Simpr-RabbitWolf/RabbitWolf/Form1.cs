using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RabbitWolf
{
	public partial class Form1 : Form
	{
		string[,] matr;
		//MyHookClass mhk;

		public Form1( )
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			
			matr = new string[10, 10]
			    {   {"0", "0", "0", "c", "0", "0", "w", "0", "0", "wb"} ,
					{"0", "0", "w", "0", "0", "0", "0", "c", "0", "0"} ,
					{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"} ,
					{"0", "0", "0", "w", "0", "0", "0", "0", "c", "0"} ,
					{"w", "0", "c", "0", "0", "0", "0", "w", "0", "c"} ,
					{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"} ,
					{"0", "0", "0", "0", "w", "c", "0", "0", "0", "0"} ,
					{"0", "0", "0", "0", "0", "0", "0", "0", "0", "w"} ,
					{"c", "w", "0", "w", "0", "0", "0", "0", "c", "0"} ,
					{"rt", "0", "w", "0", "0", "0", "0", "0", "w", "0"}
			    };

			LoadTable();
			//mhk = new MyHookClass(this);
		}

		private void LoadTable()
		{
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
						if (s == "w")
							dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Wall.bmp");
					}
				}
			}

			dataGridView1.Rows[9].Cells[0].Value = new Bitmap("RabbitTop.bmp");
			dataGridView1.Rows[0].Cells[9].Value = new Bitmap("WolfBottom.bmp");
		}

		private void DrawCell(int rowIndex, int columnIndex, string pict, string pologenie)
		{
			dataGridView1.Rows[rowIndex].Cells[columnIndex].Value = new Bitmap(pict);
			matr[rowIndex, columnIndex] = pologenie;
		}

		private void TurnLeft(int rowIndex, int columnIndex, bool rb)
		{
			if (rb)
				DrawCell(rowIndex, columnIndex, "RabbitLeft.bmp", "rl");
			else
				DrawCell(rowIndex, columnIndex, "WolfLeft.bmp", "wl");
		}

		private void TurnRight(int rowIndex, int columnIndex, bool rb)
		{
			if (rb)
				DrawCell(rowIndex, columnIndex, "RabbitRight.bmp", "rr");
			else
				DrawCell(rowIndex, columnIndex, "WolfRight.bmp", "wr");
		}

		private void TurnBack(int rowIndex, int columnIndex, bool rb)
		{
			// или вверх или вниз
			string p = matr[rowIndex, columnIndex];
			if (p.Substring(0, 1) == "r")
			{
				if (p == "rl")
					DrawCell(rowIndex, columnIndex, "RabbitRight.bmp", "rr");
				if (p == "rr")
					DrawCell(rowIndex, columnIndex, "RabbitLeft.bmp", "rl");
				if (p == "rt")
					DrawCell(rowIndex, columnIndex, "RabbitBottom.bmp", "rb");
				if (p == "rb")
					DrawCell(rowIndex, columnIndex, "RabbitTop.bmp", "rt");
			}
			else
			{
				if (p == "wl")
					DrawCell(rowIndex, columnIndex, "WolfRight.bmp", "wr");
				if (p == "wr")
					DrawCell(rowIndex, columnIndex, "WolfLeft.bmp", "wl");
				if (p == "wt")
					DrawCell(rowIndex, columnIndex, "WolfBottom.bmp", "wb");
				if (p == "wb")
					DrawCell(rowIndex, columnIndex, "WolfTop.bmp", "wt");
			}
		}

		private void Step(int rowIndex, int columnIndex, bool rb)
		{
			string p = matr[rowIndex, columnIndex];
			if (p.Substring(0, 1) == "r")
			{
				DrawCell(rowIndex, columnIndex, "Grass.bmp", "0");
				if (p == "rl")
				{
					DrawCell(rowIndex, columnIndex - 1, "RabbitLeft.bmp", "rl");
					matr[rowIndex, columnIndex] = "0";
				}
				if (p == "rr")
				{
					DrawCell(rowIndex, columnIndex + 1, "RabbitRight.bmp", "rr");
					matr[rowIndex, columnIndex] = "0";
				}
				if (p == "rt")
				{
					DrawCell(rowIndex - 1, columnIndex, "RabbitTop.bmp", "rt");
					matr[rowIndex, columnIndex] = "0";
				}
				if (p == "rb")
				{
					DrawCell(rowIndex + 1, columnIndex, "RabbitBottom.bmp", "rb");
					matr[rowIndex, columnIndex] = "0";
				}
			}
			else
			{
				DrawCell(rowIndex, columnIndex, "Grass.bmp", "0");
				if (p == "wl")
				{
					DrawCell(rowIndex, columnIndex - 1, "WolfLeft.bmp", "wl");
					matr[rowIndex, columnIndex] = "0";
				}
				if (p == "wr")
				{
					DrawCell(rowIndex, columnIndex + 1, "WolfRight.bmp", "wr");
					matr[rowIndex, columnIndex] = "0";
				}
				if (p == "wt")
				{
					DrawCell(rowIndex - 1, columnIndex, "WolfTop.bmp", "wt");
					matr[rowIndex, columnIndex] = "0";
				}
				if (p == "wb")
				{
					DrawCell(rowIndex + 1, columnIndex, "WolfBottom.bmp", "wb");
					matr[rowIndex, columnIndex] = "0";
				}
			}
		}

		private string Pologenie(int rowIndex, int columnIndex)
		{
			string p = matr[rowIndex, columnIndex];
			if (p.Substring(0, 1) == "r")
			{
				if (p == "rr")
					return "rr";
				if (p == "rl")
					return "rl";
				if (p == "rt")
					return "rt";
				if (p == "rb")
					return "rb";
			}
			else
			{
				if (p == "wr")
					return "wr";
				if (p == "wl")
					return "wl";
				if (p == "wt")
					return "wt";
				if (p == "wb")
					return "wb";
			}
			return "";
		}

		public IntPtr IsCarrotElse()
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					string s = matr[i, j];
					if (s != "c")
						return new IntPtr(1);
				}
			}
			return new IntPtr(0);
		}

		public IntPtr IsCarrotRight( )
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					string p = matr[i, j];
					if (p.Substring(0, 1) == "r")
					{
						if (p == "rr")
						{
							if (matr[i+1, j] == "c")
								new IntPtr(1);
						}
						if (p == "rl")
						{
							if (matr[i-1, j] == "c")
								new IntPtr(1);
						}
						if (p == "rt")
						{
							if (matr[i, j+1] == "c")
								new IntPtr(1);
						}
						if (p == "rb")
						{
							if (matr[i, j-1] == "c")
								new IntPtr(1);
						}
					}
				}
				break;
			}
			return new IntPtr(0);
		}
	}
}
