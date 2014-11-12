#pragma once

#include "DrawableCreep.h"
#include <iostream>

class Blob : public DrawableCreep
{
public:
	Blob(sf::Sprite sprite);
	Blob(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Blob();
	void printCreep() const;
};

