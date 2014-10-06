using System;
using System.Collections.Generic;
using System.Text;

namespace WindowsApplication4
{
    public class factory
    {
        public people[] man;
        public int man_count;
        public int active;
        public string log;
        public string message;
        public int b_pos; // позиция библиотекаря
        public int b_b_stage; // этаж запроса
        public int b_b_id; // номер книги
        public bool vzat; // взять ли книгу хочет библиотекарь?
        public bool otdat(){return !vzat;}
        public bool[,] books; // шкаф
        public bool getbook; // взял книлу = true; не было книги = false;
        public bool up; // идёт вверх?
        Random RandomNumber;
        public bool down() { return !up; }
        public void main()
        {
            message = "none";
            b_pos = 0;
            man_count = 0; // щас нет людей
            man = new people[100];
            books=new bool[4,4];


            RandomNumber = new Random();
            
            
            for(int i=0;i<4;i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (RandomNumber.Next(1, 4) == 2)
                        books[i, j] = false;
                    else
                        books[i, j] = true;
                }
            }
        }

        public void newman()
        {
            man[man_count] = new people();

            if (RandomNumber.Next(1, 4) == 1)
            {
                //несёт книгу
                int stg = 0;
                int id = 0;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (books[i, j] == false)
                        {
                            stg = i;
                            id = j;
                        }
                    }
                }

                man[man_count].main(true, stg,id);

            }
            else
            {
                //берёт книгу
                man[man_count].main(false, RandomNumber.Next(0, 4), RandomNumber.Next(0, 4));

            }
            man_count++;
        }

        public void deleteman(int id)
        {
            for (int i = 0; i < man_count; i++)
            {
                if (i >= id) man[i] = man[i + 1];
            }
            man_count--;
        }

        public void next()
        {
            active++;
            if (active >= man_count) active = 0;
        }

        public void updatebookan(int id)
        {
            if (man[id].vzat) return;
                            for (int i = 0; i < 4; i++)
                            {
                                for (int j = 0; j < 4; j++)
                                {
                                    if (books[i, j] == false)
                                    {
                                        man[id].book_stage = i;
                                        man[id].book_number = j;
                                    }
                                }
                            }
        }


        public class people
        {
            public int step; // шаг
            public bool sdat; // идёт сдавать
            public bool vzat; // идёт взять
            public bool done; // сделал дело (сдал или взял)
            public int book_stage; // этаж (1-4)
            public int book_number; // номер книги

            public void main(bool sd, int bs, int bn)
            {
                sdat = sd;
                vzat = !sd;
                book_number = bn;
                book_stage = bs;
                step = 0;
            }
            public void go() //шаг
            {
                step++;
            }

            public bool kontorka() // у конторки?
            {
                if (step == 5) return true;
                return false;
            }

            public bool door() // у двери?
            {
                if (step == 9) return true;
                return false;
            }
            
        }

    }
}
