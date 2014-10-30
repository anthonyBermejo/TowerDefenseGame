#pragma once

#include "Map.h"
#include "SFML/Graphics.hpp"

using namespace std;

class Tile{
public:
	Tile(Map::TILE_TYPE type, sf::Sprite* sprite);
	~Tile();

	Map::TILE_TYPE type;
	sf::Sprite* sprite;
private:
};

