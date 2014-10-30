#include "Tile.h"

using namespace std;

Tile::Tile(Map::TILE_TYPE type, sf::Sprite* sprite) :type(type), sprite(sprite){}

Tile::~Tile(){
	sprite = NULL;
}

//wee