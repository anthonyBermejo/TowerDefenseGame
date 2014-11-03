#include "CreepSquad.h"

const int MAX_NUMBER_OF_CREEPS = 10;

CreepSquad::CreepSquad(Map* map, TextureManager* texManager)
{
	this->creepSquad = vector<Creep*>(MAX_NUMBER_OF_CREEPS);
	this->map = map;
	this->texManager = texManager;
}

vector<Creep*> CreepSquad::getCreeps(){ return creepSquad; }

void CreepSquad::move(Player* player, sf::RenderWindow* w)
{
	removeDeadCreeps();

	for (int i = 0; i < (int)creepSquad.size(); ++i) {

		// if creep reaches the endtile, delete the object and remove coins from player
		if (checkEndTile(creepSquad[i], player)) {

			// delete creep object and remove from vector of creeps
			delete creepSquad[i];
			creepSquad[i] = NULL;
			creepSquad.erase(creepSquad.begin() + i);
			i--;

			// print out player's coins have been deducted from
			cout << "Creep reached end tile! Player now has " << player->getCoins() << " coins!" << endl;
		}
		else
			// move creep on map
			checkMove(creepSquad[i]);

		creepSquad[i]->getSprite().setPosition(creepSquad[i]->getLocationX() * 24, creepSquad[i]->getLocationY() * 24);
		w->draw(creepSquad[i]->getSprite());
	}
}

void CreepSquad::resetCreepSquad(int level, sf::RenderWindow* w)
{
	creepSquad.clear();

	// get x,y position of start tile of the map
	int startLocationX = map->getStart()[0];
	int startLocationY = map->getEnd()[1];

	switch (level)
	{
	case 1:
		creepSquad.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		break;
	case 2:
		creepSquad.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		creepSquad.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		creepSquad.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		creepSquad.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		creepSquad.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
	case 3:
		creepSquad.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		creepSquad.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		creepSquad.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		creepSquad.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		creepSquad.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
	case 4:
		creepSquad.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		creepSquad.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		creepSquad.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		creepSquad.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		creepSquad.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		break;
	}

	for (int i = 0; i < creepSquad.size(); ++i) {

		creepSquad[i]->getSprite().setPosition(creepSquad[i]->getLocationX() * 24, creepSquad[i]->getLocationY() * 24);
		w->draw(creepSquad[i]->getSprite());
	}
}

// Check if a creep is able to move in a specific direction
void CreepSquad::checkMove(Creep* creep)
{
	Direction creepDirection = creep->getDirection();
	int locationX = creep->getLocationX();
	int locationY = creep->getLocationY();

	// if a creep's project direction is an ENVIRONMENT tile,
	// check the other directions if it is able to move (there is a path there) and set the direction to that creep
	// else, move along the current direction
	if (creepDirection == Direction::LEFT)
	{
		if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::ENV) {
			if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::DOWN);
			}

			if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::UP);
			}
		}
	}
	else if (creepDirection == Direction::RIGHT)
	{
		if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::ENV)
		{

			if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::DOWN);
			}

			if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::UP);
			}
		}
	}
	else if (creepDirection == Direction::UP)
	{
		if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::ENV)
		{
			if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::LEFT);
			}

			if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::RIGHT);
			}
		}
	}
	else
	{
		if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::ENV)
		{
			if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::LEFT);
			}

			if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::PATH) {
				creep->setDirection(Direction::RIGHT);
			}
		}
	}

	creep->move(map);
}

// Checks if a creep has entered an end tile
bool CreepSquad::checkEndTile(Creep* creep, Player* player)
{
	Direction direction = creep->getDirection();
	int locationX = creep->getLocationX();
	int locationY = creep->getLocationY();

	bool creepAtEndTile = false;

	// if the direction the creep is going in has an end tile, set boolean to true
	if ((direction == Direction::LEFT && map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END) ||
		(direction == Direction::RIGHT && map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::END) ||
		(direction == Direction::UP && map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::END) ||
		(direction == Direction::DOWN && map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::END))
		creepAtEndTile = true;

	// if the creep is at an end tile 
	if (creepAtEndTile) {
		// remove coins from player according to value of creep's strength
		player->setCoins(player->getCoins() - creep->getStrength());
	}

	// return if a creep has landed on the end tile
	return creepAtEndTile;
}

void CreepSquad::removeDeadCreeps()
{
	for (int i = 0; i < (int)creepSquad.size(); ++i) {
		if (creepSquad[i]->getHitPoints() <= 0) {
			// delete creep object and remove from vector of creeps
			delete creepSquad[i];
			creepSquad[i] = NULL;
			creepSquad.erase(creepSquad.begin() + i);
			i--;
		}
	}
}

CreepSquad::~CreepSquad()
{
	for (int i = 0; i < (int)creepSquad.size(); ++i)
		delete creepSquad[i];
}
