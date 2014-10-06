using System;
using System.Collections.Generic;
using System.Text;

using System.Windows.Forms;
using System.Threading;

using System.Runtime.InteropServices;

namespace testprog
{
    class Class1: NativeWindow
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern uint RegisterWindowMessage(string lpString);

        uint simpr;
        public ttest t; 



        public Class1(IntPtr hWnd)
        {
            t=new ttest();
            // Assign the handle from the source window to this class.  
            simpr = RegisterWindowMessage("MyMessage");
            this.AssignHandle(hWnd);

        }

        protected override void WndProc(ref Message m)
        {
            int wparamhi;
            int wparamlo;
            int wparam;
            int lParam = Convert.ToInt32("" + m.LParam);
            int w = 100;

            
             
            

            if (m.Msg == simpr)
            {

                wparam = Convert.ToInt32("" + m.WParam);
                wparamhi = wparam / 65536;
                wparamlo = wparam - wparamhi * 65536;


                if (wparamhi == 0)//�������
                {
                    m.Result = new IntPtr(0);
                    
                    
                    if (wparamlo == 1)// ������� 1 
                    {
                        if (lParam == 1)// ������� 1 ������� 1
                        {
                            if (t.group==0)
                            { 
                                //MessageBox.Show("���� �� �������?*");
                                m.Result = new IntPtr(1);
                               
                            }
                            
                        }
                        if (lParam == 2)// ������� 1 ������� 1
                        {
                            if (t.step[t.active] <10)
                            {
                               // MessageBox.Show("��� <10?");
                                m.Result = new IntPtr(1);

                            }

                        }
                        if (lParam == 3)// ������� 1 ������� 1
                        {
                            if (t.poz[(t.step[t.active]+1)]==true)
                            {
                               // MessageBox.Show("������� ������?");
                                m.Result = new IntPtr(1);
                                
                            }

                        }
                        if (lParam == 4)// ������� 1 ������� 1
                        {
                            if (t.step[t.active]==10)
                            {
                                t.poz[10] = true;
                               // MessageBox.Show("���=10");
                                m.Result = new IntPtr(1);
                                

                            }

                        }
                        if (lParam == 5)// ������� 1 ������� 1
                        {
                            if (t.step[t.active] == 5)
                            {
                               // MessageBox.Show("���=5?");
                                m.Result = new IntPtr(1);

                            }

                        }
                        if (lParam == 6)// ������� 1 ������� 1
                        {
                            if (t.scet > 100)
                            {
                                //MessageBox.Show("������� = 5?");
                                m.Result = new IntPtr(1);

                            }

                        }  
                     
                    }
                    else if (wparamlo == 2)// ������� 2 
                    {
                        if (lParam == 1)//������� 2 ������� 1
                        {
                            if (t.sid[t.active]!=0) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 2)// ������� 2 ������� 2
                        {

                            if ((t.stol[0] == 10) && (t.name[t.active] == "man1")) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 3)// ������� 2 ������� 3
                        {

                            if (t.stol[1] == 10) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 4)// ������� 2 ������� 4
                        {

                            if ((t.stol[2] == 10)&&(t.name[t.active]=="man2")) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 5)// ������� 2 ������� 5
                        {

                            if (t.sidtime[t.active]==0) m.Result = new IntPtr(1);
                        }


                    }
                    

                }
                else if (wparamhi == 1)//��������
                {
                    
                    if (wparamlo == 1)// ������� 1
                    {
                        if (lParam == 1)// ������� 1 �������� 1
                        {
                            t.main();
                            t.group = 5;
                            MessageBox.Show("������ ������� ���. �����");
                           
                        }
                        else if (lParam == 2)// ������� 1 �������� 2
                        {
                            
                            //MessageBox.Show("������� "+t.active+ "������"+t.scet);
                            t.delgroup();
                            Application.DoEvents();
                            Thread.Sleep(w);
                            

                        }
                        else if (lParam == 3)// ������� 1 �������� 2
                        {
                            
                           // MessageBox.Show("��������� � " + (t.active + 1) + " ������. ����� " + t.group);
                            t.next();
                            Application.DoEvents();
                            Thread.Sleep(w);
                        }
                        else if (lParam == 4)// ������� 1 �������� 2
                        {
                            
                          // MessageBox.Show("����� " + (t.active + 1) + "������ ���");
                            t.st();
                            Application.DoEvents();
                            Thread.Sleep(w);
                        }
                        if (lParam == 5)// ������� 1 �������� 1
                        {
                            MessageBox.Show("Rool ELSE");
                        }
                        if (lParam == 6)// ������� 1 �������� 1
                        {
                           // MessageBox.Show("����� � ��������"+(t.active+1));
                        }
                        
                    }
                    
                    
                    else if (wparamlo == 2)// ������� 2 
                {
                    if (lParam == 1)// ������� 2 �������� 1
                    {
                        t.wait();
                        //MessageBox.Show("������ "+t.active+" ����� �� " +t.sid[t.active]+"��������. �������� "+t.sidtime[t.active]+"�����");
                        Application.DoEvents();
                        Thread.Sleep(w);
                    }
                    else if (lParam == 2)// ������� 2 �������� 2
                    {
                        t.seat1();
                        //MessageBox.Show("������ " + t.active + "�� 1 ��������. ");
                        Application.DoEvents();
                        Thread.Sleep(w);
                    }
                    else if (lParam == 3)// ������� 2 �������� 2
                    {
                        t.seat2();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("������ " + t.active + "�� 2 ��������. ");
                    }
                    else if (lParam == 4)// ������� 2 �������� 2
                    {
                        t.seat3();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("������ " + t.active + "�� 3 ��������. ");
                    }
                    else if (lParam == 5)// ������� 2 �������� 2
                    {
                        t.go();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("������ " + t.active + "exit");
                    }
                    else if (lParam == 6)// ������� 2 �������� 2
                    {
                        t.next();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("������ " + t.active + "next");
                    }
                    else if (lParam == 7)// ������� 2 �������� 2
                    {
                        MessageBox.Show("�������� �� 2 �������");
                    }
                }

                    Application.DoEvents();
                    Thread.Sleep(w);
                    m.Result = new IntPtr(1);



                }
                



            }
            else
            {
                base.WndProc(ref m);

                //MessageBox.Show(m.Msg + " " + simpr);
            }



        }

    }
}
