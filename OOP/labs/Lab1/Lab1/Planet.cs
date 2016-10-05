using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Planet : SpaceObject
    {
        protected static String BEST_PLANET;
        public static int INHABIT_DISTANCE_MIN;
        public static int INHABIT_DISTANCE_MAX;
        public static int AVERAGE_DISTANCE_TO_STAR;
        public static int AVERAGE_TEMPERATURE;
        public static int WARMING_SPEED;

        private int radius;
        public int distanceToStar;

        public int Diameter
        {
            get
            {
                return 2 * radius;
            }
            set
            {
                if (value > 0)
                    radius = value / 2;
            }
        }

        public Planet(String name) : base(name)
        {
            Console.WriteLine("Planet.Planet(String)");
            setDefaultValues();

            this.name = name;
        }

        static Planet()
        {
            Console.WriteLine("Planet.Planet()");
            BEST_PLANET = "Earth";

            INHABIT_DISTANCE_MIN = 100;
            INHABIT_DISTANCE_MAX = 1000;

            AVERAGE_DISTANCE_TO_STAR = 4023;
            AVERAGE_TEMPERATURE = 20;

            WARMING_SPEED = 2;
        }

        private void setDefaultValues()
        {
            this.Speed = 0;
            this.Weight = 1;

            name = "Planet-X";
            radius = 1;
            distanceToStar = AVERAGE_DISTANCE_TO_STAR;
            temerature = AVERAGE_TEMPERATURE;
        }

        public String getName()
        {
            return name;
        }

        public Boolean setName(String name)
        {
            if (isAppropriateName(name))
            {
                this.name = name;
                return true;
            }

            return false;
        }

        protected Boolean isAppropriateName(String name)
        {
            for (int i = 0; i < name.Length; i++)
            {
                if (((int)name[i] >= (int)'a') && ((int)name[i] <= (int)'z'))
                    continue;
                else if (((int)name[i] >= (int)'A') && ((int)name[i] <= (int)'Z'))
                    continue;
                else if (((int)name[i] >= (int)'0') && ((int)name[i] <= (int)'9'))
                    continue;
                else if (name[i] == '-')
                    continue;
                else
                    return false;
            }

            return true;
        }

        public virtual bool isInhabited()
        {
            if ((distanceToStar >= INHABIT_DISTANCE_MIN) && (distanceToStar <= INHABIT_DISTANCE_MAX))
                return true;
            else
                return false;
        }

        public String getNameOfBestPlanet()
        {
            return BEST_PLANET;
        }

        public override int getNeededTimeToGetTemperature(int neededTemp)
        {
            if (neededTemp >= temerature)
                return (neededTemp - temerature) / WARMING_SPEED;
            else
                return base.getNeededTimeToGetTemperature(neededTemp);
        }
    }
}
