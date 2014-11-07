#include "CreepSquad.h"

const int MAX_NUMBER_OF_CREEPS = 10;

CreepSquad::CreepSquad(Map* map, TextureManager* texManager)
{
	this->creepSquad = vector<Creep*>(MAX_NUMBER_OF_CREEPS);
	this->map = map;
	this->texManager = texManager;
	timeElapsed = sf::Time::Zero;
}

vector<Creep*> CreepSquad::getCreeps(){ return creepSquad; }

void CreepSquad::move(Player* player, sf::RenderWindow* w)
{
	cout << "in move" << endl;
	cout << "creep #: " << creepSquad.size() << endl;
	// remove creeps one at a time from a container list to enter game
	if (!startingCreepList.empty()) {
		Creep* creep = startingCreepList.back();
		creepSquad.push_back(creep);
		startingCreepList.pop_back();
	}

	for (int i = 0; i < (int)creepSquad.size(); ++i) {

		// check if creep can move, change it's direction
		checkMove(creepSquad[i]);

		if (!checkEndTile(creepSquad[i], player)) {
			// move creep along the internal amp
			creepSquad[i]->move(map);

			// set position of the sprite and draw it
			sf::Sprite* creepSprite = creepSquad[i]->getSprite();
			creepSprite->setPosition(creepSquad[i]->getLocationY() * 24.0f, creepSquad[i]->getLocationX() * 24.0f);

			// draw health bar of creep
			sf::RectangleShape healthBar;
			healthBar.setSize(sf::Vector2f(creepSquad[i]->getHitPoints() / 3, 5));
			healthBar.setFillColor(sf::Color::Red);
			healthBar.setOutlineColor(sf::Color::Black);
			healthBar.setPosition(creepSprite->getPosition().x, creepSprite->getPosition().y - 5);

			w->draw(healthBar);
			w->draw(*creepSprite);

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

	// get x,y position of start tile of the map
	startLocationX = map->getStart()[0];
	startLocationY = map->getStart()[1];

	// spawn creeps according to the level
	switch (level)
	{
	case 1:
		startingCreepList.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		startingCreepList.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		startingCreepList.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		startingCreepList.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		startingCreepList.push_back(new Creep(20, 1, 10, 50, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::BLOB));
		break;
	case 2:
		startingCreepList.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		startingCreepList.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		startingCreepList.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		startingCreepList.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		startingCreepList.push_back(new Creep(30, 1, 15, 60, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::SKELETON));
		break;
	case 3:
		startingCreepList.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		startingCreepList.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		startingCreepList.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		startingCreepList.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		startingCreepList.push_back(new Creep(50, 1, 20, 80, 50, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::ELF));
		break;
	case 4:
		startingCreepList.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		startingCreepList.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		startingCreepList.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		startingCreepList.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		startingCreepList.push_back(new Creep(40, 2, 25, 80, 60, startLocationX, startLocationY, Direction::RIGHT, texManager, SPRITE_TYPE::MAGE));
		break;
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
			if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::DOWN);
			}

			if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::UP);
			}
		}
	}
	else if (creepDirection == Direction::RIGHT)
	{
		if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::ENV)
		{

			if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::DOWN);
			}

			if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::PATH || map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::UP);
			}
		}
	}
	else if (creepDirection == Direction::UP)
	{
		if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::ENV)
		{
			if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::LEFT);
			}

			if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::RIGHT);
			}
		}
	}
	else
	{
		if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::ENV)
		{
			if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::LEFT);
			}

			if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::PATH || map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END) {
				creep->setDirection(Direction::RIGHT);
			}
		}
	}
}

// Checks if a creep has entered an end tile
bool CreepSquad::checkEndTile(Creep* creep, Player* player)
{
	Direction direction = creep->getDirection();
	int locationX = creep->getLocationX();
	int locationY = creep->getLocationY();

	bool creepAtEndTile = false;

	// if the direction the creep is going in has an end tile, set boolean to true
	if (direction == Direction::LEFT)
	{
		if (map->getTile(locationX - 1, locationY) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}
	else if (direction == Direction::RIGHT)
	{
		if (map->getTile(locationX + 1, locationY) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}
	else if (direction == Direction::UP)
	{
		if (map->getTile(locationX, locationY + 1) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}
	else
	{
		if (map->getTile(locationX, locationY - 1) == Map::TILE_TYPE::END) {
			creepAtEndTile = true;
		}
	}

	// if the creep is at an end tile
	if (creepAtEndTile) {
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

	if (timeElapsed >= sf::milliseconds(2500)) {

		removeDeadCreeps();

		move(player, w);

		timeElapsed = sf::Time::Zero;
	}
}

void CreepSquad::Draw(sf::RenderWindow* w)
{
	for (int i = 0; i < (int)creepSquad.size(); ++i)
		w->draw(*(creepSquad[i]->getSprite()));
}

CreepSquad::~CreepSquad()
{
	for (int i = 0; i < (int)creepSquad.size(); ++i)
		delete creepSquad[i];
}
