#include "Ogre.h"

// ___________________________________________________
//
// Class representing an Ogre creep
//
//____________________________________________________

// Constructors
Ogre::Ogre(sf::Sprite* sprite) : DrawableCreep()
{
}

Ogre::Ogre(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Destructors
Ogre::~Ogre()
{
}
