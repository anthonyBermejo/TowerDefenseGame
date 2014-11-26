#include "CreepSquad.h"

// _________________________________________
//
// Class representing a collection of Creeps
//
//__________________________________________

const int MAX_NUMBER_OF_CREEPS = 10;

// constructor
CreepSquad::CreepSquad(Map* map, TextureManager* texManager) : Observer()
{
	this->creepSquad = vector<DrawableCreep*>(MAX_NUMBER_OF_CREEPS);
	this->map = map;
	this->texManager = texManager;
	timeElapsed = sf::Time::Zero;
	creepSpeed = 1;
	creepFactory = new CreepFactory(texManager, map);
}

// accessors
vector<DrawableCreep*> CreepSquad::getCreeps() const { return creepSquad; }
vector<DrawableCreep*> CreepSquad::getStartingCreepList() const { return startingCreepList; }
int CreepSquad::getCreepTotalHP() const { return creepTotalHP; }

// Moves a creep along a path in a specific direction
void CreepSquad::move(Player* player, sf::Time elapsedTime)
{
	for (int i = 0; i < (int)creepSquad.size(); ++i) {
		
		// check if creep can move, change it's direction
		checkMove(creepSquad[i]);

		creepSquad[i]->setMovementTime(creepSquad[i]->getMovementTime() + elapsedTime);
		animationTime += elapsedTime;

		if (creepSquad[i]->getMovementTime() >= sf::milliseconds(1000 / creepSquad[i]->getSpeed())) {

			if (!checkEndTile(creepSquad[i], player)) {
				// move creep along the internal amp
				creepSquad[i]->move(map);
			}
			else {
				// delete creep object and remove from vector of creeps
				delete creepSquad[i];
				creepSquad[i] = NULL;
				creepSquad.erase(creepSquad.begin() + i);
				i--;
				continue;
			}

			creepSquad[i]->setMovementTime(sf::Time::Zero);
		}
		//else  {
		//	Direction direction = creepSquad[i]->getDirection();
		//	sf::Sprite* creepSprite = creepSquad[i]->getSprite();

		//	if (direction == Direction::LEFT)
		//	{
		//		creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f - 1, creepSquad[i]->getLocationX() * 24.0f);
		//	}
		//	else if (direction == Direction::RIGHT)
		//	{
		//		creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f + 1, creepSquad[i]->getLocationX() * 24.0f);
		//	}
		//	else if (direction == Direction::UP)
		//	{
		//		creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f, creepSquad[i]->getLocationX() * 24.0f - 1);
		//	}
		//	else
		//	{
		//		creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f, creepSquad[i]->getLocationX() * 24.0f + 1);
		//	}

		//	animationTime = sf::Time::Zero;
		//}
	}
}

// Reset the creep squad according to a specified level,
// populating the vector with new creeps
void CreepSquad::resetCreepSquad(int level)
{
	creepSquad.clear();
	int numCreeps = 0;

	// spawn creeps according to the level
	switch (level)
	{
	case 1:
		numCreeps = 7;
		break;
	case 2:
		numCreeps = 10;
		break;
	case 3:
		numCreeps = 4;
		break;
	case 4:
		numCreeps = 5;
		break;
	case 5:
		numCreeps = 9;
		break;
	case 6:
		numCreeps = 6;
		break;
	case 7:
		numCreeps = 1;
		break;
	default:
		numCreeps = level - 6;
		break;
	}

	for (int i = 0; i < numCreeps; ++i) {
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
	}

	creepSpeed = startingCreepList.front()->getSpeed();
	creepTotalHP = startingCreepList.front()->getHitPoints();

	for (int i = 0; i < startingCreepList.size(); ++i) {
		startingCreepList[i]->addObserver(this);
	}
}

