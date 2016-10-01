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
            Ship shipObject = new Ship();
            
            // too big crew input test
            Console.WriteLine(shipObject.Crew);
            shipObject.Crew = 120000;
            Console.WriteLine(shipObject.Crew);
            //
            
            // base constructor also has to be called
            MilitaryShip militaryShip = new MilitaryShip(2, 12);
            //

            // abstract method testing
            Submarine submarine = new Submarine(1);
            militaryShip.hasFireExterminatedTarget();
            //

            // protected field and method testing
            Tanker tanker = new Tanker();
            Console.WriteLine(tanker.getMaxSpeed());
            //

            Console.ReadLine();
        }
    }
}
