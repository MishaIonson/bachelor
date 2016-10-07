using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Star : SpaceObject
    {
        private static int MIN_STAR_TEMPERATURE;
        private static int MIN_STAR_WEIGHT;

        private static int TEMPERATURE_LOSTS_PER_YEAR;

        static Star()
        {
            MIN_STAR_TEMPERATURE = 1000;
            MIN_STAR_WEIGHT = 11233;
            TEMPERATURE_LOSTS_PER_YEAR = 10;
        }

        public int TimeToExplosion
        {
            get
            {
                if (temerature < MIN_STAR_TEMPERATURE)
                    return 0;
                else
                    return ((MIN_STAR_TEMPERATURE - temerature) / TEMPERATURE_LOSTS_PER_YEAR);
            }
            set
            {
                if (value >= 0)
                    temerature = MIN_STAR_TEMPERATURE - TEMPERATURE_LOSTS_PER_YEAR * value;
            }
        }

        public Star(String name) : base(name)
        {
            Console.WriteLine("Star.Star(String)");

            base.temerature = MIN_STAR_TEMPERATURE;
            base.Weight = MIN_STAR_WEIGHT;
        }

        public override int getNeededTimeToGetTemperature(int neededTemp)
        {
            if (temerature > neededTemp)
                return (temerature - neededTemp) / TEMPERATURE_LOSTS_PER_YEAR;
            else
                return base.getNeededTimeToGetTemperature(neededTemp);
        }


    }
}
