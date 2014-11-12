#include "Wolf.h"


Wolf::Wolf(sf::Sprite* sprite) : DrawableCreep()
{
}

Wolf::Wolf(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

Wolf::~Wolf()
{
}

void Wolf::printCreep() const
{
	std::cout << "Hello. I am a Wolf!" << std::endl;
	Creep::printCreep();
}
