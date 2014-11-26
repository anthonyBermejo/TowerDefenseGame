#pragma once
#include "DrawableCreep.h"
#include <iostream>

class Elf :
	public DrawableCreep
{
public:
	Elf(sf::Sprite* sprite);
	Elf(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Elf();
};

