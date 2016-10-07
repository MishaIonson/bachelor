using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class LifeForm
    {
        public const int HUMAN_INTELLIGENCE = 0;
        public const int COW_INTELLIGENCE = 1;
        public const int PLANT_INTELLIGENCE = 2;

        public String name;

        public int intelligenceID;

        public LifeForm()
        {
            name = "LifeFormX";
            intelligenceID = 2;
        }
    }
}
