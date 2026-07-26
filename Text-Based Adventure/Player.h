#pragma once

#include <iostream>
#include <string>
#include <map>

class Player 
{
private:
    int health;
    int maxHealth;
    int rage;
    int eloquence; 

    // Maps item name to the quantity owned
    std::map<std::string, int> inventory;

    // Status Effects
    bool hasMegaphone;

public:
    Player();

    // hud
    void printHUD() const;

    // Stat Modifiers
    void takeDamage(int amount);
    void heal(int amount);
    void modifyEloquence(int amount);
    void addRage(int amount);

    // Inventory Management
    void addItem(std::string itemName, int quantity);
    bool useItem(std::string itemName);

    // Combat checks
    bool canAttack(int eloquenceCost) const;
    void consumeMegaphoneBuff();
    bool isMegaphoneActive() const;
    bool isAlive() const;
};