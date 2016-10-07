using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class InhabitedPlanet : Planet
    {

        private int population;
        private LinkedList<LifeForm> inhabitantsList;

        public InhabitedPlanet(String name) : base(name)
        {
            inhabitantsList = new LinkedList<LifeForm>();
            setDefaultValues();
        }

        private void setDefaultValues()
        {
            base.Diameter = 1;
            base.distanceToStar = (Planet.INHABIT_DISTANCE_MIN + Planet.INHABIT_DISTANCE_MAX) / 2;

            population = 1;
        }

        public override bool isInhabited()
        {
            return true;
        }

        public void addNewInhabitant(LifeForm inhabitant)
        {
            if (inhabitantsList != null)
                inhabitantsList.AddLast(inhabitant);
        }

        public Boolean containsLifeForm(LifeForm lifeForm)
        {
            if (inhabitantsList != null)
                return inhabitantsList.Contains(lifeForm);

            return false;
        }
    }
}
