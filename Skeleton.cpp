
#include "Skeleton.h"


Skeleton::Skeleton(sf::Sprite* sprite) : DrawableCreep()
{
}

Skeleton::Skeleton(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}


Skeleton::~Skeleton()
{
}

void Skeleton::printCreep() const
{
	std::cout << "Hello. I am a Skeleton!" << std::endl;
	Creep::printCreep();
}