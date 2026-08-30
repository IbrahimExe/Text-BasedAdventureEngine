using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C__Text_BasedAdventure
{
    public class Player
    {
        public int Health { get; private set; }
        public int MaxHealth { get; private set; }
        public int Rage { get; private set; }
        public int Eloquence { get; private set; }
        public bool HasMegaphoneBuff { get; private set; }

        // use dicrionary instead of C++ map
        private Dictionary<string, int> inventory;

        public Player()
        {
            MaxHealth = 100;
            Health = MaxHealth;
            Rage = 0;
            Eloquence = 50;
            HasMegaphoneBuff = false;

            inventory = new Dictionary<string, int>
            {
                { "Cough Syrup", 2 },
                { "Cortisol Pills", 1 }
            };
        }

        public void PrintHUD()
        {
            Console.WriteLine("\n=========================================");
            Console.WriteLine(" PLAYER STATUS ");
            Console.WriteLine($"HP: [{Health}/{MaxHealth}] | Eloquence: [{Eloquence}] | Rage: [{Rage}]");
            Console.WriteLine("-----------------------------------------");
            Console.WriteLine(" INVENTORY: ");

            bool hasItems = false;
            foreach (var item in inventory)
            {
                if (item.Value > 0)
                {
                    Console.WriteLine($" - {item.Key} (x{item.Value})");
                    hasItems = true;
                }
            }
            if (!hasItems)
            {
                Console.WriteLine(" - (Empty)");
            }
            Console.WriteLine("=========================================\n");
        }

        public void TakeDamage(int amount)
        {
            Health -= amount;
            if (Health < 0) Health = 0;
        }

        public void Heal(int amount)
        {
            Health += amount;
            if (Health > MaxHealth) Health = MaxHealth;
        }

        public void ModifyEloquence(int amount)
        {
            Eloquence += amount;
            if (Eloquence < 0) Eloquence = 0;
        }

        public void AddRage(int amount)
        {
            Rage += amount;
        }

        public void AddItem(string itemName, int quantity)
        {
            if (inventory.ContainsKey(itemName))
            {
                inventory[itemName] += quantity;
            }
            else
            {
                inventory[itemName] = quantity;
            }
        }

        public bool UseItem(string itemName)
        {
            if (inventory.ContainsKey(itemName) && inventory[itemName] > 0)
            {
                if (itemName == "Cough Syrup")
                {
                    Console.WriteLine("*Gulp* You chug the Cough Syrup. Your throat feels smooth. (+30 Eloquence)");
                    ModifyEloquence(30);
                }
                else if (itemName == "Cortisol Pills")
                {
                    Console.WriteLine("You pop some Cortisol Pills. The stress fades, but the heart palpitations begin. (+40 HP)");
                    Heal(40);
                }
                else if (itemName == "Megaphone")
                {
                    Console.WriteLine("You equip the Megaphone. Your next verbal assault will be deafening! (Next attack deals 2x damage)");
                    HasMegaphoneBuff = true;
                }

                inventory[itemName]--;
                return true;
            }

            Console.WriteLine($"You don't have any {itemName} left!");
            return false;
        }


        public bool CanAttack(int eloquenceCost) => Eloquence >= eloquenceCost;

        public void ConsumeMegaphoneBuff() => HasMegaphoneBuff = false;

        public bool IsAlive() => Health > 0;
    }

}