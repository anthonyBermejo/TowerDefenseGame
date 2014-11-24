#pragma once
#include "Tower.h"

using namespace std;

class DrawableTower : public Tower{

public:
	DrawableTower(TOWER_TYPE type, int level, sf::Vector2i mapPos, CreepSquad* squad, Player* p, TextureManager* tm, int mapCols, int mapRows);
	~DrawableTower();

	void Draw(sf::RenderWindow* w, bool isSelected);
	sf::Sprite getSprite() const;

private:

	sf::Sprite sprite;
	TextureManager* tm;
	sf::RectangleShape rangeRect;


};