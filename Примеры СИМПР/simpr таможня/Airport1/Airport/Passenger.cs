using System;
using System.Collections.Generic;
using System.Text;

namespace Airport
{
    public class Passenger : Human
    {
        private Gender gender;
        private Height height;
        private Figure figure;
        private CarryingItems items = new CarryingItems();
        private CarryingLuggage carrying = new CarryingLuggage();
        private int ImageIndex = 0;

        public Passenger()
        {

            Common.TableMessage = "";
            Common.Attention = false;

            #region �����������
            if (Probability(50)) gender = Gender.Male;
            else gender = Gender.Female;

            if (Probability(Common.ProbIsHigh)) height = Height.High;
            else height = Height.Normal;

            if (height == Height.Normal)
            {
                if (Probability(Common.ProbIsFat)) figure = Figure.Fat;
                else figure = Figure.Normal;
            }
            else figure = Figure.Normal;

            if (Probability(Common.ProbHasMetal)) items.Add(Items.Metal);
            if (Probability(Common.ProbHasPassport)) items.Add(Items.Passport);
            if (Probability(Common.ProbHasTicket)) items.Add(Items.Ticket);
            if (Probability(Common.ProbHasVipCard)) items.Add(Items.VipCard);

            if (Probability(Common.ProbHasLargeBag)) carrying.Add(Luggage.LargeBag);
            if (Probability(Common.ProbHasDrugs)) carrying.Add(Luggage.Drugs);
            if (Probability(Common.ProbHasBomb)) carrying.Add(Luggage.Bomb);
            if (Probability(Common.ProbHasDiamond)) carrying.Add(Luggage.Diamond);
            if (Probability(Common.ProbHasPistol)) carrying.Add(Luggage.Pistol);
            if (Probability(100 - Common.ProbHasLuggage)) carrying.Add(Luggage.None);

            if (Probability(80) && carrying.Diamond) items.Add(Items.License);

            #endregion

            #region ����� �����������

            if (height == Height.High) { /*if (carrying.SuitCase) ImageIndex = 1; else*/ if (carrying.LargeBag)ImageIndex = 2; else ImageIndex = 0; }
            else if (figure == Figure.Fat) { /*if (carrying.SuitCase)ImageIndex = 4;else*/  if (carrying.LargeBag)ImageIndex = 5; else ImageIndex = 3; }
            else { /*if (carrying.SuitCase)ImageIndex = 6; else*/ if (carrying.LargeBag)ImageIndex = 7; else ImageIndex = 8; }

            Image = Common.ImagesMan.Enter[ImageIndex];

            #endregion

        }

        public void ComeToTerminal()
        {
            Image = Common.ImagesMan.NearTerminal[ImageIndex];
        }

        public void ExitAirport()
        {
            Image = Common.ImagesMan.GoAway[ImageIndex];
        }

        public void Bend()
        {
            Image = Common.ImagesMan.Special[ImageIndex];
        }

        public void GoThrough()
        {
            Image = Common.ImagesMan.GoThrough[ImageIndex];
            Common.TableMessage = "����������� ����!";
        }

        public void PutOutMetal()
        {
            Common.TableMessage = "������������� �������� ������.";
        }

        public void Shoot()
        {
            Image = Common.ImagesMan.Shoot[ImageIndex];
        }

        private bool Probability(int percent)
        {
            Random Rand = new Random();
            int Number = Rand.Next(100);
            if (Number <= percent)
            {
                return true;
            }
            return false;
        }

        public bool IsHigh
        {
            get
            {
                if (height == Height.High) return true;
                return false;
            }
        }

        public bool IsFat
        {
            get
            {
                if (figure == Figure.Fat) return true;
                return false;
            }
        }

        public bool HasTicket
        {
            get
            {
                if (items.Ticket == true) return true;
                Common.TableMessage = "����������� �����.";
                return false;
            }
        }

        public bool HasPassport
        {
            get
            {
                if (items.Passport == true) return true;
                Common.TableMessage = "������ ��� �������� ��������.";
                return false;
            }
        }

        public bool HasVipCard
        {
            get
            {
                if (items.VipCard)
                {
                    Common.TableMessage = "VIP �����";
                    return true;
                }
                return false;
            }
        }

        public bool HasMealItems
        {
            get
            {
                if (items.Metal)
                {
                    Common.Attention = true;
                    return true;
                }
                return false;
            }
        }

        public bool HasLuggage
        {
            get 
            { 
                if (!carrying.None) return true;
                return false;
            }
        }

        //public bool HasSuitcase
        //{
        //    get
        //    {
        //        if (carrying.SuitCase) return true;
        //        return false;
        //    }
        //}

        public bool HasLargeBag
        {
            get
            {
                if (carrying.LargeBag)
                {
                    Common.TableMessage = "���������� �����! ������ ��������.";
                    Common.Attention = true;
                    return true;
                }
                return false;
            }
        }

        public bool HasDrugs
        {
            get
            {
                if (carrying.Drugs)
                {
                    return true;
                }
                return false;
            }
        }

        public bool HasBomb
        {
            get
            {
                if (carrying.Bomb)
                {
                    Common.Attention = true;
                    return true;
                }
                return false;
            }
        }

        public bool HasDiamond
        {
            get
            {
                if (carrying.Diamond)
                {
                    Common.Attention = true;
                    Common.TableMessage = "��������� �����!";
                    return true;
                }
                return false;
            }
        }

        public bool HasLicense
        {
            get
            {
                if (items.License) return true;
                if (carrying.Diamond) Common.TableMessage = "����������� �������� �� �����!";
                return false;
            }
        }

        public bool HasPistol
        {
            get
            {
                if (carrying.Pistol)
                {
                    Common.Attention = true;
                    Common.TableMessage = "��������� ��������!";
                    return true;
                }
                return false;
            }
        }
    }
}
