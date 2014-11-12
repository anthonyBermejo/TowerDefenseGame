#include "Ogre.h"

Ogre::Ogre(sf::Sprite* sprite) : DrawableCreep()
{
}

Ogre::Ogre(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

Ogre::~Ogre()
{
}

void Ogre::printCreep() const
{
	std::cout << "Hello. I am an Ogre!" << std::endl;
	Creep::printCreep();
}