// Check if a creep is able to move in a specific direction
void CreepSquad::checkMove(DrawableCreep* creep)
{
	Direction creepDirection = creep->getDirection();
	int locationX = creep->getLocationX();
	int locationY = creep->getLocationY();

	// if a creep's project direction is an ENVIRONMENT tile,
	// check the other directions if it is able to move (there is a path there) and set the direction to that creep
	// else, move along the current direction
	if (creepDirection == Direction::LEFT)
	{
		if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::ENV || locationY == 0) {
			if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::DOWN);
			}

			if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::UP);
			}
		}
	}
	else if (creepDirection == Direction::RIGHT)
	{
		if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::ENV || locationY == map->getCols() - 1)
		{

			if (map->getTile(locationX+1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX+1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::DOWN);
			}

			if (map->getTile(locationX-1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX-1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::UP);
			}
		}
	}
	else if (creepDirection == Direction::UP)
	{
		if (map->getTile(locationX-1, locationY) == Map::TILE_TYPE::ENV || locationX == 0)
		{
			if (map->getTile(locationX, locationY-1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY-1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::LEFT);
			}

			if (map->getTile(locationX, locationY+1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY+1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::RIGHT);
			}
		}
	}
	else if (creepDirection == Direction::DOWN)
	{
		if (map->getTile(locationX+1, locationY) == Map::TILE_TYPE::ENV || locationX == map->getRows()-1)
		{
			if (map->getTile(locationX, locationY-1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY-1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::LEFT);
			}

			if (map->getTile(locationX, locationY+1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY+1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::RIGHT);
			}
		}
	}
}

// Checks if a creep has entered an end tile
bool CreepSquad::checkEndTile(DrawableCreep* creep, Player* player)
{
	Direction direction = creep->getDirection();
	int locationX = creep->getLocationX();
	int locationY = creep->getLocationY();

	bool creepAtEndTile = false;

	// if the direction the creep is going in has an end tile, set boolean to true
	if (direction == Direction::LEFT)
	{
		if (map->getTile(locationX, locationY-1) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}
	else if (direction == Direction::RIGHT)
	{
		if (map->getTile(locationX, locationY+1) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}
	else if (direction == Direction::UP)
	{
		if (map->getTile(locationX-1, locationY) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}
	else
	{
		if (map->getTile(locationX+1, locationY) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}

	// if the creep is at an end tile
	if (creepAtEndTile && creep->getHitPoints() > 0) {
		// remove coins from player according to value of creep's strength
		player->setHealth(player->getHealth() - 1);

		// set tile creep was on back to path
		map->setTile(locationX, locationY, Map::TILE_TYPE::PATH);
	}

	// return if a creep has landed on the end tile
	return creepAtEndTile;
}

// Removes any dead creeps from the vector of creeps
void CreepSquad::removeDeadCreeps()
{
	for (int i = 0; i < (int)creepSquad.size(); ++i) {
		if (creepSquad[i]->getHitPoints() <= 0) {

			// delete creep object and remove from vector of creeps
			map->setTile(creepSquad[i]->getLocationX(), creepSquad[i]->getLocationY(), Map::PATH);

			delete creepSquad[i];
			creepSquad[i] = NULL;
			creepSquad.erase(creepSquad.begin() + i);
			i--;
		}
	}
}

// Update method that runs in every iteration of the game loop
void CreepSquad::Update(Player* player, sf::Time elapsedTime)
{
	spawnElapsedTime += elapsedTime;

	// set spawn timer for the creeps
	if (spawnElapsedTime >= sf::milliseconds(3000)) {

		// remove creeps one at a time from a container list to enter game
		if (!startingCreepList.empty()) {
			DrawableCreep* creep = startingCreepList.back();

			creepSquad.push_back(creep);
			startingCreepList.pop_back();

			spawnElapsedTime = sf::Time::Zero;
		}
	}

	// remove any dead creeps
	removeDeadCreeps();

	// move the creeps
	move(player, elapsedTime);
}

// Deconstructor
CreepSquad::~CreepSquad()
{
	for (int i = 0; i < (int)creepSquad.size(); ++i) {
		delete creepSquad[i];
		creepSquad[i] = NULL;
	}

	delete map;
	map = NULL;

	delete creepFactory;
	creepFactory = NULL;
}
