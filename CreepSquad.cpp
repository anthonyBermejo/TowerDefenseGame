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
		if (creepSquad[i]->checkEndTile(map, player)) {

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
			creepSquad[i]->checkMove(map);

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
CreepSquad::~CreepSquad()
{

}
