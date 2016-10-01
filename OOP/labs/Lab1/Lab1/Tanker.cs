using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Tanker : Ship
    {
        private int weightCapacity;

        public int WeightCapacity
        {
            get
            {
                return weightCapacity;
            }
            set
            {
                if ((value >= 10) && (value <= 900000))
                    weightCapacity = value;
            }
        }
       
        public Tanker()
        {
            // protected field testing
            maxSpeed = 10;
        }

        public int getMaxSpeed()
        {
            return maxSpeed;
        }
    }
}
