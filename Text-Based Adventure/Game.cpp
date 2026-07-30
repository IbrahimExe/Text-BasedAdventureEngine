#include "Game.h"
#include <iostream>

void RagebaitGame::start() 
{
    prologue();

    std::cout << "\n--- TUTORIAL STAGE ---\n";
    if (!battle("Gustavo", 40, 5, "Howdy, buddy! Prepare to talk about Destiny 2!")) 
    {
        return; // Player died, end game
    }

    ragebaitTrap();
    if (!player.isAlive()) return; // Check if the trap killed the player


    std::cout << "\n--- STAGE 2 ---\n";
    if (!battle("Salmon", 80, 15, "I'm the fastest yapper in the West, guey!")) 
    {
        return;
    }

    // Give player a reward before the boss
    std::cout << "\n[Loot Drop] Salmon dropped a Megaphone and some Cough Syrup!\n";
    player.addItem("Megaphone", 1);
    player.addItem("Cough Syrup", 1);
    player.addItem("Cortisol Pills", 2);


    std::cout << "\n--- FINAL BOSS ---\n";
    if (!battle("Santi", 150, 25, "You look triggered, friend! I am the ultimate Ragebaiter!")) 
    {
        return;
    }

    epilogue(); // Win condition met
}

void RagebaitGame::prologue()
{
    std::cout << "=========================================\n";
    std::cout << "      RAGEBAIT: RAGE OF THE WEST   \n";
    std::cout << "=========================================\n";
    std::cout << "You walk into a dusty LaSalle classroom.\n";
    std::cout << "Your goal: Defeat the schools biggest trolls using only your words.\n";
    std::cout << "Manage your Health, Eloquence, and Rage.\n";
}

void RagebaitGame::ragebaitTrap()
{
    std::cout << "\n[EVENT: RAGEBAITED!]\n";
    std::cout << "As you walk to the next Classroom, you spot a sign that says:\n";
    //std::cout << "\"C++ is just a worse version of Java.\"\n";    
    std::cout << "\"Unreal is the best engine for making games, way better than GameMaker!\"\n";
    std::cout << "It's pure RAGEBAIT! You get unreasonably angry, popping a blood vessel.\n";

    player.takeDamage(20);
    player.addRage(15);

    std::cout << "You lose 20 HP but gain 15 Rage!\n";
}

void RagebaitGame::epilogue()
{
    std::cout << "\n=========================================\n";
    std::cout << "              VICTORY!                   \n";
    std::cout << "=========================================\n";
    std::cout << "You have roasted Santi into oblivion. LaSalle is yours!\n";
    std::cout << "You are the most eloquent yapper in the West. Thanks for playing!\n";
}

bool RagebaitGame::battle(std::string enemyName, int enemyHealth, int enemyDamage, std::string taunt)
{
    std::cout << "\n" << enemyName << " steps up! \"" << taunt << "\"\n";

    while (player.isAlive() && enemyHealth > 0) 
    {
        player.printHUD();
        std::cout << "ENEMY: " << enemyName << " | HP: [" << enemyHealth << "]\n";
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Roast (Cost: 10 Eloquence)\n";
        std::cout << "2. Use Cough Syrup (Restore Eloquence)\n";
        std::cout << "3. Use Cortisol Pills (Restore HP)\n";
        std::cout << "4. Equip Megaphone (Double Damage)\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;
        std::cout << "\n";

        // Handle Player Turn
        if (choice == 1) 
        {
            if (player.canAttack(10)) 
            {
                player.modifyEloquence(-10);
                int damage = 20;

                if (player.isMegaphoneActive()) 
                {
                    damage *= 2;
                    player.consumeMegaphoneBuff();
                    std::cout << " MAXIMUM VOLUME! ";
                }

                std::cout << "You roasted " << enemyName << " for " << damage << " emotional damage!\n";
                enemyHealth -= damage;
            }
            else 
            {
                std::cout << "You stammer! Not enough Eloquence to speak!\n";
            }
        }
        else if (choice == 2) { player.useItem("Cough Syrup"); }

        else if (choice == 3) { player.useItem("Cortisol Pills"); }

        else if (choice == 4) { player.useItem("Megaphone"); }
        else 
        {
            std::cout << "Invalid choice! You just stand there awkwardly.\n";
        }

        // enemy Turn
        if (enemyHealth > 0)
        {
            std::cout << enemyName << " fires back an insult, dealing " << enemyDamage << " damage!\n";
            player.takeDamage(enemyDamage);
            player.addRage(10); // Taking damage builds rage
        }
    }

    if (!player.isAlive()) 
    {
        std::cout << "\n GAME OVER \n";
        std::cout << "Your feelings were hurt too badly. You collapse in the LaSalle bathrooms.\n";
        return false;
    }

    std::cout << "\n You defeated " << enemyName << "!\n";
    return true;
}
