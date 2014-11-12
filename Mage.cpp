#include "Mage.h"

Mage::Mage(sf::Sprite* sprite) : DrawableCreep()
{
}

Mage::Mage(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

Mage::~Mage()
{
}

void Mage::printCreep() const
{
	std::cout << "Hello. I am a Mage!" << std::endl;
	Creep::printCreep();
}