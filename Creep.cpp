#include "Creep.h"
#include "Map.h"
#include <iostream>

using namespace std;

// Constructors
Creep::Creep() : Observable()
{
	hitPoints = 50;
	speed = 1;
	defense = 1;
	reward = 10;
	strength = 10;
	locationX = 0;
	locationY = 0;
	direction = Direction::RIGHT;
	movementTime = sf::Time::Zero; 
}

Creep::Creep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction direction) : Observable()
{
	this->hitPoints = hp;
	this->speed = speed;
	this->defense = defense;
	this->reward = reward;
	this->strength = strength;
	this->locationX = locationX;
	this->locationY = locationY;
	this->direction = direction;
	this->movementTime = sf::Time::Zero;
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

sf::Time Creep::getMovementTime() const
{
	return movementTime;
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

void Creep::setMovementTime(sf::Time time)
{
	this->movementTime = time;
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
		this->locationY = mapLocationY - 1;
	}
	else if (direction == Direction::RIGHT)
	{
		this->locationY = mapLocationY + 1;
	}
	else if (direction == Direction::UP)
	{
		this->locationX = mapLocationX - 1;
	}
	else
	{
		this->locationX = mapLocationX + 1;
	}

	// set new map location to enemy position
	if (map->getTile(locationX, locationY) != Map::TILE_TYPE::END)
		map->setTile(locationX, locationY, Map::TILE_TYPE::CREEP);

	notify();
}

void Creep::damageCreep(Player *player, int damage)
{
	hitPoints = hitPoints - damage;

	if (hitPoints <= 0) {
		player->setCoins(player->getCoins() + reward);
	}
	
	notify();
}

// Destructor
Creep::~Creep()
{
}
