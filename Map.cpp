#include "Map.h"
#include <iostream>
#include <vector>
#include <stdlib.h> 


using namespace std;

Map::Map() : Observable()
{
	this->map = std::vector<std::vector<int> >(0, std::vector<int>(0));
}

Map::Map(int rows, int cols) : Observable()
{
	this->map = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 0));
}

Map::~Map()
{
}

void Map::setTile(int x, int y, int val){
	//checking that x and y are within map range and that value is valid
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1) &&
		(val >= 0 && val <= 3)){
			if (val >= 0 && val <= 4){
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
}


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

int* Map::getStart(){
	return start;
}

int* Map::getEnd(){
	return end;
}

//printing map for testing
void Map::printMap() const {
	for (int i = 0; i < getRows(); i++){
		for (int j = 0; j < getCols(); j++)
			cout << "|" << map[i][j] << "|";
		cout << "\n";
	}
}

//return the number of rows in the map
int Map::getRows() const{
	return map.size();
}

//returns the number of columns in the map
int Map::getCols() const{
	return map[0].size();
}

//retrieves that value at a specified x, y index
int Map::getTile(int x, int y) const {
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1))
		return map[x][y];
}
