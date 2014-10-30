#pragma once
#include "rapidxml.hpp"
#include "Map.h"
#include <string>

using namespace std;
using namespace rapidxml;

class MapEditor
{
public:
	MapEditor();
	MapEditor(std::string mapDir);
	MapEditor(int rows, int cols);

	~MapEditor();

	void saveMap(std::string saveDir);
	void validityTest();
	void setTile(int row, int col, int val);
private:
	Map map;
	xml_document<> doc;

	bool isConnected(int x, int y) const;
	bool validateMap() const;
	void createCustomMap();
	void createNewMap(int rows, int cols);
	void loadMapFile(std::string mapDir);
	void importMap() const;
	void printMap() const;
};