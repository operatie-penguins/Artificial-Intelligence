using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace myProject
{
    public partial class Form1 : Form
    {
        string[,] matr;
        int number;
        int[,] clients;
        string current = "m";
        int order = -1;
        int card = 7;
        mySimprClass mySimpr;
        Random random = new Random();

        public class Index
        {
            public int i;
            public int j;
        }

        public Form1()
        {
            InitializeComponent();
            mySimpr = new mySimprClass(this);
            blockTextBox.Text = " ";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            matr = new string[10, 10]
			    {   {"f1", "s1", "f2", "mr3", "mr4", "mr4", "mr4", "mr4", "mr4", "mr5"} ,
					{"f4", "cb", "cb", "mr8", "mb", "mb", "c1", "c2", "c3", "mr7"} ,
					{"f3", "cb", "cb", "m", "mb", "mb", "mb", "mb", "mb", "mr7"} ,
					{"f4", "cb", "cb", "mr8", "mb", "mb", "c1", "c2", "c3", "mr7"} ,
					{"f3", "cb", "cb", "mr2", "mr1", "mr1", "mr1", "mr1", "mr1", "mr6"} ,
					{"f4", "cb", "cb", "s10", "s1", "s1", "s1", "s5", "s5", "s7"} ,
					{"f3", "cb", "cb", "cb", "cb", "cb", "cb", "b1", "b4", "s4"} ,
					{"f4", "cb", "cb", "cb", "cb", "cb", "cb", "b2", "b3", "s4"} ,
					{"f", "cb", "cb", "s6", "s2", "s2", "s2", "s3", "s3", "s8"} ,
					{"z", "cb", "cb", "z", "z", "z", "z", "z", "z", "z"}
			    };
            LoadTable();
            LoadClients();
        }
        private int RandomNumber(int min, int max)
        {
            Thread.Sleep(1);
            return random.Next(min, max);
        }
        public void LoadClients()
        {
            number = RandomNumber(10, 15);
            blockTextBox.Text = "Всего будет клиентов : " + number.ToString() + "\r\n";
            int k = 0;
            int l = 0;
            clients = new int[number, 7];
            for (int i = 0; i < number; i++)
            {
                clients[i, 0] = -1;
                clients[i, 1] = -1;
                clients[i, 2] = RandomNumber(-1, 2);
                if (clients[i, 2] == 2)
                {
                    clients[i, 2] = 1;
                }
                if (clients[i, 2] == -1)
                {
                    clients[i, 2] = 0;
                }
                if (clients[i, 2] == 1)
                {
                    k += 1;
                    clients[i, 3] = 1;
                }
                else
                {
                    clients[i, 3] = RandomNumber(0, 2);
                    if (clients[i, 3] == 2)
                    {
                        clients[i, 3] = 1;
                    }
                    if (clients[i, 3] == -1)
                    {
                        clients[i, 3] = 0;
                    }
                }
                if (clients[i, 3] == 1)
                    l += 1;

                clients[i, 4] = 0;
                clients[i, 5] = 0;
                clients[i, 6] = 0;
            }
            blockTextBox.Text += "Всего клиентов,которые знают,что карта готова : " + k.ToString() + "\r\n";
            blockTextBox.Text += "Всего готовых карт : " + l.ToString() + "\r\n";
        }

        public void LoadTable()
        {
            dataGridView1.Rows.Add(10);
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    string s = matr[i, j];
                    switch (s)
                    {
                        case "cb":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("back.jpg");
                            break;
                        case "z":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Out.jpg");
                            break;
                        case "s1":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa1.jpg");
                            break;
                        case "s2":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa2.jpg");
                            break;
                        case "s3":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa3.jpg");
                            break;
                        case "s4":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa4.jpg");
                            break;
                        case "s5":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa5.jpg");
                            break;
                        case "s6":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa6.jpg");
                            break;
                        case "s7":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa7.jpg");
                            break;
                        case "s8":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa8.jpg");
                            break;
                        case "s10":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Sofa10.jpg");
                            break;
                        case "mb":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("manBack.jpg");
                            break;
                        case "f":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Flowers.jpg");
                            break;
                        case "f1":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Flowers1.jpg");
                            break;
                        case "f2":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Flowers2.jpg");
                            break;
                        case "f3":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Flowers3.jpg");
                            break;
                        case "f4":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Flowers4.jpg");
                            break;
                        case "c1":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Cards1.jpg");
                            break;
                        case "c2":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Cards2.jpg");
                            break;
                        case "c3":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Cards3.jpg");
                            break;
                        case "mr1":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom1.jpg");
                            break;
                        case "mr2":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom2.jpg");
                            break;
                        case "mr3":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom3.jpg");
                            break;
                        case "mr4":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom4.jpg");
                            break;
                        case "mr5":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom5.jpg");
                            break;
                        case "mr6":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom6.jpg");
                            break;
                        case "mr7":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom7.jpg");
                            break;
                        case "mr8":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRoom8.jpg");
                            break;
                        case "b1":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Base1.jpg");
                            break;
                        case "b2":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Base2.jpg");
                            break;
                        case "b3":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Base3.jpg");
                            break;
                        case "b4":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Base4.jpg");
                            break;
                        case "m":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("Manager.jpg");
                            break;
                        case "mr":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerRight.jpg");
                            break;
                        case "mlc":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerLeftCard.jpg");
                            break;
                        case "mc":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ManagerCard.jpg");
                            break;
                        case "cup":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientUp.jpg");
                            break;
                        case "cupk":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientUpKnow.jpg");
                            break;
                        case "cr":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientRight.jpg");
                            break;
                        case "cl":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientLeft.jpg");
                            break;
                        case "clc":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientLeftCard.jpg");
                            break;
                        case "clk":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientLeftKnow.jpg");
                            break;
                        case "cd":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientDown.jpg");
                            break;
                        case "cdc":
                            dataGridView1.Rows[i].Cells[j].Value = new Bitmap("ClientDownCard.jpg");
                            break;
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
                    if (matr[i, j] == who)
                    {
                        ind.i = i;
                        ind.j = j;
                    }
                }
            }
            return ind;
        }
        public void GoToTheNext()
        {
            if (current == "m")
            {
                order += 1;
                if (order < number)
                {
                    if (clients[order, 6] != 1)
                    {
                        current = "c";
                    }
                    else
                    {
                        bool fl = true;
                        int i = 0;
                        while ((fl) & (i < number))
                        {
                            if (clients[order, 6] == 0)
                            { fl = false; }
                            i++;
                        }
                        if (fl)
                        { current = "m"; }
                        else
                        {
                            GoToTheNext();
                        }
                    }
                }
                else
                {
                    order = -1;
                    GoToTheNext();
                }

            }
            else
            {
                current = "m";
            }
            return;
        }
        //Действия сотрудника банка
        public void WaitClient()
        {
            matr[2, 3] = "m";
            DrawCell(2, 3, "Manager.jpg", "m");
            return;
        }
        public void ManagerGoToTheRight()
        {
            Index ind = Find("mr");
            if ((ind.i == -1) & (ind.j == -1))
            {
                ind = Find("m");
                DrawCell(ind.i, ind.j, "Right.jpg", "01");
                int k = ind.j + 1;
                DrawCell(ind.i, k, "ManagerRight.jpg", "mr");
                return;
            }
            else
            {
                DrawCell(ind.i, ind.j, "manBack.jpg", "mb");
                int k = ind.j + 1;
                DrawCell(ind.i, k, "ManagerRight.jpg", "mr");
                return;
            }
        }
        public void ManagerGoToTheLeft()
        {
            Index ind = Find("mlc");
            DrawCell(ind.i, ind.j, "manBack.jpg", "mb");
            int k = ind.j - 1;
            DrawCell(ind.i, k, "ManagerLeftCard.jpg", "mlc");
            return;
        }
        public void GetCard()
        {
            Index ind = Find("mr");
            DrawCell(ind.i, ind.j, "ManagerLeftCard.jpg", "mlc");
            return;

        }
        public void ReturnCard()
        {
            Index ind = Find("mlc");
            DrawCell(ind.i, ind.j, "manBack.jpg", "mb");
            int k = ind.j - 1;
            DrawCell(ind.i, k, "ManagerCard.jpg", "mc");
            card = RandomNumber(5, 7);
            return;
        }
        //Действия клиента
        public void GoToTheBank()
        {
            if (clients[order, 2] == 0)
            {
                DrawCell(9, 2, "ClientUp.jpg", "cup");
                Thread.Sleep(25);
                DrawCell(9, 2, "back.jpg", "cb");
                DrawCell(8, 2, "ClientUp.jpg", "cup");
                Thread.Sleep(70);
                DrawCell(8, 2, "back.jpg", "cb");
                DrawCell(7, 2, "ClientUp.jpg", "cup");
                clients[order, 1] = 2;
                clients[order, 0] = 7;
                clients[order, 5] = 1;
                return;
            }
            else
            {
                DrawCell(9, 2, "ClientUpKnow.jpg", "cupk");
                clients[order, 0] = 9;
                clients[order, 1] = 2;
                clients[order, 5] = 1;
                return;
            }
        }
        public void GoBackWithCard()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            i = i + 1;
            DrawCell(i, j, "ClientDownCard.jpg", "cdc");
            clients[order, 0] = i;
            return;
        }
        public void GoBackWithoutCard()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            i = i + 1;
            DrawCell(i, j, "ClientDown.jpg", "cd");
            clients[order, 0] = i;
            return;
        }
        public void ExitTheBank()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            clients[order, 6] = 1;
            clients[order, 5] = 1;
            if (clients[order, 3] == 1)
            { blockTextBox.Text += "Вышел клиент №  " + order.ToString() + " c картой \r\n"; }
            else
            {
                blockTextBox.Text += "Всего клиент №  " + order.ToString() + " без карты \r\n";
            }
            return;
        }
        //Действия клиента,который знает,что карта готова
        public void GoToTheUp()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            i = i - 1;
            DrawCell(i, j, "ClientUpKnow.jpg", "cupk");
            clients[order, 0] = i;
            return;
        }
        public void WaitManager()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            clients[order, 4] = 2;
            DrawCell(i, j, "ClientRight.jpg", "cr");
            return;
        }
        public void GoToTheLeftCard()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            j = j - 1;
            DrawCell(i, j, "ClientLeftCard.jpg", "clc");
            clients[order, 1] = j;
            return;
        }
        public void GoToTheExitCard()
        {
            clients[order, 4] = 1;
            DrawCell(2, 3, "Manager.jpg", "m");
            return;
        }
        //Действия клиента,который не знает,что карта готова
        public void ClientGoToTheRight()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            j = j + 1;
            DrawCell(i, j, "ClientRight.jpg", "cr");
            clients[order, 1] = j;
            return;
        }
        public void ClientGoToTheUp()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            i = i - 1;
            DrawCell(i, j, "ClientUp.jpg", "cup");
            clients[order, 0] = i;
            return;
        }
        public void ClientGoToTheLeftKnow()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            j = j - 1;
            DrawCell(i, j, "ClientLeftKnow.jpg", "clk");
            clients[order, 1] = j;
            return;
        }
        public void ClientGoToTheLeft()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            DrawCell(i, j, "back.jpg", "cb");
            j = j - 1;
            DrawCell(i, j, "ClientLeft.jpg", "cl");
            clients[order, 1] = j;
            return;
        }
        public void GoBackWithoutDocs()
        {
            clients[order, 3] = 0;
            clients[order, 4] = 1;
        }
        public void GoToTheManager()
        {
            //      clients[order,3] = 1;
            DrawCell(clients[order,0], clients[order,1], "ClientUpKnow.jpg", "cupk");
            clients[order, 2] = 1;
        }
        #endregion

        #region "Условия"
        //-------Таблица1-------
        public IntPtr IsCurrentManager()
        {
            if (current != "m")
                return new IntPtr(0);
            return new IntPtr(1);

        }
        public IntPtr IsCurrentClient()
        {
            if (current != "c")
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsAll()
        {
            bool fl = true;
            int i = 0;
            while ((fl) && (i < number))
            {
                if (clients[i, 6] == 0)
                    fl = false;
                i++;
            }
            if (fl)
            { MessageBox.Show("Все клиенты вышли из банка."); }
            if (fl)
                return new IntPtr(1);
            return new IntPtr(0);
        }
        //-------Таблица2-------
        public IntPtr IsWaitClient()
        {
            if (order == -1)
            {
                return new IntPtr(1);
            }
            else
            {
                Index ind = Find("m");
                if (((ind.i != 2) || (ind.j != 3)) & (clients[order, 4] != 3))
                    return new IntPtr(0);
                return new IntPtr(1);
            }
        }
        public IntPtr IsCameClient()
        {
            if (order == -1)
            {
                return new IntPtr(0);
            }
            else
            {
                int i = clients[order, 0];
                int j = clients[order, 1];
                if ((i != 2) || (j != 2))
                    return new IntPtr(0);
                return new IntPtr(1);
            }
        }
        public IntPtr IsGoRight()
        {
            Index ind = Find("mr");
            if ((ind.i == -1) & (ind.j == -1))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsGoLeft()
        {
            Index ind = Find("mlc");
            if ((ind.i == -1) & (ind.j == -1))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsWentToTheCards()
        {
            Index ind = Find("mr");
            if ((ind.i != 2) || (ind.j != card))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsWentToTheClient()
        {
            Index ind = Find("mlc");
            if ((ind.i != 2) || (ind.j != 4))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        //-------Таблица3-------
        public IntPtr ClientInTheBank()
        {
            if (clients[order, 5] != 1)
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr CanComeInTheBank()
        {
            if ((matr[5, 2] != "cb") || (matr[7, 3] != "cb") || (matr[9, 2] != "cb") || (matr[8, 2] != "cb") || (matr[7, 2] != "cb"))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsKnownAboutCard()
        {
            if (clients[order, 2] == 0)
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsCardReady()
        {
            if (clients[order, 3] != 1)
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsGoToTheExit()
        {
            if (clients[order, 4] != 1)
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsWentToTheExit()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            if ((i != 8) || (j != 1))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        //-------Таблица4-------
        public IntPtr CanMakeStepUp()
        {
            int i = clients[order, 0] - 1;
            int j = clients[order, 1];
            if (matr[i, j] != "cb")
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsComeToTheManager()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            if ((i != 2) || (j != 2))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsWaitManager()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            if (((i != 2) || (j != 2)) || (clients[order, 4] != 2))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsManagerReturn()
        {
            Index ind = Find("mc");
            if ((ind.i != 2) || (ind.j != 3))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        //-------Таблица5-------
        public IntPtr CanMakeStepRight()
        {
            int i = clients[order, 0];
            int j = clients[order, 1] + 1;
            if (matr[i, j] != "cb")
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsWentToTheDocs()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            if ((i != 7) || (j != 5))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsGoBackTo_()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            if ((matr[i, j] != "cl") & (matr[i, j] != "clk"))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr CanMakeStepLeft()
        {
            int i = clients[order, 0];
            int j = clients[order, 1] - 1;
            if (matr[i, j] != "cb")
                return new IntPtr(0);
            return new IntPtr(1);
        }
        public IntPtr IsWentTo_()
        {
            int i = clients[order, 0];
            int j = clients[order, 1];
            if ((i != 6) || (j != 2))
                return new IntPtr(0);
            return new IntPtr(1);
        }
        #endregion

    }
}