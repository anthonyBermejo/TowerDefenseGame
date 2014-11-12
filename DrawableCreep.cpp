#include "DrawableCreep.h"


DrawableCreep::DrawableCreep() : Creep()
{
	this->sprite = sprite;
}

DrawableCreep::DrawableCreep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : Creep(hp, speed, defense, reward, strength, locationX, locationY, dir)
{
	this->sprite = sprite;
}

DrawableCreep::~DrawableCreep()
{
}

sf::Sprite* DrawableCreep::getSprite() const
{
	return sprite;
}
