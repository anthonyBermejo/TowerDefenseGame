#pragma once

#include "DrawableCreep.h"
#include <iostream>

class Bull : public DrawableCreep
{
public:
	Bull(sf::Sprite* sprite);
	Bull(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Bull();
};

