using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Threading;

namespace LabaOne
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Init();
        }

        MyHookClass mhk;
        int stackLength;
        int timeOut = 40;
        bool isStarting;

        private void Init()
        {
            SizeF sizeStack = CreateGraphics().MeasureString("1", txtStack1.Font);
            stackLength = txtStack1.Height / (int)sizeStack.Height;
            txtStack1.Lines = new string[stackLength - 1];
            txtStack2.Lines = new string[stackLength - 1];
            isStarting = false;
            comboBox1.Text = timeOut.ToString();
            label1.Text = String.Empty;
            label2.Text = String.Empty;
            label3.Text = String.Empty;
            op1 = op2 = null;
        }

        private string getLeftInput(TextBox txt)
        {
            if (txt.Text.Length == 0)
                return "";

            string c = txt.Text.Substring(0, 1);
            string text = txt.Text.Substring(1, txt.TextLength - 1);

            SizeF size;
            do
            {
                c += " ";
                txt.Text = c + text;
                Thread.Sleep(timeOut);
                Application.DoEvents();
                size = CreateGraphics().MeasureString(txt.Text + "_", txt.Font);
            }
            while (txt.Width > (int)size.Width);

            txt.Text = text;

            return c.Substring(0, 1);
        }

        private string getRightInput(TextBox txt)
        {
            Thread.Sleep(timeOut);

            if (txt.Text.Length == 0)
                return "";

            string c = txt.Text.Substring(0, 1);
            txt.Text = txt.Text.Substring(1, txt.Text.Length - 1);
            return c;
        }

        private string getIntoStack(TextBox txt)
        {
            int up = 0;

            for (int i = 0; i < txt.Lines.Length; i++)
            {
                if (txt.Lines[i] != "")
                {
                    up = i;
                    break;
                }
            }

            string c = txt.Lines[up];
            string[] s = null;

            for (int i = up; i >= 0; i--)
            {
                s = txt.Lines;
                s[i] = "";

                if (i > 0)
                    s[i - 1] = c;

                txt.Lines = s;
                Thread.Sleep(timeOut);
                Application.DoEvents();
            }

            return c;
        }

        private void putIntoStack(TextBox txt, string c)
        {
            if (txt.Lines[0] != "")
            {
                stackLength++;
                string[] s = new string[stackLength];
                for (int i = 0; i < txt.Lines.Length; i++)
                    s[i + 1] = txt.Lines[i];
                s[0] = c;
                txt.Lines = s;
                return;
            }

            for (int i = 0; i < txt.Lines.Length; i++)
            {
                string[] s = txt.Lines;

                if (s[i] == "")
                {
                    s[i] = c;

                    if (i > 0)
                        s[i - 1] = "";

                    txt.Lines = s;
                    Thread.Sleep(timeOut);
                    Application.DoEvents();
                }
            }
        }

        private void putRightInput(TextBox txt, string c)
        {
            if (c == "") return;

            SizeF sizeRes = CreateGraphics().MeasureString("_" + txt.Text + "_", txt.Font);
            string c1 = "";
            while (txt.Width > (int)sizeRes.Width)
            {
                c1 += " ";
                sizeRes = CreateGraphics().MeasureString("_" + c1 + "_", txt.Font);
            }

            string startText = txt.Text;

            int n1 = c1.Length;
            for (int i = 0; i <= n1; i++)
            {
                txt.Text = startText + c1 + c;
                Thread.Sleep(timeOut);
                Application.DoEvents();

                if (c1 == " ")
                {
                    c1 = "";
                }
                else if (c1.Length > 0)
                {
                    c1 = c1.Substring(0, c1.Length - 1);
                }
            }
        }

        #region К таблице 1

        public IntPtr IsInputNumeral()
        {
            if( txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (Char.IsDigit(txtInput.Text, 0))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputOpenStaple()
        {
            if (txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (txtInput.Text.Substring(0, 1) == "(")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputCloseStaple()
        {
            if (txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (txtInput.Text.Substring(0, 1) == ")")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputPlus()
        {
            if (txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (txtInput.Text.Substring(0, 1) == "+")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputMinus()
        {
            if (txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (txtInput.Text.Substring(0, 1) == "-")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputMultiply()
        {
            if (txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (txtInput.Text.Substring(0, 1) == "*")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputDiv()
        {
            if (txtInput.Text.Length == 0)
                return new IntPtr(0);

            if (txtInput.Text.Substring(0, 1) == "/")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsInputEmpty()
        {
            if (txtInput.Text == "")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsStack1OpenStaple()
        {
            for (int i = 0; i < txtStack1.Lines.Length; i++)
            {
                if (txtStack1.Lines[i] == "(")
                    return new IntPtr(1);

                if (txtStack1.Lines[i] != "")
                    break;
            }

            return new IntPtr(0);
        }

        public IntPtr IsStack1Plus()
        {
            for (int i = 0; i < txtStack1.Lines.Length; i++)
            {
                if (txtStack1.Lines[i] == "+")
                    return new IntPtr(1);

                if (txtStack1.Lines[i] != "")
                    break;
            }

            return new IntPtr(0);
        }

        public IntPtr IsStack1Multiply()
        {
            for (int i = 0; i < txtStack1.Lines.Length; i++)
            {
                if (txtStack1.Lines[i] == "*")
                    return new IntPtr(1);

                if (txtStack1.Lines[i] != "")
                    break;
            }

            return new IntPtr(0);
        }

        public IntPtr IsStack1Minus()
        {
            for (int i = 0; i < txtStack1.Lines.Length; i++)
            {
                if (txtStack1.Lines[i] == "-")
                    return new IntPtr(1);

                if (txtStack1.Lines[i] != "")
                    break;
            }

            return new IntPtr(0);
        }

        public IntPtr IsStack1Div()
        {
            for (int i = 0; i < txtStack1.Lines.Length; i++)
            {
                if (txtStack1.Lines[i] == "/")
                    return new IntPtr(1);

                if (txtStack1.Lines[i] != "")
                    break;
            }

            return new IntPtr(0);
        }

        public IntPtr IsStack1Empty()
        {
            for (int i = 0; i < txtStack1.Lines.Length; i++)
            {
                if (txtStack1.Lines[i] != "")
                    return new IntPtr(0);
            }

            return new IntPtr(1);
        }

        public IntPtr IsStarting()
        {
            if (isStarting)
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsSaveInput()
        {
            if (label1.Text.Length == 0)
                return new IntPtr(0);
            return new IntPtr(1);
        }

        public IntPtr IsSaveRes1()
        {
            if (label2.Text.Length == 0)
                return new IntPtr(0);
            return new IntPtr(1);
        }

        public void Sleep()
        {
            for (int i = 0; i < 10; i++)
            {
                Thread.Sleep(10);
                Application.DoEvents();
            }
        }

        public void WriteInputToRes1()
        {
            string s = getLeftInput(txtInput);
            putRightInput(txtRes1, s);
        }

        public void WriteInputToStack1()
        {
            string s = getLeftInput(txtInput);
            putIntoStack(txtStack1, s);
        }

        public void WriteStack1ToRes()
        {
            string s = getIntoStack(txtStack1);
            putRightInput(txtRes1, s);
        }

        public void DeleteStamp()
        {
            getLeftInput(txtInput);
            getIntoStack(txtStack1);
        }

        public void SaveInput()
        {
            label1.Text = "Start input is :" + Environment.NewLine + txtInput.Text;
        }

        public void SaveRes1()
        {
            label2.Text = "Postinfix result is :" + Environment.NewLine + txtRes1.Text;
        }

        #endregion

        #region К таблице 2

        int? op1;
        int? op2;

        public IntPtr IsRes1Empty()
        {
            if (txtRes1.Text.Length == 0)
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsRes1Numeral()
        {
            if (Char.IsDigit(txtRes1.Text, 0))
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsRes1Plus()
        {
            if (txtRes1.Text.Substring(0, 1) == "+")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsRes1Minus()
        {
            if (txtRes1.Text.Substring(0, 1) == "-")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsRes1Multiply()
        {
            if (txtRes1.Text.Substring(0, 1) == "*")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsRes1Div()
        {
            if (txtRes1.Text.Substring(0, 1) == "/")
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsStack2Empty()
        {
            for (int i = 0; i < txtStack2.Lines.Length; i++)
            {
                if (txtStack2.Lines[i] != "")
                    return new IntPtr(0);
            }

            return new IntPtr(1);
        }

        public IntPtr IsOp1Exist()
        {
            if (op1 != null)
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public IntPtr IsOp2Exist()
        {
            if (op2 != null)
                return new IntPtr(1);
            return new IntPtr(0);
        }

        public void WriteRes1ToStack2()
        {
            string s = getRightInput(txtRes1);
            putIntoStack(txtStack2, s);
        }

        public void GetOp1()
        {
            string s = getIntoStack(txtStack2);
            op1 = int.Parse(s);
        }

        public void GetOp2()
        {
            string s = getIntoStack(txtStack2);
            op2 = int.Parse(s);
        }

        public void SumOp1Op2()
        {
            string s = (op1 + op2).ToString();
            putIntoStack(txtStack2, s);
        }

        public void MinusOp1Op2()
        {
            string s = (op1 - op2).ToString();
            putIntoStack(txtStack2, s);
        }

        public void MultiplyOp1Op2()
        {
            string s = (op1 * op2).ToString();
            putIntoStack(txtStack2, s);
        }

        public void DivOp1Op2()
        {
            string s = (op1 / op2).ToString();
            putIntoStack(txtStack2, s);
        }

        public void ClearOp1Op2()
        {
            op1 = op2 = null;
        }

        public void ClearLeftCharInRes1()
        {
            getRightInput(txtRes1);
        }

        public void WriteResult()
        {
            string res = getIntoStack(txtStack2);
            putRightInput(txtRes2, res);
            label3.Text = "Result is:" + Environment.NewLine + res;
        }

        #endregion

        private void button1_Click(object sender, EventArgs e)
        {
            isStarting = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            timeOut = int.Parse(comboBox1.Items[comboBox1.SelectedIndex].ToString());
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            mhk = new MyHookClass(this);
        }
    }
}
