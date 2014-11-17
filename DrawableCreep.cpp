#include "DrawableCreep.h"


DrawableCreep::DrawableCreep() : Creep()
{
	this->sprite = sprite;
	this->healthBar = new sf::RectangleShape();
}

DrawableCreep::DrawableCreep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : Creep(hp, speed, defense, reward, strength, locationX, locationY, dir)
{
	this->sprite = sprite;
	this->healthBar = new sf::RectangleShape();
}

DrawableCreep::~DrawableCreep()
{
}

sf::Sprite* DrawableCreep::getSprite() const
{
	return sprite;
}

sf::RectangleShape* DrawableCreep::getHealthBar() const
{
	return healthBar;
}