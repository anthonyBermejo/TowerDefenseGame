#pragma once

#include <vector>
#include <iostream>
#include "Creep.h"
#include "Map.h"
#include <queue>
#include "CreepFactory.h"
#include "DrawableCreep.h"

using namespace std;

class CreepSquad
{
public:
	CreepSquad(Map* map, TextureManager* texManager);
	void move(Player *player, sf::RenderWindow* w);
	void resetCreepSquad(int level, sf::RenderWindow* w);
	virtual ~CreepSquad();

	vector<DrawableCreep*> getCreeps() const;
	vector<DrawableCreep*> getStartingCreepList() const;

	void Update(Player* player, sf::RenderWindow* w, sf::Time elapsedTime);
	void Draw(sf::RenderWindow* w);

private:
	vector<DrawableCreep*> creepSquad;
	Map* map;
	TextureManager* texManager;
	vector<DrawableCreep*> startingCreepList;
	sf::Time timeElapsed;

	int startLocationX;
	int startLocationY;

	void checkMove(DrawableCreep* creep);
	bool checkEndTile(DrawableCreep* creep, Player* player);
	void damageCreep(Player *player, int damage);
	void removeDeadCreeps();
	int creepSpeed;

	CreepFactory* creepFactory;
};

