#include "Creep.h"
#include "Map.h"
#include <iostream>

using namespace std;

// Constructors
Creep::Creep(TextureManager* texManager)
{
	hitPoints = 50;
	speed = 1;
	defense = 1;
	reward = 10;
	strength = 10;
	locationX = 0;
	locationY = 0;
	direction = Direction::RIGHT;
	spriteType = SPRITE_TYPE::SLIME;
	this->texManager = texManager;

	sprite1 = new sf::Sprite();
	sprite2 = new sf::Sprite();
}

Creep::Creep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction direction, TextureManager* texManager, SPRITE_TYPE spriteType)
{
	this->hitPoints = hp;
	this->speed = speed;
	this->defense = defense;
	this->reward = reward;
	this->strength = strength;
	this->locationX = locationX;
	this->locationY = locationY;
	this->direction = direction;
	this->texManager = texManager;
	this->spriteType = spriteType;

	// load sprites according to the type of the creep
	loadCreepSprites();
}


// Getters
int Creep::getHitPoints() const
{
	return hitPoints;
}

int Creep::getSpeed() const
{
	return speed;
}

int Creep::getDefense() const
{
	return defense;
}

int Creep::getReward() const
{
	return reward;
}

int Creep::getStrength() const
{
	return strength;
}

int Creep::getLocationX() const
{
	return locationX;
}

int Creep::getLocationY() const
{
	return locationY;
}

Direction Creep::getDirection() const
{
	return direction;
}

sf::Sprite* Creep::getSprite() const
{
	return sprite1;
}

// Setters
void Creep::setHitPoints(int hp)
{
	this->hitPoints = hp;
}

void Creep::setSpeed(int speed)
{
	this->speed = speed;
}

void Creep::setDefense(int defense)
{
	this->defense = defense;
}

void Creep::setReward(int reward)
{
	this->reward = reward;
}

void Creep::setStrength(int strength)
{
	this->strength = strength;
}

void Creep::setLocationX(int locationX)
{
	this->locationX = locationX;
}
void Creep::setLocationY(int locationY)
{
	this->locationY = locationY;
}

void Creep::setDirection(Direction direction)
{
	this->direction = direction;
}

// Custom methods

// Prints out the current values of a creep's attributes
void Creep::printCreep() const
{
	std::cout << "hitpoints: " << hitPoints << std::endl;
	std::cout << "speed: " << speed << std::endl;
	std::cout << "defense: " << defense << std::endl;
	std::cout << "reward: " << reward << std::endl;
	std::cout << "strength: " << strength << std::endl;
	std::cout << "locationX " << locationX << std::endl;
	std::cout << "locationY " << locationY << std::endl;
	std::cout << endl;
}

// Moves a creep on the map according to the direction they are going in
void Creep::move(Map *map)
{
	// initialize variables to the creep's current location
	int mapLocationX = this->locationX;
	int mapLocationY = this->locationY;

	// creep's location back to path tile
	if (map->getTile(mapLocationX, mapLocationY) != Map::TILE_TYPE::START && map->getTile(mapLocationX, mapLocationY) != Map::TILE_TYPE::END)
		map->setTile(mapLocationX, mapLocationY, Map::TILE_TYPE::PATH);

	// change x,y coordinates of an alien according to movement direction
	if (direction == Direction::LEFT)
	{
		this->locationX = mapLocationX - 1;
	}
	else if (direction == Direction::RIGHT)
	{
		this->locationX = mapLocationX + 1;
	}
	else if (direction == Direction::UP)
	{
		this->locationY = mapLocationY + 1;
	}
	else
	{
		this->locationY = mapLocationY - 1;
	}

	// set new map location to enemy position
	if (map->getTile(locationX, locationY) != Map::TILE_TYPE::END)
		map->setTile(locationX, locationY, Map::TILE_TYPE::CREEP);
}

void Creep::damageCreep(Player *player, int damage)
{
	hitPoints = (hitPoints + defense) - damage;

	if (hitPoints <= 0) {
		player->setCoins(player->getCoins() + reward);
	}
}

void Creep::loadCreepSprites()
{
	sprite1 = new sf::Sprite();
	sprite2 = new sf::Sprite();

	switch (spriteType)
	{
	case SPRITE_TYPE::SLIME:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(0, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24, 0, 24, 24));
		break;
	case SPRITE_TYPE::MAGE:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(24*2, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24*3, 0, 24, 24));
		break;
	case SPRITE_TYPE::SKELETON:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(24*4, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24*5, 0, 24, 24));
		break;
	case SPRITE_TYPE::OGRE:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(24 * 6, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24 * 7, 0, 24, 24));
		break;
	case SPRITE_TYPE::BULL:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(24 * 8, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24 * 9, 0, 24, 24));
		break;
	case SPRITE_TYPE::WOLF:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(24 * 10, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24 * 11, 0, 24, 24));
		break;
	case SPRITE_TYPE::ELF:
		sprite1->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite1->setTextureRect(sf::IntRect(24 * 12, 0, 24, 24));
		sprite2->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
		sprite2->setTextureRect(sf::IntRect(24 * 13, 0, 24, 24));
		break;
	}
}

// Destructor
Creep::~Creep()
{
}
