using System;
using System.Collections.Generic;
using System.Text;

namespace Airport
{
    public class Transporter : Device
    {
        public Transporter()
        {
            Image = Properties.Resources.�������2_1_;
        }

        public void SetImage()
        {
            if(Common.Attention) Image = Properties.Resources.�������2_2_;
            else Image = Properties.Resources.�������2_1_;
        }
    }
}
