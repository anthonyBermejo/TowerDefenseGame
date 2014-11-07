#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include "TextureManager.h"

using namespace std;
using namespace rapidxml;

class Map
{
public:
	
	enum TILE_TYPE{ENV,PATH,START,END,CREEP};
	
	Map();
	Map(int rows, int cols, TextureManager* texManager);
	Map(int rows, int cols);
	~Map();

	const static int MAX_MAP_WIDTH = 64;
	const static int MAX_MAP_HEIGHT = 64;
	const static int MIN_MAP_WIDTH = 8;
	const static int MIN_MAP_HEIGHT = 8;

	//	const std::vector<std::vector<int>> getMap();

	void setTile(int x, int y, TILE_TYPE t);
	void setTile(int x, int y, int val);
	int* getStart();
	int* getEnd();
	int getCols() const;
	int getRows() const;
	int getTile(int x, int y) const;
	void printMap() const;
	void drawPath(sf::RenderWindow* w);

	void drawMap(sf::RenderWindow* w);
	void setTextureManager(TextureManager* tm);
	
	
private:
	int start[2];
	int end[2];
	int cols;
	int rows;
	std::vector<std::vector<int> > map;

	TextureManager* texManager;

	sf::Sprite envSprite1; // solid green
	sf::Sprite envSprite2; // green with "grass"
	sf::Sprite pathSprite1;// verticle solid
	sf::Sprite pathSprite2;// vertical with variety
	sf::Sprite pathSprite3;// horizontal solid
	sf::Sprite pathSprite4;// horizontal with variety
	sf::Sprite pathSprite5;// top right
	sf::Sprite pathSprite6;// top left
	sf::Sprite pathSprite7;// bottom right
	sf::Sprite pathSprite8;// bottom left
	sf::Sprite startSprite;// start
	sf::Sprite endSprite;  // end
	sf::Sprite blockSprite;// block path

	void startTest();
	void endTest();
	void brokenTest();
	void pathTest();
};

