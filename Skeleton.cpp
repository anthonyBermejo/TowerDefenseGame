
#include "Skeleton.h"

// ___________________________________________________
//
// Class representing a skeleton creep
//
//____________________________________________________

// Cosntructors
Skeleton::Skeleton(sf::Sprite* sprite) : DrawableCreep()
{
}

Skeleton::Skeleton(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Destructor
Skeleton::~Skeleton()
{
}
