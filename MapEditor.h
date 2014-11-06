#pragma once
#include "rapidxml.hpp"
#include "Map.h"
#include "TextMessage.h"
#include <string>

using namespace std;
using namespace rapidxml;

class MapEditor
{
public:
	MapEditor();
	MapEditor(std::string path, TextureManager* tm);
	MapEditor(int rows, int cols);
	MapEditor(Map* map);
	MapEditor(TextureManager* tm,sf::RenderWindow* win);

	~MapEditor();

	void createCustomMap();
	void setPath(int x, int y);
	void setStartAndEnd(int x, int y);
	void saveMap(std::string saveDir);
	void validityTest();
	void setTile(int row, int col, int val);
	Map* getMap();
private:
	Map map;
	xml_document<> doc;
	sf::RenderWindow* win;
	TextureManager* tm;

	TextMessage* saveMapMsg;
	TextMessage* backMsg;
	TextMessage* loadMsg;
	TextMessage* createNewMsg;

	bool startSet;
	bool endSet;
	bool isConnected(int x, int y) const;
	bool validateMap() const;
	void createNewMap(int rows, int cols);
	void loadMapFile(std::string mapDir);
	void importMap() const;
	void printMap() const;
};