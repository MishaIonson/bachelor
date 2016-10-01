using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class MilitaryShip : Ship
    {
        private int wearponNumber;

        public int WearponNumber
        {
            get
            {
                return wearponNumber;
            }
            set
            {
                if ((value >= 0) && (value <= 9))
                    wearponNumber = value;
            }
        }

        private int armor;

        // redefined constructor
        public MilitaryShip(int armor)
        {
            this.armor = armor;
            wearponNumber = 0;
        }

        // used base class constructors
        public MilitaryShip(int crew, int capacity) : base(crew, capacity)
        {
            Console.WriteLine("MilitaryShips.MilitaryShip(int, int)");
            wearponNumber = 0;
        }

        public virtual Boolean hasFireExterminatedTarget()
        {
            Console.WriteLine("MilitaryShips.hasFireExterminatedTarget()");

            if (new Random().Next(0, 12 - wearponNumber) == 1)
                return true;
            else
                return false;
        }
    }
}
