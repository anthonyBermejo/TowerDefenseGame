#pragma once
#include "DrawableCreep.h"
#include <iostream>

class Wolf :
	public DrawableCreep
{
public:
	Wolf(sf::Sprite* sprite);
	Wolf(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Wolf();
};

