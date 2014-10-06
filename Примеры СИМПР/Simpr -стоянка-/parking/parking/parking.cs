using System;
using System.Collections.Generic;
using System.Text;

namespace parking
{
    public class parking
    {
        private int[] free = new int[5];

        public parking()
        {
            Random rand = new Random();
            for (int i = 0; i < 5; i++)
            {
                free[i] = rand.Next(5);
            }
        }

        public int this[int index]
        {
            get
            {
                return free[index];
            }
        }
    }
}
