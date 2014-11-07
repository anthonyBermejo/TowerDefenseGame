#pragma once

#include <vector>
#include <iostream>
#include "Creep.h"
#include "Map.h"
#include <queue>

using namespace std;

class CreepSquad
{
public:
	CreepSquad(Map* map, TextureManager* texManager);
	void move(Player *player, sf::RenderWindow* w);
	void resetCreepSquad(int level, sf::RenderWindow* w);
	virtual ~CreepSquad();

	vector<Creep*> getCreeps() const;
	vector<Creep*> getStartingCreepList() const;

	void Update(Player* player, sf::RenderWindow* w, sf::Time elapsedTime);
	void Draw(sf::RenderWindow* w);

private:
	vector<Creep*> creepSquad;
	Map* map;
	TextureManager* texManager;
	vector<Creep*> startingCreepList;
	sf::Time timeElapsed;

	int startLocationX;
	int startLocationY;

	void checkMove(Creep* creep);
	bool checkEndTile(Creep* creep, Player* player);
	void damageCreep(Player *player, int damage);
	void removeDeadCreeps();
	int creepSpeed;
};

