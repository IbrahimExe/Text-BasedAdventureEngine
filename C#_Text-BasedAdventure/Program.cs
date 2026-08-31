// See https://aka.ms/new-console-template for more information
using System;

namespace C__Text_BasedAdventure
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // instantiate the game engine
            Game myGame = new Game();

            // start the game loop
            myGame.Start();

            // Keep the console open after the game ends
            Console.WriteLine("\nPress Enter to exit (Ik ironic)...");
            Console.ReadLine();
        }
    }
}
