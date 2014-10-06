using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


namespace WindowsApplication9
{
    public enum finex { fine,exellent}//перечислимый тип
    public enum season {winter,autumn,summer,spring }
   // public enum money { thousand1, thousand2, thousand3, thousand4, thousand5, thousand6, thousand7 }
    public enum havemoney { yes,no}
    public class koor
    {
        public int position = 0;
        public Point[] KOOR;
        public Point[] KOOR1 = new Point[19];
        public Point[] KOOR2 = new Point[19];
        
        public koor()
        {
            KOOR = KOOR1;
            /*
            KOOR[0] = new Point(20, 220);
            KOOR[1] = new Point(68, 220);
            KOOR[2] = new Point(227, 220);
            KOOR[3] = new Point(360, 220);
            KOOR[4] = new Point(500, 220);
            KOOR[5] = new Point(655, 220);
            KOOR[6] = new Point(726, 293);
            KOOR[7] = new Point(638, 364);
            KOOR[8] = new Point(570, 364);
            KOOR[9] = new Point(495, 364);
            KOOR[10] = new Point(388, 364);
            KOOR[11] = new Point(250, 364);
            KOOR[12] = new Point(64, 364);
            KOOR[13] = new Point(64, 308);
            */
            KOOR1[0] = new Point(20, 220);
            KOOR1[1] = new Point(68, 220);
            KOOR1[2] = new Point(227, 220);
            KOOR1[3] = new Point(360, 220);
            KOOR1[4] = new Point(500, 220);
            KOOR1[5] = new Point(655, 220);
            KOOR1[6] = new Point(726, 293);
            KOOR1[7] = new Point(638, 364);
            KOOR1[8] = new Point(570, 364);
            KOOR1[9] = new Point(495, 364);
            KOOR1[10] = new Point(388, 364);
            KOOR1[11] = new Point(301, 364);
            KOOR1[12] = new Point(250, 364);
            KOOR1[13] = new Point(185, 364);
            KOOR1[14] = new Point(64, 364);
            KOOR1[15] = new Point(64, 308);
            KOOR1[16] = new Point(64, 220);
            KOOR1[17] = new Point(21, 220);
            KOOR1[18] = new Point(21, 220);

            KOOR2[0] = new Point(20, 220);
            KOOR2[1] = new Point(68, 220);
            KOOR2[2] = new Point(227, 220);
            KOOR2[3] = new Point(360, 220);
            KOOR2[4] = new Point(500, 220);
            KOOR2[5] = new Point(655, 220);
            KOOR2[6] = new Point(726, 293);
            KOOR2[7] = new Point(726, 364);
            KOOR2[8] = new Point(645, 364);
            KOOR2[9] = new Point(527, 364);
            KOOR2[10] = new Point(388, 364);
            KOOR2[11] = new Point(389, 457);
            KOOR2[12] = new Point(389, 503);
            KOOR2[13] = new Point(322, 503);
            KOOR2[14] = new Point(209, 503);
            KOOR2[15] = new Point(323, 503);
            KOOR2[16] = new Point(457, 503);
            KOOR2[17] = new Point(543, 503);
            KOOR2[18] = new Point(543, 503);
        }
    }  
}
