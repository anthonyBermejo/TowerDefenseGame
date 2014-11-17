#pragma once

#include <vector>
#include <iostream>
#include "Creep.h"
#include "Map.h"
#include <queue>
#include "CreepFactory.h"
#include "DrawableCreep.h"

using namespace std;

class CreepSquad : public Observer
{
public:
	CreepSquad(Map* map, TextureManager* texManager);
	void move(Player *player, sf::Time elapsedTime, sf::RenderWindow* w);
	void resetCreepSquad(int level, sf::RenderWindow* w);
	virtual ~CreepSquad();

	vector<DrawableCreep*> getCreeps() const;
	vector<DrawableCreep*> getStartingCreepList() const;

	void update();
	void Update(Player* player, sf::RenderWindow* w, sf::Time elapsedTime);
	void Draw(sf::RenderWindow* w);

private:
	vector<DrawableCreep*> creepSquad;
	Map* map;
	TextureManager* texManager;
	vector<DrawableCreep*> startingCreepList;
	sf::Time timeElapsed;
	sf::Time spawnElapsedTime;

	int startLocationX;
	int startLocationY;

	void checkMove(DrawableCreep* creep);
	bool checkEndTile(DrawableCreep* creep, Player* player);
	void removeDeadCreeps();
	void displayHealthBar(DrawableCreep* creep);
	int creepSpeed;
	int creepTotalHP;

	CreepFactory* creepFactory;
};

