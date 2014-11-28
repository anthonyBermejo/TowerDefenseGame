#include "DrawableCreepSquad.h"

// ___________________________________________________
//
// Class representing a collection of drawable Creeps
// with UI components such as sprites
//
//____________________________________________________

// Constructors
DrawableCreepSquad::DrawableCreepSquad(Map* map, TextureManager* texManager) : CreepSquad(map, texManager)
{
	this->creepSquad = CreepSquad::getCreeps();
	this->creepTotalHP = CreepSquad::getCreepTotalHP();
}

// Destructor
DrawableCreepSquad::~DrawableCreepSquad()
{
}

// Update method that runs in every iteration of the game loop
void DrawableCreepSquad::Update(Player* player, sf::Time elapsedTime)
{
	CreepSquad::Update(player, elapsedTime);
}

// Update method used when notify is called on classes it observes
void DrawableCreepSquad::update() {

	creepSquad = CreepSquad::getCreeps();

	for (int i = 0; i < (int)creepSquad.size(); ++i) {
		// set position of the sprite
		if (creepSquad[i]->getHitPoints() > 0) {
			sf::Sprite* creepSprite = creepSquad[i]->getSprite();
			creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f, creepSquad[i]->getLocationX() * 24.0f);

			// display health bar
			displayHealthBar(creepSquad[i]);

			//check if creep is slowed
			if (creepSquad[i]->isSlowedDown() && creepSquad[i]->getSprite()->getColor() != sf::Color::Blue)
				creepSquad[i]->getSprite()->setColor(sf::Color::Blue);
		}
	}
}

// Draws the sprites of each creep
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

// Draws the health bars of each creep
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