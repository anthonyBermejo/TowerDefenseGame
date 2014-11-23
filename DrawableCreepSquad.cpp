#include "DrawableCreepSquad.h"


DrawableCreepSquad::DrawableCreepSquad(Map* map, TextureManager* texManager) : CreepSquad(map, texManager)
{
	this->creepSquad = CreepSquad::getCreeps();
	this->creepTotalHP = CreepSquad::getCreepTotalHP();
}

DrawableCreepSquad::~DrawableCreepSquad()
{
}

void DrawableCreepSquad::Update(Player* player, sf::Time elapsedTime)
{
	CreepSquad::Update(player, elapsedTime);
}

void DrawableCreepSquad::update() {

	creepSquad = CreepSquad::getCreeps();

	for (int i = 0; i < (int)creepSquad.size(); ++i) {
		// set position of the sprite
		if (creepSquad[i]->getHitPoints() > 0) {
			sf::Sprite* creepSprite = creepSquad[i]->getSprite();
			creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f, creepSquad[i]->getLocationX() * 24.0f);

			// display health bar
			displayHealthBar(creepSquad[i]);
		}
	}
}

void DrawableCreepSquad::Draw(sf::RenderWindow* w)
{
	creepSquad = CreepSquad::getCreeps();

	for (int i = 0; i < (int)creepSquad.size(); ++i)
	{
		if (creepSquad[i]->getHitPoints() > 0) {
			w->draw(*(creepSquad[i]->getSprite()));
		}
	}

	// need 2nd for loop or else health bars will be hidden under creeps
	for (int i = 0; i < (int)creepSquad.size(); ++i)
	{
		if (creepSquad[i]->getHitPoints() > 0) {
			w->draw(*(creepSquad[i]->getHealthBar()));
		}
	}
}

void DrawableCreepSquad::displayHealthBar(DrawableCreep* creep)
{
	creepTotalHP = CreepSquad::getCreepTotalHP();

	sf::RectangleShape* healthBar = creep->getHealthBar();
	healthBar->setSize(sf::Vector2f(((float)creep->getHitPoints() / (float)creepTotalHP) * 24, 5));
	healthBar->setFillColor(sf::Color::Red);
	healthBar->setOutlineColor(sf::Color::Black);
	healthBar->setOutlineThickness(0.5);
	healthBar->setPosition(creep->getSprite()->getPosition().x, creep->getSprite()->getPosition().y - 5);
}