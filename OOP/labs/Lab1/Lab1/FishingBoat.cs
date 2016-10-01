using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class FishingBoat : Ship
    {
        /* let's say that all fishing boats are almoust similar comparing to considering types of ships,
         * so this class gonna be static and needs only for some basics calculations about
         */

        public static int capacity;
        // the only place where fishing boats are allowed to be now
        private static String watersType;
        
        // private constructor saves from FishingBoat type object initialisation
         private FishingBoat()
        { }

        static FishingBoat()
        {
            capacity = 12;
            watersType = "lake";
        }

        // hold - spot for catched fish on the boat
        public static int howFastHoldWillBeFull(int timeOnWater, int fishCatched)
        {
            if (fishCatched >= capacity)
                return 0;

            return (capacity - fishCatched) / (fishCatched / timeOnWater);
        }

        
        public static String WatersType
        {
            get
            {
                return watersType;
            }
            set// checking if input data is ok
            {
                if ((value == "ocean") || (value == "sea") || (value == "river") || (value == "lake"))
                    watersType = value;
            }
        }


    }
}
