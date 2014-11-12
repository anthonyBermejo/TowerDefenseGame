#include "CreepSquad.h"

const int MAX_NUMBER_OF_CREEPS = 10;

CreepSquad::CreepSquad(Map* map, TextureManager* texManager)
{
	this->creepSquad = vector<DrawableCreep*>(MAX_NUMBER_OF_CREEPS);
	this->map = map;
	this->texManager = texManager;
	timeElapsed = sf::Time::Zero;
	creepSpeed = 1;
	creepFactory = new CreepFactory(texManager);
}

vector<DrawableCreep*> CreepSquad::getCreeps() const { return creepSquad; }
vector<DrawableCreep*> CreepSquad::getStartingCreepList() const { return startingCreepList; }

void CreepSquad::move(Player* player, sf::RenderWindow* w)
{
	// remove creeps one at a time from a container list to enter game
	if (!startingCreepList.empty()) {
		DrawableCreep* creep = startingCreepList.back();

		// get x,y position of start tile of the map
		creep->setLocationX(map->getStart()[0]);
		creep->setLocationY(map->getStart()[1]);

		creepSquad.push_back(creep);
		startingCreepList.pop_back();
	}

	for (int i = 0; i < (int)creepSquad.size(); ++i) {

		// check if creep can move, change it's direction
		checkMove(creepSquad[i]);

		if (!checkEndTile(creepSquad[i], player)) {
			// move creep along the internal amp
			creepSquad[i]->move(map);

			// set position of the sprite
			if (creepSquad[i]->getHitPoints() > 0) {
				sf::Sprite* creepSprite = creepSquad[i]->getSprite();
				creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f, creepSquad[i]->getLocationX() * 24.0f);
			}

			// draw health bar of creep
			//sf::RectangleShape healthBar;
			//healthBar.setSize(sf::Vector2f(creepSquad[i]->getHitPoints() / 3, 5));
			//healthBar.setFillColor(sf::Color::Red);
			//healthBar.setPosition(creepSprite->getPosition().x, creepSprite->getPosition().y - 5);
			//w->draw(healthBar);
		}
		else {
			// delete creep object and remove from vector of creeps
			delete creepSquad[i];
			creepSquad[i] = NULL;
			creepSquad.erase(creepSquad.begin() + i);
			i--;
		}
	}
}

void CreepSquad::resetCreepSquad(int level, sf::RenderWindow* w)
{
	creepSquad.clear();

	// spawn creeps according to the level
	switch (level)
	{
	case 1:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	case 2:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	case 3:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	case 4:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	case 5:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	case 6:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	case 7:
		startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		break;
	default:
		//TEMPORARY FIX SO THAT THE GAME DOESNT CRASH AFTER LEVEL 7
		for (int i = 0; i < level - 6; ++i){
			startingCreepList.push_back(creepFactory->getCreepAtLevel(level));
		}
		break;
	}

	creepSpeed = startingCreepList.front()->getSpeed();
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


void CreepSquad::Update(Player* player, sf::RenderWindow* w, sf::Time elapsedTime)
{
	timeElapsed += elapsedTime;

	if (timeElapsed >= sf::milliseconds(1000 / creepSpeed)) {

		removeDeadCreeps();

		move(player, w);

		timeElapsed = sf::Time::Zero;
	}
}

void CreepSquad::Draw(sf::RenderWindow* w)
{
	for (int i = 0; i < (int)creepSquad.size(); ++i)
	{
		if (creepSquad[i]->getHitPoints() > 0)
			w->draw(*(creepSquad[i]->getSprite()));
	}
}

CreepSquad::~CreepSquad()
{
	for (int i = 0; i < (int)creepSquad.size(); ++i)
		delete creepSquad[i];
}
