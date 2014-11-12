#include "Bull.h"

Bull::Bull(sf::Sprite* sprite) : DrawableCreep()
{
}

Bull::Bull(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

Bull::~Bull()
{
}

void Bull::printCreep() const
{
	std::cout << "Hello. I am a Bull!" << std::endl;
	Creep::printCreep();
}