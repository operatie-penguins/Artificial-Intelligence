using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

namespace Box
{
    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        uint simpr;
        Form1 f;

        public MyHookClass(Form1 af)
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
                if (wparamhi == 0) // Условия
                {
                    if (wparamlo == 1) // Номер таблицы
                    { //Человечек (Таблица 1)
                            switch (lParam) // Номер Условия
                            {
                                case 1: m.Result = f.Box(); break; // Есть ли кубики?
                                case 2: m.Result = f.NearHeap(); break; // Человечек у кучи?
                                case 3: m.Result = f.InHands(); break; //Кубик в руках?
                                case 4: m.Result = f.RedInHands(); break; //Красный кубик в руках?
                                case 5: m.Result = f.WhiteInHands(); break; //Белый кубик в руках?
                                default: m.Result = new IntPtr(1); break;
                            }
                    }
                    else if (wparamlo == 2)//Человечек разносит кубики (Таблица 2)
                       {
                            switch (lParam)
                            {
                                case 1: m.Result = f.LeftSide(); break; // Левая сторона?
                                case 2: m.Result = f.RightSide(); break; // Правая сторона?
                                case 3: m.Result = f.BoxNearLeft(); break; // Рядом ящик есть по левой стороне?
                                case 4: m.Result = f.BoxNearRight(); break; // Рядом ящик есть по правой стороне?
                                case 5: m.Result = f.InHands(); break; //Кубик в руках?
                                default: m.Result = new IntPtr(1); break;
                            }
                       }
                    else  
                        
                        if (wparamlo == 3) // Человечек возвращается (Таблица 3)
                       {
                            switch (lParam)
                            {
                                case 1: m.Result = f.LeftSideBack(); break; // Возвращается слева?
                                case 2: m.Result = f.RightSideBack(); break; // Возвращается справа?
                                case 3: m.Result = f.Step(); break; // Шагать вперед можно?
                                case 4: m.Result = f.StepBox(); break; // Предыдущий шаг - положить кубик?
                                default: m.Result = new IntPtr(1); break;
                            }
                    }
                   // MessageBox.Show(m.Result.ToString());
                    
                }
                  
                #endregion
                #region Действия
                else if (wparamhi == 1) // Действия
                {
                    if (wparamlo == 1)
                    {
                            switch (lParam) // Человечек (Таблица 1)
                            {
                                case 1: f.Get(); break; //взять кубик
                                case 2: f.GoLeftSide(); break; //идти к левой стороне
                                case 3: f.GoRightSide(); break; //идти к правой стороне
                                case 4: MessageBox.Show("Ура! Все кубики разложены!"); break; //выдать сообщение
                            } 
                    }
                    else if (wparamlo == 2)
                    {
                            switch (lParam) // Человечек разносит кубики (Таблица 2)
                            {
                                case 1: f.GiveBoxLeft(); break; //положить кубик с левой стороны
                                case 2: f.GiveBoxRight(); break; //положить кубик с правой стороны
                                case 3: f.TurnRightLeftSide(); break; //повернуть направо с левой стороны
                                case 4: f.TurnRightRightSide(); break; //повернуть направо с правой стороны
                                case 5: f.TurnLeftLeftSide(); break; //повернуть налево с левой стороны
                                case 6: f.TurnLeftRightSide(); break; //повернуть налево с правой стороны
                                case 7: f.StepLeftSide(); break; //сделать шаг с левой стороны
                                case 8: f.StepRightSide(); break; //сделать шаг с правой стороны
                            }
                    }
                    else if (wparamlo == 3)
                    {
                            switch (lParam) // Человечек возвращается (Таблица 3)
                            {
                                case 1: f.TurnLeft(); break; //повернуть налево
                                case 2: f.TurnRight(); break; //повернуть направо
                                case 3: f.StepUpLeft(); break; //сделать шаг (левая сторона)
                                case 4: f.StepUpRight(); break; //сделать шаг (правая сторона)
                                case 5: f.Go(); break; //идти к кубикам
                            }
                    }
                    System.Threading.Thread.Sleep(100);
                    m.Result = new IntPtr(1);
                        // Ответом на запрос действия со стороны СИМПР должна быть единица

                    //MessageBox.Show(wparamlo.ToString() + "|" + lParam.ToString());
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

