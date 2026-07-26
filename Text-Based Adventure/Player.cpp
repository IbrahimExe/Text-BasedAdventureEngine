#include "Player.h"

Player::Player() 
{
    maxHealth = 100;
    health = maxHealth;
    rage = 0;
    eloquence = 50;
    hasMegaphone = false;

    // Starting Inventory
    inventory["Cough Syrup"] = 2;
    inventory["Cortisol Pills"] = 1; 
}

// 4. User Interface: The HUD Display
void Player::printHUD() const 
{
    std::cout << "\n=========================================\n";
    std::cout << " PLAYER STATUS \n";
    std::cout << "HP: [" << health << "/" << maxHealth << "] | ";
    std::cout << "Eloquence: [" << eloquence << "] | ";
    std::cout << "Rage: [" << rage << "]\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "🎒 INVENTORY: \n";

    bool hasItems = false;
    for (const auto& item : inventory) 
    {
        if (item.second > 0) 
        {
            std::cout << " - " << item.first << " (x" << item.second << ")\n";
            hasItems = true;
        }
    }
    if (!hasItems) 
    {
        std::cout << " - (Empty)\n";
    }
    std::cout << "=========================================\n\n";
}

// Stat Modifiers
void Player::takeDamage(int amount) 
{
    health -= amount;
    if (health < 0) health = 0;
}

void Player::heal(int amount) 
{
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Player::modifyEloquence(int amount) 
{
    eloquence += amount;
    if (eloquence < 0) eloquence = 0;
}

void Player::addRage(int amount) 
{
    rage += amount;
}

// Inventory Management
void Player::addItem(std::string itemName, int quantity) 
{
    inventory[itemName] += quantity;
}

bool Player::useItem(std::string itemName) 
{

    if (inventory.find(itemName) != inventory.end() && inventory[itemName] > 0) 
    {

        // Apply item effects
        if (itemName == "Cough Syrup") 
        {
            std::cout << "*Gulp* You chug the Cough Syrup. Your throat feels smooth. (+30 Eloquence)\n";
            modifyEloquence(30);
        }
        else if (itemName == "Cortisol Pills") 
        {
            std::cout << "You pop some Cortisol Pills. The stress fades, but the heart palpitations begin. (+40 HP)\n";
            heal(40);
        }
        else if (itemName == "Megaphone") 
        {
            std::cout << "You equip the Megaphone. Your next verbal assault will be deafening! (Next attack deals 2x damage)\n";
            hasMegaphone = true;
        }

        // Consume the item
        inventory[itemName]--;
        return true;
    }

    std::cout << "You don't have any " << itemName << " left!\n";
    return false;
}

// Combat Checks
bool Player::canAttack(int eloquenceCost) const 
{
    return eloquence >= eloquenceCost;
}

bool Player::isMegaphoneActive() const 
{
    return hasMegaphone;
}

void Player::consumeMegaphoneBuff() 
{
    hasMegaphone = false;
}

bool Player::isAlive() const 
{
    return health > 0;
}