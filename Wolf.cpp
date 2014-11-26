#include "Wolf.h"

// ___________________________________________________
//
// Class representing a Wolf creep
//
//____________________________________________________

// Constructors
Wolf::Wolf(sf::Sprite* sprite) : DrawableCreep()
{
}

Wolf::Wolf(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Destructor
Wolf::~Wolf()
{
}
