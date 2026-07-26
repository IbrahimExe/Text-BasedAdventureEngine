#pragma once

#include "Player.h"
#include <string>

class RagebaitGame 
{
private:
    Player player;

    // narrative/ events
    void prologue();
    void ragebaitTrap();
    void epilogue();

    // Reusable battle system
    bool battle(std::string enemyName, int enemyHealth, int enemyDamage, std::string taunt);

public:
    // entry point to run the game
    void start();
};