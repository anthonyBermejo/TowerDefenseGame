#include "Blob.h"

Blob::Blob(sf::Sprite sprite) : DrawableCreep()
{
}

Blob::Blob(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

Blob::~Blob()
{}

void Blob::printCreep() const
{
	std::cout << "Hello. I am an Blob!" << std::endl;
	Creep::printCreep();
}
