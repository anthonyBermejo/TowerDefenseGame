#pragma once
#include "Creep.h"

class DrawableCreep : public Creep
{
public:
	DrawableCreep();
	DrawableCreep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite);
	virtual ~DrawableCreep();
	sf::Sprite* getSprite() const;
private:
	sf::Sprite* sprite;
};

