#pragma once
#include "rapidxml.hpp"
#include "Map.h"
#include "TextMessage.h"
#include "DrawableMap.h"
#include <string>

using namespace std;
using namespace rapidxml;

class MainClass;

class MapEditor : public Observable
{
public:
	MapEditor();
	MapEditor(std::string path, TextureManager* tm);
	MapEditor(Map* map);
	MapEditor(TextureManager* tm, sf::RenderWindow* win, MainClass* main);

	~MapEditor();

	void createCustomMap();
	void setPath(int x, int y);
	void setStartAndEnd(int x, int y);
	void saveMap(std::string saveDir);
	void validityTest();
	void loadMapFile(std::string mapDir);
	void setTile(int row, int col, int val);
	std::string getFilePath();
	Map* getMap();
	void drawMap();
	bool validateMap() const;
private:
	Map* map;
	xml_document<> doc;
	sf::RenderWindow* win;
	TextureManager* tm;
	MainClass* main;
	DrawableMap* drawable;

	bool prevClick;
	bool startSet;
	bool endSet;
	bool isConnected(int x, int y) const;
	
	void createNewMap(int rows, int cols);
	void importMap() const;
	void printMap() const;
};