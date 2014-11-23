#pragma once
#include "CreepSquad.h"

class DrawableCreepSquad :
	public CreepSquad
{
public:
	DrawableCreepSquad(Map* map, TextureManager* texManager);
	virtual ~DrawableCreepSquad();
	void Update(Player* player, sf::Time elapsedTime);
	void update();
	void displayHealthBar(DrawableCreep* creep);
	void Draw(sf::RenderWindow* w);

private:
	int creepTotalHP;
	vector<DrawableCreep*> creepSquad;
};

