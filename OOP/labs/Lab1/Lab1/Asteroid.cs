using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Asteroid
    {
        /* if planet's diameter >= MIN_DIAMETER_OF_PLANET_TO_BE_COLLAPSED 
         * then in case if asteroid is faster then planet,
         * last will be destroyed
        */
        private static int MIN_DIAMETER_OF_PLANET_TO_BE_COLLAPSED;

        static Asteroid()
        {
            MIN_DIAMETER_OF_PLANET_TO_BE_COLLAPSED = 10230;
        }

        private Asteroid()
        {

        }

        public static Boolean willCollapsePlanet(int planetDiameter, int planetSpeed, int asteroidSpeed)
        {
            if ((planetDiameter >= MIN_DIAMETER_OF_PLANET_TO_BE_COLLAPSED) && (asteroidSpeed > planetSpeed))
                return true;
            else
                return false;
        }
    }
}
