using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace myProject
{
    class mySimprClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        uint simpr;
        Form1 f;

        public mySimprClass(Form1 af)
        {
            simpr = RegisterWindowMessage("MyMessage");
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
                        switch (lParam)  // Условия
                        {
                            case (1): m.Result = f.IsCurrentManager(); break;
                            case (2): m.Result = f.IsCurrentClient(); break;
                            case (3): m.Result = f.IsAll(); break;
                        }
                    }
                    else if (wparam == 2) // Таблица 2 
                    {
                        switch (lParam)
                        {
                            case (1): m.Result = f.IsWaitClient(); break;
                            case (2): m.Result = f.IsCameClient(); break;
                            case (3): m.Result = f.IsGoRight(); break;
                            case (4): m.Result = f.IsGoLeft(); break;
                            case (5): m.Result = f.IsWentToTheCards(); break;
                            case (6): m.Result = f.IsWentToTheClient(); break;
                        }
                    }

                    else if (wparam == 3) // Таблица 3
                    {
                        switch (lParam)
                        {

                            case (1): m.Result = f.ClientInTheBank(); break;
                            case (2): m.Result = f.CanComeInTheBank(); break;
                            case (3): m.Result = f.IsKnownAboutCard(); break;
                            case (4): m.Result = f.IsCardReady(); break;
                            case (5): m.Result = f.IsGoToTheExit(); break;
                            case (6): m.Result = f.IsWentToTheExit(); break;
                        }
                    }

                    else if (wparam == 4) // Таблица 4
                    {
                        switch (lParam)
                        {
                            case (1): m.Result = f.CanMakeStepUp(); break;
                            case (2): m.Result = f.IsComeToTheManager(); break;
                            case (3): m.Result = f.IsWaitManager(); break;
                            case (4): m.Result = f.IsManagerReturn(); break;
                        }
                    }
                    else if (wparam == 5) // Таблица 5
                    {
                        switch (lParam)
                        {
                            case (1): m.Result = f.CanMakeStepRight(); break;
                            case (2): m.Result = f.IsWentToTheDocs(); break;
                            case (3): m.Result = f.IsCardReady(); break;
                            case (4): m.Result = f.IsGoBackTo_(); break;
                            case (5): m.Result = f.CanMakeStepLeft(); break;
                            case (6): m.Result = f.IsWentTo_(); break;
                        }
                    }


                                  }
                #endregion
                #region Действия
                else if (wparamhi == 1)
                {
                    if (wparamlo == 1) // Таблица 1 
                    {
                    }
                    else if (wparamlo == 2) // Таблица 2 
                    {
                        switch (lParam)
                        {
                            case (1): f.GoToTheNext(); break;
                            case (2): f.WaitClient(); break;
                            case (3): f.ManagerGoToTheRight(); break;
                            case (4): f.ManagerGoToTheLeft(); break;
                            case (5): f.GetCard(); break;
                            case (6): f.ReturnCard(); break;
                        }
                    }

                    else if (wparamlo == 3) // Таблица 3
                    {
                        switch (lParam)
                        {
                            case (1): f.GoToTheNext(); break;
                            case (2): f.GoToTheBank(); break;
                            case (3): f.GoBackWithCard(); break;
                            case (4): f.GoBackWithoutCard(); break;
                            case (5): f.ExitTheBank(); break;
                        }
                    }

                    else if (wparamlo == 4) // Таблица 4
                    {
                        switch (lParam)
                        {
                            case (1): f.GoToTheNext(); break;
                            case (2): f.GoToTheUp(); break;
                            case (3): f.WaitManager(); break;
                            case (4): f.GoToTheLeftCard(); break;
                            case (5): f.GoToTheExitCard(); break;
                        }
                    }
                    else if (wparamlo == 5) // Таблица 4
                    {
                        switch (lParam)
                        {
                            case (1): f.GoToTheNext(); break;
                            case (2): f.ClientGoToTheRight(); break;
                            case (3): f.ClientGoToTheUp(); break;
                            case (4): f.ClientGoToTheLeftKnow(); break;
                            case (5): f.ClientGoToTheLeft(); break;
                            case (6): f.GoBackWithoutDocs(); break;
                            case (7): f.GoToTheManager(); break;
                        }
                    }
                    System.Threading.Thread.Sleep(50);
                    //  Ответом на запрос действия со стороны СИМПР должна быть единица
                    m.Result = new IntPtr(1);

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
