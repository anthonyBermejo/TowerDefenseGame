#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include "TextureManager.h"
#include "Observable.h"

using namespace std;
using namespace rapidxml;

class Map : public Observable {
public:
	enum TILE_TYPE{ENV,PATH,START,END,CREEP};
	
	Map();
	Map(int rows, int cols);
	~Map();

	const static int MAX_MAP_WIDTH = 64;
	const static int MAX_MAP_HEIGHT = 64;
	const static int MIN_MAP_WIDTH = 8;
	const static int MIN_MAP_HEIGHT = 8;

	void setTile(int x, int y, TILE_TYPE t);
	void setTile(int x, int y, int val);
	int* getStart();
	int* getEnd();
	int getCols() const;
	int getRows() const;
	int getTile(int x, int y) const;
	void printMap() const;	
private:
	int start[2];
	int end[2];
	int cols;
	int rows;
	std::vector<std::vector<int> > map;
};

