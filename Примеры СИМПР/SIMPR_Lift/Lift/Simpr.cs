using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace SIMPR 
{
    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);
        
        uint simpr;
        Kernel krn;
        BaseLift lift;
        public static bool stop = false;

        public MyHookClass(IntPtr hWnd)
        {
            simpr = RegisterWindowMessage("Message"); // регистрируем своё сообщение
            this.AssignHandle(hWnd);
            krn = new Kernel();
            krn.Start();
            lift = krn.lift;
//             human = krn.human;
        }
        BasePeople human
        {
            get { return krn.human; }
        }

        private IntPtr BoolPtr(bool term)
        {
            if (term) return new IntPtr(1);
            else return new IntPtr(0);
        }

        protected override void WndProc(ref Message m) 
        {
            try
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
                        if (wparamlo == 1) // Таблица 1 - управляющая
                        {
                            switch (lParam)  // Условия
                            {
                                case 1: m.Result = BoolPtr(krn.NeedAddHuman); break;
                                case 2: m.Result = BoolPtr(krn.IsLiftTurn);   break;
                                case 3: m.Result = BoolPtr(krn.NeedAddHuman); break;
                                case 4: m.Result = BoolPtr(BasePeople.Exist); break;
                            }
                        }
                        else if (wparamlo == 2) // Таблица 2 - лифт
                        {
                            switch (lParam)  // Условия
                            {
                                case 1: m.Result = BoolPtr(lift.IsIdle); break;
                                case 2: m.Result = BoolPtr(lift.IsMovingUp); break;
                                case 3: m.Result = BoolPtr(lift.IsMovingDown); break;
                                case 4: m.Result = BoolPtr(lift.IsDoorsOpen); break;
                                case 5: m.Result = BoolPtr(lift.IsGroundFloor); break;
                                case 6: m.Result = BoolPtr(lift.HaveTarget); break;
                                case 7: m.Result = BoolPtr(lift.IsTargetAbove); break;
                                case 8: m.Result = BoolPtr(lift.IsTargetBelow); break;
                                case 9: m.Result = BoolPtr(lift.IsTargetFloor); break;
                            }
                        }
                        else if (wparamlo == 3) // Таблица 3 - люди
                        {
                            switch (lParam)
                            {
                                case 1: m.Result = BoolPtr(human.isMadeCall); break;
                                case 2: m.Result = BoolPtr(human.NeedUp); break;
                                case 3: m.Result = BoolPtr(lift.IsMovingUp); break;
                                case 4: m.Result = BoolPtr(lift.IsIdle); break;
                                case 5: m.Result = BoolPtr(lift.IsDoorsOpen); break;
                                case 6: m.Result = BoolPtr(human.LiftInSameFloor); break;
                                case 7: m.Result = BoolPtr(human.InCar); break;
                                case 8: m.Result = BoolPtr(human.IsEndFloor); break;
                                case 9: m.Result = BoolPtr(human.HasArrived); break;
                            }
                        }

                        //  MessageBox.Show(m.Result.ToString());
                    }
                    #endregion
                    #region Действия
                    else if (wparamhi == 1)
                    {
                        //MessageBox.Show( wparamlo.ToString() + "|" + lParam.ToString());

                        if (wparamlo == 1) // Таблица 1
                        {
                            switch (lParam)
                            {
                                case 1: krn.AddHuman(); break;
                                case 2: krn.GetPeopleTurn(); break;
                                case 3: krn.GetLiftTurn(); break;
                            }
                        }

                        else if (wparamlo == 2) // Таблица 2
                        {
                            switch (lParam)
                            {
                                case 1: lift.Stay(); break;
                                case 2: lift.MoveUp(); break;
                                case 3: lift.MoveDown(); break;
                                case 4: lift.OpenDoors(); break;
                                case 5: lift.CloseDoors(); break;
                                case 6: lift.GetTarget(); break;
                            }
                        }
                        else if (wparamlo == 3) // Таблица 3
                        {
                            switch (lParam)
                            {
                                case 1: human.CallLift(); break;
                                case 2: human.Enter(); break;
                                case 3: human.Wait(); break;
                                case 4: human.Exit(); break;
                                case 5: human.GoAway(); break;
                                case 6: krn.NextHuman(); break;
                            }
                        }
                        m.Result = new IntPtr(1);
                    }
                    #endregion

                    Application.DoEvents();
                    System.Threading.Thread.Sleep(15);
                }
                else
                {
                    base.WndProc(ref m);
                }
            }
            catch (Exception exc)
            {
                Debug.WriteLine(exc.ToString() + "\n");
            }
        }
    }
}
