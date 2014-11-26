#include "Mage.h"

// ___________________________________________________
//
// Class representing a Mage creep
//
//____________________________________________________

// Constructors
Mage::Mage(sf::Sprite* sprite) : DrawableCreep()
{
}

Mage::Mage(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Destructor
Mage::~Mage()
{
}