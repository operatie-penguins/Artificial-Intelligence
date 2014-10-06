using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace SIMPR
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            FileStream f = new FileStream("DebugInfo.txt", FileMode.Create, FileAccess.Write);
            TextWriterTraceListener writer = new TextWriterTraceListener(f);
            Debug.Listeners.Add(writer);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());

            Debug.Flush();
            f.Close();
        }
    }
}