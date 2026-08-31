using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C__Text_BasedAdventure
{
    public class Game
    {
        private Player player;

        public Game()
        {
            player = new Player();
        }

        public void Start()
        {
            Prologue();

            Console.WriteLine("\n--- TUTORIAL STAGE ---");
            if (!Battle("Gustavo", 40, 5, "Howdy, buddy! Prepare to talk about Destiny 2!"))
            {
                return; // Player died, end game
            }

            RagebaitTrap();
            if (!player.IsAlive()) return; // Check if the trap killed the player

            Console.WriteLine("\n--- STAGE 2 ---");
            if (!Battle("Salmon", 80, 15, "I'm the fastest yapper in the West, guey!"))
            {
                return;
            }

            // Give player a reward before the boss
            Console.WriteLine("\n[Loot Drop] Salmon dropped a Megaphone, Cough Syrup, and Cortisol Pills!");
            player.AddItem("Megaphone", 1);
            player.AddItem("Cough Syrup", 1);
            player.AddItem("Cortisol Pills", 2);

            Console.WriteLine("\n--- FINAL BOSS ---");
            if (!Battle("Santi", 150, 25, "You look triggered, friend! I am the ultimate Ragebaiter!"))
            {
                return;
            }

            Epilogue(); // Win condition met
        }

        private void Prologue()
        {
            Console.WriteLine("=========================================");
            Console.WriteLine("      RAGEBAIT: RAGE OF THE WEST         ");
            Console.WriteLine("=========================================");
            Console.WriteLine("You walk into a dusty LaSalle classroom.");
            Console.WriteLine("Your goal: Defeat the schools biggest trolls using only your words.");
            Console.WriteLine("Manage your Health, Eloquence, and Rage.");
        }

        private void RagebaitTrap()
        {
            Console.WriteLine("\n[EVENT: RAGEBAITED!]");
            Console.WriteLine("As you walk to the next Classroom, you spot a sign that says:");
            Console.WriteLine("\"Unreal is the best engine for making games, way better than GameMaker!\"");
            Console.WriteLine("It's pure RAGEBAIT! You get unreasonably angry, popping a blood vessel.");

            player.TakeDamage(20);
            player.AddRage(15);

            Console.WriteLine("You lose 20 HP but gain 15 Rage!");
        }

        private void Epilogue()
        {
            Console.WriteLine("\n=========================================");
            Console.WriteLine("              VICTORY!                   ");
            Console.WriteLine("=========================================");
            Console.WriteLine("You have roasted Santi into oblivion. LaSalle is yours!");
            Console.WriteLine("You are the most eloquent yapper in the West. Thanks for playing!");
        }

        private bool Battle(string enemyName, int enemyHealth, int enemyDamage, string taunt)
        {
            Console.WriteLine($"\n{enemyName} steps up! \"{taunt}\"");

            while (player.IsAlive() && enemyHealth > 0)
            {
                player.PrintHUD();
                Console.WriteLine($"ENEMY: {enemyName} | HP: [{enemyHealth}]");
                Console.WriteLine("\nChoose an action:");
                Console.WriteLine("1. Roast (Cost: 10 Eloquence)");
                Console.WriteLine("2. Use Cough Syrup (Restore Eloquence)");
                Console.WriteLine("3. Use Cortisol Pills (Restore HP)");
                Console.WriteLine("4. Equip Megaphone (Double Damage)");
                Console.Write("> ");

                // C# specific input handling to prevent crashes from bad input
                if (!int.TryParse(Console.ReadLine(), out int choice))
                {
                    choice = 0; // Default to invalid if they type letters
                }
                Console.WriteLine();

                // Handle Player Turn
                if (choice == 1)
                {
                    if (player.CanAttack(10))
                    {
                        player.ModifyEloquence(-10);
                        int damage = 20;

                        if (player.HasMegaphoneBuff)
                        {
                            damage *= 2;
                            player.ConsumeMegaphoneBuff();
                            Console.Write("MAXIMUM VOLUME! ");
                        }

                        Console.WriteLine($"You roasted {enemyName} for {damage} emotional damage!");
                        enemyHealth -= damage;
                    }
                    else
                    {
                        Console.WriteLine("You stammer! Not enough Eloquence to speak!");
                    }
                }
                else if (choice == 2) { player.UseItem("Cough Syrup"); }
                else if (choice == 3) { player.UseItem("Cortisol Pills"); }
                else if (choice == 4) { player.UseItem("Megaphone"); }
                else
                {
                    Console.WriteLine("Invalid choice! You just stand there awkwardly.");
                }

                // Enemy Turn
                if (enemyHealth > 0)
                {
                    Console.WriteLine($"{enemyName} fires back an insult, dealing {enemyDamage} damage!");
                    player.TakeDamage(enemyDamage);
                    player.AddRage(10); // Taking damage builds rage
                }
            }

            if (!player.IsAlive())
            {
                Console.WriteLine("\n GAME OVER ");
                Console.WriteLine("Your feelings were hurt too badly. You collapse in the LaSalle bathrooms.");
                return false;
            }

            Console.WriteLine($"\n You defeated {enemyName}!");
            return true;
        }
    }
}