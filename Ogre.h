#pragma once
#include "DrawableCreep.h"
#include <iostream>

class Ogre :
	public DrawableCreep
{
public:
	Ogre(sf::Sprite* sprite);
	Ogre(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~Ogre();
};

