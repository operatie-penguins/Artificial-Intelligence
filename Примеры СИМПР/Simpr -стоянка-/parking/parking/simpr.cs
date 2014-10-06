using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Drawing;

namespace parking
{
    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        uint simpr;

        public car Car = new car();
        parking Parking = new parking();

        public string log = "";

        public MyHookClass(IntPtr hWnd)
        {
            simpr = RegisterWindowMessage("MyMessage"); // регистрируем своё сообщение
            this.AssignHandle(hWnd);
        }

        private IntPtr SetPtr(bool term)
        {
            if (term) return new IntPtr(1);
            return new IntPtr(0);
        }

        protected override void WndProc(ref Message m) // в эту функцию приходят все сообщения от СИМПРА
        {
            if (m.Msg == simpr)
            {
                int wparamhi, wparamlo, wparam;
                int lParam = Convert.ToInt32("" + m.LParam);
                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;

                #region Условия

                if (wparamhi == 0)//условия
                {
                    m.Result = new IntPtr(0);
                    if (wparamlo == 1)// таблица 1 
                    {
                        switch (lParam)
                        {
                            case 1: { m.Result = SetPtr(Car.IsSedan); break; }
                            case 2: { m.Result = SetPtr(Car.IsTruck); break; }
                            case 3: { m.Result = SetPtr(Car.IsMinivan); break; }
                            case 4: { m.Result = SetPtr(Car.IsBike); break; }
                        }
                    }
                    else  
                    {
                        switch (lParam)
                        {
                            case 1: { m.Result = SetPtr(Car.WantsToPark); break; }
                            case 2: { m.Result = SetPtr(Car.HasTrailer); break; }
                            case 3: { m.Result = SetPtr(Car.IsVIP); break; }
                            case 4: { m.Result = SetPtr(Car.HasSpikes); break; }
                            case 5: { m.Result = SetPtr(Car.IsStudent); break; }
                            case 6: { m.Result = SetPtr(Car.IsDirty); break; }
                          
                        }
                    }
                }
                #endregion

                #region Действия

                else if (wparamhi == 1)//действия
                {
                    if (wparamlo == 2)// таблица 1 
                    {
                        switch (lParam)
                        {
                            case 1: { Car.SedanDriveToParking(); break; }
                            case 2: { Car.SedanUseTrailerParking(); break; }
                            case 3: { Car.SedanUseVIPParking(); break; }
                            case 4: { Car.SedanPenaltySpikes(); break; }
                            case 5: { Car.SedanPenaltyStudent(); break; }
                            case 6: { Car.SedanPenaltyCleaning(); break; }
                            case 7: { Car.SedanDriveAway(); break; }
                            case 8: { Car = new car(); ; break; }
                        }
                    }
                    else if (wparamlo == 3)// таблица 2 
                    {
                        switch (lParam)
                        {
                            case 1: { Car.TruckDriveToParking(); break; }
                            case 2: { Car.TruckUseTrailerParking(); break; }
                            case 3: { Car.TruckUseVIPParking(); break; }
                            case 4: { Car.TruckPenaltySpikes(); break; }
                            case 5: { Car.TruckPenaltyStudent(); break; }
                            case 6: { Car.TruckPenaltyCleaning(); break; }
                            case 7: { Car.TruckDriveAway(); break; }
                            case 8: { Car = new car(); ; break; }
                        }
                    }
                    else if (wparamlo == 4)// таблица 2 
                    {
                        switch (lParam)
                        {
                            case 1: { Car.MinivanDriveToParking(); break; }
                            case 2: { Car.MinivanUseTrailerParking(); break; }
                            case 3: { Car.MinivanUseVIPParking(); break; }
                            case 4: { Car.MinivanPenaltySpikes(); break; }
                            case 5: { Car.MinivanPenaltyStudent(); break; }
                            case 6: { Car.MinivanPenaltyCleaning(); break; }
                            case 7: { Car.MinivanDriveAway(); break; }
                            case 8: { Car = new car(); ; break; }
                        }
                    }
                    else if (wparamlo == 5)// таблица 2 
                    {
                        switch (lParam)
                        {
                            case 1: { Car.BikeDriveToParking(); break; }
                            case 2: { Car.BikeUseTrailerParking(); break; }
                            case 3: { Car.BikeUseVIPParking(); break; }
                            case 4: { Car.BikePenaltySpikes(); break; }
                            case 5: { Car.BikePenaltyStudent(); break; }
                            case 6: { Car.BikePenaltyCleaning(); break; }
                            case 7: { Car.BikeDriveAway(); break; }
                            case 8: { Car = new car(); ; break; }
                        }
                    }
                    

                    Application.DoEvents();
                    Thread.Sleep(500); // если у нас есть визуальное отображение, то задержку можно установить здесь   

                    m.Result = new IntPtr(1); // ответом на запрос действия со стороны СИМПР должна быть единица
                }
                #endregion
                log = wparamhi.ToString() + " " + wparamlo.ToString() + " " + lParam.ToString() + " " + m.Result.ToString() + "\r\n" + log;
            }
            else
            {
                base.WndProc(ref m); // для всех действий не связанных с СИМПР возвращаем управление программе
            }
        }
    }
}
