using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace RabbitWolf 
{
    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);
        
        uint simpr;
        Form1 f;

        public MyHookClass(Form1 af)
        {
            simpr = RegisterWindowMessage("RabbitWolfMessage");
            this.AssignHandle(af.Handle);
            f = af;
        }

        protected override void WndProc(ref Message m) 
        {
            int wparamhi,wparamlo,wparam;
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
							case (1): m.Result = f.IsReady(); break;
						}
					}
                    else if (wparamlo == 2) // Таблица 2
                    {
                        switch (lParam)  // Условия
                        {
                            case (1): m.Result = f.IsCarrotElse(); break;
                            case (2): m.Result = f.IsCarrotInFront(); break;
                            case (3): m.Result = f.IsCarrotRight(); break;
                            case (4): m.Result = f.IsCarrotLeft(); break;
                            case (5): m.Result = f.IsRabbitEaten(); break;
                        }
                    }
                    else if (wparamlo == 3) // Таблица 3 
                        {
                            switch (lParam)
                            {
                                case (1): m.Result = f.IsRabbitRight(); break;
                                case (2): m.Result = f.IsRabbitLeft(); break;
                                case (3): m.Result = f.IsRabbitInFront(); break;
                                case (4): m.Result = f.IsRabbitBack(); break;
                                case (5): m.Result = f.IsRabbitWolfTogether(); break;
                            }
                        }

                        else if (wparamlo == 4) // Таблица 4
                        {
                            switch (lParam)
                            {
                                case (1): m.Result = f.IsWallInFrontRabbit(); break;
                                case (2): m.Result = f.IsWallRightRabbit(); break;
                                case (3): m.Result = f.IsWallLeftRabbit(); break;
                            }
                        }

                    else if (wparamlo == 5) // Таблица 5
                        {
                            switch (lParam)
                            {
                                case (1): m.Result = f.IsWallInFrontWolf(); break;
                                case (2): m.Result = f.IsWallRightWolf(); break;
                                case (3): m.Result = f.IsWallLeftWolf(); break;
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
							case (1): f.Sleep(); break;
						}
					}

                   else if (wparamlo == 2) // Таблица 2
                   {
                       switch (lParam)
                       {
                           case (1): f.TurnRightRabbit(); break;
                           case (2): f.TurnLeftRabbit(); break;
                           case (3): f.StepRabbit(); break;
                           case (4): f.TurnRightNotTurnRabbit(); break;
                           case (5): f.TurnLeftNotTurnRabbit(); break;
                           case (6): f.TurnLeftRightRabbit(); break;
                           case (7): f.TurnLeftRightNotTurnRabbit(); break;
                       }
                   }
                   else if (wparamlo == 3) // Таблица 3
                       {
                           switch (lParam)
                           {
                               case (1): f.TurnRightWolf(); break;
                               case (2): f.TurnLeftWolf(); break;
                               case (3): f.TurnBackWolf(); ; break;
                               case (4): f.StepWolf(); break;
                           }
                       }

                       else if (wparamlo == 4) // Таблица 4
                       {
                           switch (lParam)
                           {
                               case (1): f.TurnRightRabbit(); break;
                               case (2): f.TurnLeftRightRabbit(); break;
                               case (3): f.TurnLeftRabbit(); break;
                               case (4): f.StepRabbit(); break;
                               case (5): f.TurnBackRabbit(); break;
                               case (6): f.TurnLeftRightNotTurnRabbit(); break;
                               case (7): f.TurnLeftNotTurnRabbit(); break;
                               case (8): f.TurnRightNotTurnRabbit(); break;
                           }
                       }

                   else if (wparamlo == 5) // Таблица 5
                   {
                       switch (lParam)
                       {
                           case (1): f.TurnRightWolf(); break;
                           case (2): f.TurnLeftRightWolf(); break;
                           case (3): f.TurnLeftWolf(); break;
                           case (4): f.StepWolf(); break;
                           case (5): f.TurnBackWolf(); break;
                           case (6): f.TurnLeftRightNotTurnWolf(); break;
                           case (7): f.TurnLeftNotTurnWolf(); break;
                           case (8): f.TurnRightNotTurnWolf(); break;
                       }
                   }
                   System.Threading.Thread.Sleep(f.ind);
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
