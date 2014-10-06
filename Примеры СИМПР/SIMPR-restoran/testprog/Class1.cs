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


                if (wparamhi == 0)//услови€
                {
                    m.Result = new IntPtr(0);
                    
                    
                    if (wparamlo == 1)// таблица 1 
                    {
                        if (lParam == 1)// таблица 1 условие 1
                        {
                            if (t.group==0)
                            { 
                                //MessageBox.Show("есть ли человек?*");
                                m.Result = new IntPtr(1);
                               
                            }
                            
                        }
                        if (lParam == 2)// таблица 1 условие 1
                        {
                            if (t.step[t.active] <10)
                            {
                               // MessageBox.Show("Ўаг <10?");
                                m.Result = new IntPtr(1);

                            }

                        }
                        if (lParam == 3)// таблица 1 условие 1
                        {
                            if (t.poz[(t.step[t.active]+1)]==true)
                            {
                               // MessageBox.Show("ѕозици€ зан€та?");
                                m.Result = new IntPtr(1);
                                
                            }

                        }
                        if (lParam == 4)// таблица 1 условие 1
                        {
                            if (t.step[t.active]==10)
                            {
                                t.poz[10] = true;
                               // MessageBox.Show("шаг=10");
                                m.Result = new IntPtr(1);
                                

                            }

                        }
                        if (lParam == 5)// таблица 1 условие 1
                        {
                            if (t.step[t.active] == 5)
                            {
                               // MessageBox.Show("Ўаг=5?");
                                m.Result = new IntPtr(1);

                            }

                        }
                        if (lParam == 6)// таблица 1 условие 1
                        {
                            if (t.scet > 100)
                            {
                                //MessageBox.Show("—четчик = 5?");
                                m.Result = new IntPtr(1);

                            }

                        }  
                     
                    }
                    else if (wparamlo == 2)// таблица 2 
                    {
                        if (lParam == 1)//таблица 2 условие 1
                        {
                            if (t.sid[t.active]!=0) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 2)// таблица 2 условие 2
                        {

                            if ((t.stol[0] == 10) && (t.name[t.active] == "man1")) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 3)// таблица 2 условие 3
                        {

                            if (t.stol[1] == 10) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 4)// таблица 2 условие 4
                        {

                            if ((t.stol[2] == 10)&&(t.name[t.active]=="man2")) m.Result = new IntPtr(1);
                        }
                        else if (lParam == 5)// таблица 2 условие 5
                        {

                            if (t.sidtime[t.active]==0) m.Result = new IntPtr(1);
                        }


                    }
                    

                }
                else if (wparamhi == 1)//действи€
                {
                    
                    if (wparamlo == 1)// таблица 1
                    {
                        if (lParam == 1)// таблица 1 действие 1
                        {
                            t.main();
                            t.group = 5;
                            MessageBox.Show("Ѕольше человек нет. ¬ыход");
                           
                        }
                        else if (lParam == 2)// таблица 1 действие 2
                        {
                            
                            //MessageBox.Show("удал€ем "+t.active+ "группу"+t.scet);
                            t.delgroup();
                            Application.DoEvents();
                            Thread.Sleep(w);
                            

                        }
                        else if (lParam == 3)// таблица 1 действие 2
                        {
                            
                           // MessageBox.Show("ѕереходим к " + (t.active + 1) + " группе. ¬сего " + t.group);
                            t.next();
                            Application.DoEvents();
                            Thread.Sleep(w);
                        }
                        else if (lParam == 4)// таблица 1 действие 2
                        {
                            
                          // MessageBox.Show("грппа " + (t.active + 1) + "делает шаг");
                            t.st();
                            Application.DoEvents();
                            Thread.Sleep(w);
                        }
                        if (lParam == 5)// таблица 1 действие 1
                        {
                            MessageBox.Show("Rool ELSE");
                        }
                        if (lParam == 6)// таблица 1 действие 1
                        {
                           // MessageBox.Show("зашли в ресторан"+(t.active+1));
                        }
                        
                    }
                    
                    
                    else if (wparamlo == 2)// таблица 2 
                {
                    if (lParam == 1)// таблица 2 действие 1
                    {
                        t.wait();
                        //MessageBox.Show("группа "+t.active+" сидит за " +t.sid[t.active]+"столиком. ќсталось "+t.sidtime[t.active]+"ждать");
                        Application.DoEvents();
                        Thread.Sleep(w);
                    }
                    else if (lParam == 2)// таблица 2 действие 2
                    {
                        t.seat1();
                        //MessageBox.Show("группа " + t.active + "за 1 столиком. ");
                        Application.DoEvents();
                        Thread.Sleep(w);
                    }
                    else if (lParam == 3)// таблица 2 действие 2
                    {
                        t.seat2();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("группа " + t.active + "за 2 столиком. ");
                    }
                    else if (lParam == 4)// таблица 2 действие 2
                    {
                        t.seat3();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("группа " + t.active + "за 3 столиком. ");
                    }
                    else if (lParam == 5)// таблица 2 действие 2
                    {
                        t.go();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("группа " + t.active + "exit");
                    }
                    else if (lParam == 6)// таблица 2 действие 2
                    {
                        t.next();
                        Application.DoEvents();
                        Thread.Sleep(w);
                        //MessageBox.Show("группа " + t.active + "next");
                    }
                    else if (lParam == 7)// таблица 2 действие 2
                    {
                        MessageBox.Show("ошибочка во 2 таблице");
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
