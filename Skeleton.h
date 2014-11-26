#pragma once
#include "DrawableCreep.h"
#include <iostream>

class Skeleton :
	public DrawableCreep
{
public:
	Skeleton(sf::Sprite* sprite);
	Skeleton(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Skeleton();
};

