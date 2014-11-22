#include "DrawableCreep.h"


DrawableCreep::DrawableCreep() : Creep()
{
	this->sprite = sprite;
	this->healthBar = new sf::RectangleShape();
	sprite->setPosition(0,0);
	healthBar->setSize(sf::Vector2f(24, 5));
	healthBar->setFillColor(sf::Color::Red);
	healthBar->setOutlineColor(sf::Color::Black);
	healthBar->setOutlineThickness(0.5);
	healthBar->setPosition(0, 0);
}

DrawableCreep::DrawableCreep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : Creep(hp, speed, defense, reward, strength, locationX, locationY, dir)
{
	this->sprite = sprite;
	this->healthBar = new sf::RectangleShape();
	sprite->setPosition(locationY * 24.0f, locationX * 24.0f);
	healthBar->setSize(sf::Vector2f(24, 5));
	healthBar->setFillColor(sf::Color::Red);
	healthBar->setOutlineColor(sf::Color::Black);
	healthBar->setOutlineThickness(0.5);
	healthBar->setPosition(sprite->getPosition().x, sprite->getPosition().y - 5);
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