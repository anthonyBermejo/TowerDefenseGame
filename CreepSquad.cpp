#include "CreepSquad.h"

const int MAX_NUMBER_OF_CREEPS = 10;

CreepSquad::CreepSquad(Map* map, TextureManager* texManager)
{
	this->creepSquad = vector<Creep*>(MAX_NUMBER_OF_CREEPS);
	this->map = map;
	this->texManager = texManager;
}

void CreepSquad::move(Player* player, sf::RenderWindow* w)
{
	for (int i = 0; i < (int)creepSquad.size(); ++i) {

		// if creep reaches the endtile, delete the object and remove coins from player
		if (checkEndTile(creepSquad[i], map, player)) {

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
			checkMove(creepSquad[i], map);

		creepSquad[i]->getSprite().setPosition(creepSquad[i]->getLocationX() * 24, creepSquad[i]->getLocationY() * 24);
		w->draw(creepSquad[i]->getSprite());
	}
}

void CreepSquad::resetCreepSquad(int level)
{
	creepSquad.clear();

	switch (level)
	{
	case 1:
		creepSquad.push_back(new Creep(1, 2, 1, 50, 50, 1, 1, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(1, 2, 1, 50, 50, 0, 1, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(1, 2, 1, 50, 50, 0, 1, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		creepSquad.push_back(new Creep(1, 2, 1, 50, 50, 0, 1, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		break;
	}

	// spawn creep on map at it's starting x,y location
	for (int i = 0; i < creepSquad.size(); ++i) {
		// set creep on the map to it's x,y location

		// get x,y position of start tile of the map

		// set all starting x,y positions of creeps
		creepSquad[i]->setLocationX(0);
		creepSquad[i]->setLocationY(1);
		creepSquad[i]->getSprite().setPosition(creepSquad[i]->getLocationX() * 24, creepSquad[i]->getLocationY() * 24);
	}
}

// Check if a creep is able to move in a specific direction
void CreepSquad::checkMove(Creep* creep, Map *map)
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
bool CreepSquad::checkEndTile(Creep* creep,Map* map, Player* player)
{
	Direction direction = creep->getDirection();
	int locationX = creep->getLocationX();
	int locationY = creep->getLocationY();

	bool creepAtEndTile = false;

	// if the direction the creep is going in has an end tile, set boolean to true
	if (direction == Direction::LEFT && map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END)
	{
		creepAtEndTile = true;
	}
	else if (direction == Direction::RIGHT && map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::END)
	{
		creepAtEndTile = true;

	}
	else if (direction == Direction::UP && map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::END)
	{
		creepAtEndTile = true;
	}
	else if (direction == Direction::DOWN && map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::END)
	{
		creepAtEndTile = true;

	}

	// if the creep is at an end tile 
	if (creepAtEndTile) {
		// remove coins from player according to value of creep's strength
		player->setCoins(player->getCoins() - creep->getStrength());

		// set tile creep was on back to path
		//map->setTile(locationX, locationY, MapTile::PATH);
	}

	// return if a creep has landed on the end tile
	return creepAtEndTile;
}

CreepSquad::~CreepSquad()
{

}
