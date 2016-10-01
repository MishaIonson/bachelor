using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Ship
    {
        // static variable, 'cause the weather is the same for each vehicle
        // 0 - no storm, 5 - Japan '11
        public static int stormIndex;
        public static String manufacturedCountry; // let's say that there is a monopoly and all ships are making there

        protected int capacity;
        private int crew;

        public int Crew
        {
            get
            {
                return crew;
            }
            set
            {
                if ((value > 0) && (value < 5000))
                    crew = value;
            }
        }


        private static float TIME_DELAY;

        //  permissible values: [1, 100]
        protected int maxSpeed;

        // overload constructors
        public Ship()
        {
            Console.WriteLine("Ship.Ship()");

            capacity = 1;
            crew = 1;
        }

        public Ship(int crew)
        {
            Console.WriteLine("Ship.Ship(int)");

            this.crew = crew;
            capacity = 1;
        }

        public Ship(int crew, int maxSpeed)
        {
            Console.WriteLine("Ship.Ship(int, int)");
            this.crew = crew;
            this.maxSpeed = maxSpeed;
        }

        // static constructor for static variable
        static Ship()
        {
            stormIndex = 2;
            manufacturedCountry = "China";
            TIME_DELAY = 0.1f;
        }

        public float getNeededTimeToGetTargetPoint(int distance)
        {
            if (stormIndex == 5)
                return Int64.MaxValue;
            else
                return (float) distance / maxSpeed + getApproximateTimeDelay((float) distance / maxSpeed);
        }

        // private because needs for internal time calculations only
        private float getApproximateTimeDelay(float time)
        {
            return (float) time * TIME_DELAY + (float) Math.Sqrt(TIME_DELAY * 10) + (float) Math.Tan(time) + stormIndex;
        }

        // checks if new value is ok
        public Boolean setCrew(int crewIn)
        {
            if ((crew > 0) && (crew < 5000))
            {
                crew = crewIn;
                return true;
            }
            else
                return false;
        }

        // protected method
        protected void sayHelloToSailor()
        {
            Console.WriteLine("hello, sailor!");
        }

    }
}
