using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace WindowsApplication4
{
        //[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        //static  delegate RegisterWindowMessage(string lpString);
    
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        public static Form fm1;

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            fm1 = new Form1();
            Application.Run(fm1);
        }
    }
}