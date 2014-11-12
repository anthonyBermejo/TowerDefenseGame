#pragma once
#include "DrawableCreep.h"
#include <iostream>

class Mage : public DrawableCreep
{
public:
	Mage(sf::Sprite* sprite);
	Mage(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Mage();
	void printCreep() const;
};

