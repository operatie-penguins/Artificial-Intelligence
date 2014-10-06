using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace LabaOne
{
    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        uint simpr;
        Form1 f;

        public MyHookClass(Form1 af)
        {
            simpr = RegisterWindowMessage("msg_LabaOne");
            this.AssignHandle(af.Handle);
            f = af;
        }

        protected override void WndProc(ref Message m)
        {
            int wparamhi, wparamlo, wparam;
            int lParam = Convert.ToInt32("" + m.LParam);

            if (m.Msg == simpr)
            {
                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;


                #region Условия
                if (wparamhi == 0)
                {
                    if (wparamlo == 1) // Таблица 1 
                    {
                        switch (lParam)
                        {
                            case (1): m.Result = f.IsStarting(); break;
                            case (2): m.Result = f.IsInputNumeral(); break;
                            case (3): m.Result = f.IsInputOpenStaple(); break;
                            case (4): m.Result = f.IsInputCloseStaple(); break;
                            case (5): m.Result = f.IsInputPlus(); break;
                            case (6): m.Result = f.IsInputMinus(); break;
                            case (7): m.Result = f.IsInputMultiply(); break;
                            case (8): m.Result = f.IsInputDiv(); break;
                            case (9): m.Result = f.IsInputEmpty(); break;
                            case (10): m.Result = f.IsStack1OpenStaple(); break;
                            case (11): m.Result = f.IsStack1Plus(); break;
                            case (12): m.Result = f.IsStack1Minus(); break;
                            case (13): m.Result = f.IsStack1Multiply(); break;
                            case (14): m.Result = f.IsStack1Div(); break;
                            case (15): m.Result = f.IsStack1Empty(); break;
                            case (16): m.Result = f.IsSaveInput(); break;
                            case (17): m.Result = f.IsSaveRes1(); break;
                        }
                    }
                    else if (wparam == 2) // Таблица 2 
                    {
                        switch (lParam)
                        {
                            case (1): m.Result = f.IsRes1Empty(); break;
                            case (2): m.Result = f.IsRes1Numeral(); break;
                            case (3): m.Result = f.IsRes1Plus(); break;
                            case (4): m.Result = f.IsRes1Minus(); break;
                            case (5): m.Result = f.IsRes1Multiply(); break;
                            case (6): m.Result = f.IsRes1Div(); break;
                            case (7): m.Result = f.IsStack2Empty(); break;
                            case (8): m.Result = f.IsOp2Exist(); break;
                            case (9): m.Result = f.IsOp1Exist(); break;
                        }
                    }
                }
                #endregion
                #region Действия
                else if (wparamhi == 1)
                {
                    if (wparamlo == 1) // Таблица 1 
                    {
                        switch (lParam)
                        {
                            case (1): f.Sleep(); break;
                            case (2): f.SaveInput(); break;
                            case (3): f.WriteInputToRes1(); break;
                            case (4): f.WriteInputToStack1(); break;
                            case (5): f.WriteStack1ToRes(); break;
                            case (6): f.DeleteStamp(); break;
                            case (7): f.SaveRes1(); break;
                        }
                    }
                    else if (wparamlo == 2) // Таблица 2 
                    {
                        switch (lParam)
                        {
                            case (1): f.WriteRes1ToStack2(); break;
                            case (2): f.GetOp2(); break;
                            case (3): f.GetOp1(); break;
                            case (4): f.SumOp1Op2(); break;
                            case (5): f.MinusOp1Op2(); break;
                            case (6): f.MultiplyOp1Op2(); break;
                            case (7): f.DivOp1Op2(); break;
                            case (8): f.ClearOp1Op2(); break;
                            case (9): f.ClearLeftCharInRes1(); break;
                            case (10): f.WriteResult(); break;
                        }
                    }

                    m.Result = new IntPtr(1); // Ответом на запрос действия со стороны СИМПР должна быть единица

                }
                #endregion

                Application.DoEvents();
            }
            else
            {
                base.WndProc(ref m);
            }
        }
    }
}
