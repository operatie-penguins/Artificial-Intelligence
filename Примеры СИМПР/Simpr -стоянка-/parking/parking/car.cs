using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace parking
{
    public class car
    {
        public enum TypeOfCar { Sedan, Truck, Minivan, Bike }

        public bool WantsToPark = false;
        public bool HasTrailer = false;
        public bool IsVIP = false;
        public bool HasSpikes = false;
        public bool IsStudent = false;
        public bool IsDirty = false;
        public bool IsExpensive = false;
        public bool ShowTrailer = false;
        public string Messages = "";

        public TypeOfCar CarType;

        public Bitmap CarImage;
        public Bitmap TrailerImage;

        public Point Position;
        public Point TrailerPosition;

        Random rand = new Random();

        private bool RandomBool(int percent)
        {
            if (percent <= 100)
            {
                if (rand.Next(100) <= percent) return true;
                return false;
            }
            return true;
        }

        private TypeOfCar SetType
        {
            get
            {
                int number = rand.Next(100);
                if (number > 75) return TypeOfCar.Bike;
                if (number > 50) return TypeOfCar.Minivan;
                if (number > 25) return TypeOfCar.Truck;
                return TypeOfCar.Sedan;
            }
        }

        private Bitmap SetImage
        {
            get
            {
                if (CarType == TypeOfCar.Bike) return Properties.Resources.мотоцикл;
                if (CarType == TypeOfCar.Minivan)
                {
                    if (HasTrailer) return Properties.Resources.минивен_с_прицепом;
                    return Properties.Resources.минивен;
                }
                if (CarType == TypeOfCar.Truck)
                {
                    if (HasTrailer) return Properties.Resources.грузовик_с_прицепом;
                    return Properties.Resources.грузовик;
                }
                else
                {
                    if (HasTrailer) return Properties.Resources.легковая_с_прицепом;
                    return Properties.Resources.red;
                }
            }
        }

        public car()
        {
            WantsToPark = RandomBool(50);

            HasTrailer = RandomBool(50);
            IsVIP = RandomBool(50);
            HasSpikes = RandomBool(50);
            IsStudent = RandomBool(50);
            IsDirty = RandomBool(50);
            IsExpensive = RandomBool(50);

            CarType = SetType;
            CarImage = SetImage;

            if (CarType != TypeOfCar.Truck) TrailerImage = Properties.Resources.ПрицепЛегковая;
            else TrailerImage = Properties.Resources.ПрицепГрузовик;

            Position = new Point(30, 220);
            TrailerPosition = new Point(40, 430);
        }

        #region Свойства

        public bool IsSedan
        {
            get
            {
                if (CarType == TypeOfCar.Sedan) return true;
                return false;
            }
        }

        public bool IsTruck
        {
            get
            {
                if (CarType == TypeOfCar.Truck) return true;
                return false;
            }
        }

        public bool IsMinivan
        {
            get
            {
                if (CarType == TypeOfCar.Minivan) return true;
                return false;
            }
        }

        public bool IsBike
        {
            get
            {
                if (CarType == TypeOfCar.Bike) return true;
                return false;
            }
        }

        #endregion

        #region Методы

        public void SedanDriveToParking()
        {
            Position = new Point(950, 55);
            CarImage = Properties.Resources.red;
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }

        public void SedanUseTrailerParking()
        {
            ShowTrailer = true;
        }

        public void SedanUseVIPParking()
        {
            Position = new Point(800, 55);
            CarImage = Properties.Resources.Легковая_vip;
            CarImage.RotateFlip(RotateFlipType.Rotate180FlipNone);
        }

        public void SedanPenaltySpikes()
        {
            Messages += "Штраф за использование ошипованной резины: 50 рублей.\r\n";
        }

        public void SedanPenaltyStudent()
        {
            Messages += "Ученик за рулем. Доплата 50 рублей.\r\n";
        }

        public void SedanPenaltyCleaning()
        {
            Messages += "Автомобиль должен посетить мойку. Доплата 50 рублей.\r\n";
        }

        public void SedanDriveAway()
        {
            Position = new Point(270, 10);
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }



        public void TruckDriveToParking()
        {
            Position = new Point(950, 245);
            CarImage = Properties.Resources.грузовик;
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }

        public void TruckUseTrailerParking()
        {
            ShowTrailer = true;
        }

        public void TruckUseVIPParking()
        {
            Position = new Point(800, 245);
            CarImage = Properties.Resources.Грузовик_vip;
            CarImage.RotateFlip(RotateFlipType.Rotate180FlipNone);
        }

        public void TruckPenaltySpikes()
        {
            Messages += "Штраф за использование ошипованной резины: 150 рублей.\r\n";
        }

        public void TruckPenaltyStudent()
        {
            Messages += "Ученик за рулем. Доплата 150 рублей.\r\n";
        }

        public void TruckPenaltyCleaning()
        {
            Messages += "Автомобиль должен посетить мойку. Доплата 150 рублей.\r\n";
        }

        public void TruckDriveAway()
        {
            Position = new Point(270, 10);
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }



        public void MinivanDriveToParking()
        {
            Position = new Point(950, 395);
            CarImage = Properties.Resources.минивен;
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }

        public void MinivanUseTrailerParking()
        {
            ShowTrailer = true;
        }

        public void MinivanUseVIPParking()
        {
            Position = new Point(800, 395);
            CarImage = Properties.Resources.Минивен_vip;
            CarImage.RotateFlip(RotateFlipType.Rotate180FlipNone);
        }

        public void MinivanPenaltySpikes()
        {
            Messages += "Штраф за использование ошипованной резины: 100 рублей.\r\n";
        }

        public void MinivanPenaltyStudent()
        {
            Messages += "Ученик за рулем. Доплата 100 рублей.\r\n";
        }

        public void MinivanPenaltyCleaning()
        {
            Messages += "Автомобиль должен посетить мойку. Доплата 100 рублей.\r\n";
        }

        public void MinivanDriveAway()
        {
            Position = new Point(270, 10);
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }






        public void BikeDriveToParking()
        {
            Position = new Point(950, 635);
            CarImage = Properties.Resources.мотоцикл;
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }

        public void BikeUseTrailerParking()
        {
        }

        public void BikeUseVIPParking()
        {
            Position = new Point(800, 635);
            CarImage = Properties.Resources.Мотоцикл_vip;
            CarImage.RotateFlip(RotateFlipType.Rotate180FlipNone);
        }

        public void BikePenaltySpikes()
        {
            Messages += "Штраф за использование ошипованной резины: 25 рублей.\r\n";
        }

        public void BikePenaltyStudent()
        {
            Messages += "Ученик за рулем. Доплата 25 рублей.\r\n";
        }

        public void BikePenaltyCleaning()
        {
            Messages += "Автомобиль должен посетить мойку. Доплата 25 рублей.\r\n";
        }

        public void BikeDriveAway()
        {
            Position = new Point(270, 10);
            CarImage.RotateFlip(RotateFlipType.Rotate270FlipNone);
        }

        #endregion
    }
}
