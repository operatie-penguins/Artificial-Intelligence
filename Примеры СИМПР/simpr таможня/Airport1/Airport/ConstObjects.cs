using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace Airport
{
    public class ConstObjects : Device
    {
        public ConstObjects()
        {
            Bitmap image1 = Properties.Resources.конвеер2;
            Bitmap image2 = Properties.Resources.Мент2;

   
                Bitmap b = new Bitmap(800, 356);
                Graphics g = Graphics.FromImage(b);
                g.Clear(Color.White);
                image1.MakeTransparent();
                image2.MakeTransparent();
                g.DrawImage(image1, 0, 0);
                g.DrawImage(image2, 0, 0);
                Image = b;
        }
    }
}
