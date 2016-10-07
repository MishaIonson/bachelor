using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class SpaceObject
    {
        public const int LIGHT_SPEED = 100000;
        public const int MIN_WEIGHT_OF_BLACK_WHOLE = 234123109;

        protected String name;
        public int temerature;

        private int weight;
        public int Weight
        {
            get {return weight;}
            set
            {
                if ((value > 0) && (value < MIN_WEIGHT_OF_BLACK_WHOLE))
                    weight = value;
            }

        }

        private double speed;
        public double Speed
        {
            get { return speed; }
            set
            {
                if ((value >= 0) && (value < LIGHT_SPEED))
                    speed = value;
            }
        }

        public SpaceObject(String name)
        {
            Console.WriteLine("SpaceObject.SpaceObject(String)");

            weight = 1;
            speed = 0d;

            this.name = name;
            temerature = 0;
        }

        public double getNeededTimeToOvercome(int distance)
        {
            return (double) distance / speed;
        }

        public double getNeededTimeToOvercome(double distance)
        {
            return distance / speed;
        }


        public virtual int getNeededTimeToGetTemperature(int neededTemp)
        {
            /*
            * -1 returns if there is no way to get this temp
            */
            if (neededTemp > temerature)
                return -1;
            else
                return (int) Math.Sqrt(weight) * (temerature - neededTemp);

        }
    }
}
