#include "Elf.h"


Elf::Elf(sf::Sprite* sprite) : DrawableCreep()
{
}

Elf::Elf(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}


Elf::~Elf()
{
}

void Elf::printCreep() const
{
	std::cout << "Hello. I am an Elf!" << std::endl;
	Creep::printCreep();
}