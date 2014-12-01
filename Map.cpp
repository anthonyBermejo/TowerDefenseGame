#include "Map.h"
#include <iostream>
#include <vector>
#include <stdlib.h> 


using namespace std;

//Creates an empty map
Map::Map() : Observable()
{
	this->map = std::vector<std::vector<TILE_TYPE> >(0, std::vector<TILE_TYPE>(0));
}

//Creates a map using the dimensions provided
Map::Map(int rows, int cols) : Observable()
{
	this->map = std::vector<std::vector<TILE_TYPE> >(rows, std::vector<TILE_TYPE>(cols, ENV));
}

Map::~Map()
{
}

//Wrapper used when loading XML map into vector to set proper tiles
void Map::setTile(int x, int y, int val){
	switch (val){
	case 0:
		setTile(x, y, ENV);
		break;
	case 1:
		setTile(x, y, PATH);
		break;
	case 2:
		setTile(x, y, START);
		break;
	case 3:
		setTile(x, y, END);
		break;
	case 4:
		setTile(x, y, CREEP);
		break;
	default:
		setTile(x, y, PATH);
	}
}

//Sets the map tiles
void Map::setTile(int x, int y, TILE_TYPE val){
	//checking that x and y are within map range and that value is valid
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1) &&
		(val >= Map::TILE_TYPE::ENV && val <= Map::TILE_TYPE::CREEP)){
		if (val == Map::START){
			start[0] = x;
			start[1] = y;
		}
		else if (val == Map::END) {
			end[0] = x;
			end[1] = y;
		}
		map[x][y] = val;
		notify();
	}
}

//Returns a pointer to the start tile coordinates
int* Map::getStart(){
	return start;
}

//Returns a pointer to the end tile coordinates
int* Map::getEnd(){
	return end;
}

//Prints map for testing
void Map::printMap() const {
	for (int i = 0; i < getRows(); i++){
		for (int j = 0; j < getCols(); j++)
			cout << "|" << map[i][j] << "|";
		cout << "\n";
	}
}

//Provides the number of rows in the map
int Map::getRows() const{
	return map.size();
}

//Provides the number of columns in the map
int Map::getCols() const{
	return map[0].size();
}

//Provides that value at a specified x, y index
int Map::getTile(int x, int y) const {
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1))
		return map[x][y];
}
