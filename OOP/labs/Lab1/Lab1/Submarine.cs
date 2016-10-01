using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Submarine : MilitaryShip
    {
        private int maxDeep;

        public int MaxDeep
        {
            get
            {
                return maxDeep;
            }
            set // let's say that there is no way to go deeper then 10000
            {
                if ((value > 0) && (value < 10000))
                    maxDeep = value;
            }
        }

        // defines if object has nuclear wearpon
        public Boolean hasNuclearWearpon;
        
        public String typeName;

        public Submarine(int armor) : base(armor)
        {
            typeName = "TypicalSubmarine-1";
        }

        public override Boolean hasFireExterminatedTarget()
        {
            Console.WriteLine("Submarine.hasFireExterminatedTarget()");

            if (new Random().Next(0, 12 - base.WearponNumber) == 1)
                return true;
            else
                return false;
        }
    }
}
