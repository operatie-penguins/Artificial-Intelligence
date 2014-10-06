using System;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Drawing;

namespace Airport
{
    public class MyHookClass : NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        private Passenger passenger = new Passenger();
        private Policeman policeman = new Policeman();
        private Frame frame = new Frame();
        private Transporter transporter = new Transporter();
        private ConstObjects constobjects = new ConstObjects();
        private SapperDog sapperdog = new SapperDog();

        public string log = "";
        public string items
        {
            get 
            {
                return "�����: " + passenger.HasBomb.ToString() + "\r\n" +
                    "�����: " + passenger.HasDiamond.ToString() + "\r\n" +
                    "���������: " + passenger.HasDrugs.ToString() + "\r\n" +
                    "�����: " + passenger.HasLargeBag.ToString() + "\r\n" +
                    "��������: " + passenger.HasLicense.ToString() + "\r\n" +
                    "�����: " + passenger.HasLuggage.ToString() + "\r\n" +
                    "������: " + passenger.HasMealItems.ToString() + "\r\n" +
                    "�������: " + passenger.HasPassport.ToString() + "\r\n" +
                    "��������: " + passenger.HasPistol.ToString() + "\r\n" +
                    "�����: " + passenger.HasTicket.ToString() + "\r\n" +
                    "VIP: " + passenger.HasVipCard.ToString() + "\r\n";
            }
        }
        public Bitmap Img
        {
            get
            {
                Bitmap b = new Bitmap(800, 356);
                Graphics g = Graphics.FromImage(b);
                g.Clear(Color.White);
                Properties.Resources.���_��������.MakeTransparent();
                Properties.Resources.�����1.MakeTransparent();
                transporter.SetImage();
                g.DrawImage(Properties.Resources.���_��������, 0, 0);
                g.DrawImage(Properties.Resources.�����1, 0, 0);
                g.DrawImage(passenger.Image, 0, 0);
                g.DrawImage(frame.Image, 0, 0);
                g.DrawImage(transporter.Image, 0, 0);
                g.DrawImage(sapperdog.Image, 0, 0);
                //g.DrawImage(constobjects.Image, 0, 0);
                g.DrawImage(policeman.Image, 0, 0);
                g.DrawImage(Common.NewMessage(Common.TableMessage), 0, 0);
                b.MakeTransparent();
                return b;
            }
        }



        uint simpr;

        public MyHookClass(IntPtr hWnd)
        {
            simpr = RegisterWindowMessage("MyMessage"); // ������������ ��� ���������
            this.AssignHandle(hWnd);
        }

        protected override void WndProc(ref Message m) // � ��� ������� �������� ��� ��������� �� ������
        {
            if (m.Msg == simpr)
            {
                int wparamhi, wparamlo, wparam;
                int lParam = Convert.ToInt32("" + m.LParam);
                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;

                #region �������

                if (wparamhi == 0)//�������
                {
                    m.Result = new IntPtr(0);
                    if (wparamlo == 1)// ������� 1 
                    {
                        switch (lParam)
                        {
                            case 1: { if (Common.EverybodyPassed) m.Result = new IntPtr(1); break; }
                        }
                    }
                    else if (wparamlo == 2)// ������� 2 
                    {
                        switch (lParam)
                        {
                            case 1: { if (passenger.IsHigh) m.Result = new IntPtr(1); break; }
                            case 2: { if (passenger.IsFat) m.Result = new IntPtr(1); break; }
                            case 3: { if (passenger.HasPassport) m.Result = new IntPtr(1); break; }
                            case 4: { if (passenger.HasTicket) m.Result = new IntPtr(1); break; }
                            case 5: { if (passenger.HasMealItems) m.Result = new IntPtr(1); break; }
                            case 6: { if (passenger.HasVipCard) m.Result = new IntPtr(1); break; }
                            case 7: { if (passenger.HasLuggage) m.Result = new IntPtr(1); break; }
                            case 8: { if (passenger.HasLargeBag) m.Result = new IntPtr(1); break; }
                            case 9: { if (passenger.HasDrugs) m.Result = new IntPtr(1); break; }
                            case 10: { if (passenger.HasBomb) m.Result = new IntPtr(1); break; }
                            case 11: { if (passenger.HasDiamond) m.Result = new IntPtr(1); break; }
                            case 12: { if (passenger.HasLicense) m.Result = new IntPtr(1); break; }
                            case 13: { if (passenger.HasPistol) m.Result = new IntPtr(1); break; }
                        }
                    }
                }
                #endregion

                #region ��������

                else if (wparamhi == 1)//��������
                {

                    if (wparamlo == 1)// ������� 1 
                    {
                        switch (lParam)
                        {
                            case 1: { break; }
                            case 2: { passenger = new Passenger(); Common.PassLeft--; break; }
                        }
                    }
                    else if (wparamlo == 2)// ������� 2 
                    {
                        switch (lParam)
                        {
                            case 1: { passenger.ComeToTerminal(); break; }
                            case 2: { passenger.ExitAirport(); break; }
                            case 3: { passenger.Bend(); break; }
                            case 4: { passenger.GoThrough(); break; }
                            case 5: { policeman.Help(); break; }
                            case 6: { passenger.PutOutMetal(); break; }
                            case 7: { sapperdog.CallDog(); break; }
                            case 8: { sapperdog.CallSapper(); break; }
                            case 9: { policeman.Check(); break; }
                            case 10: { passenger.Shoot(); break; }
                        }
                    }

                    Application.DoEvents();
                    Thread.CurrentThread.Priority = ThreadPriority.Highest;
                    Thread.Sleep(350); // ���� � ��� ���� ���������� �����������, �� �������� ����� ���������� �����   

                    m.Result = new IntPtr(1); // ������� �� ������ �������� �� ������� ����� ������ ���� �������
                }
                #endregion
                log += wparamhi.ToString() + " " + wparamlo.ToString() + " " + lParam.ToString() + " " + m.Result.ToString() + "\r\n";
            }
            else
            {
                base.WndProc(ref m); // ��� ���� �������� �� ��������� � ����� ���������� ���������� ���������
            }
        }

    }
}
