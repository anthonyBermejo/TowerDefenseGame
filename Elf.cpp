#include "Elf.h"

// ___________________________________________________
//
// Class representing an Elf creep
//
//____________________________________________________

// Constructors
Elf::Elf(sf::Sprite* sprite) : DrawableCreep()
{
}

Elf::Elf(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Destructor
Elf::~Elf()
{
}