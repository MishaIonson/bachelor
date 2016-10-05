using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            // static fields demonstration
            Console.WriteLine("Static field: " + Planet.INHABIT_DISTANCE_MAX + "\n");

            // properies demonstration
            SpaceObject spaceObject = new SpaceObject("object1");
            spaceObject.Weight = -1;
            Console.WriteLine("properties demo: " + spaceObject.Weight);
            spaceObject.Weight = 12;
            Console.WriteLine("properties demo: " + spaceObject.Weight + "\n");

            // constructor demonstration
            Console.WriteLine("constructor demo:");
            Star star = new Star("Star1");
            Console.WriteLine("\n");

            // virtual and overrided methods demonstration
            Planet mars = new Planet("Mars");
            Console.WriteLine("virtual: " + spaceObject.getNeededTimeToGetTemperature(12345));
            Console.WriteLine("overrided: " + mars.getNeededTimeToGetTemperature(12345));


            Console.ReadKey();
        }
    }
}
