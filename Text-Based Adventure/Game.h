#pragma once

#include "Player.h"
#include <string>

class Game 
{
private:
    Player player;

    // Narrative & Events
    void prologue();
    void ragebaitTrap();
    void epilogue();

    // Reusable battle system
    bool battle(std::string enemyName, int enemyHealth, int enemyDamage, std::string taunt);

public:
    // Main entry point to run the game
    void start();
};