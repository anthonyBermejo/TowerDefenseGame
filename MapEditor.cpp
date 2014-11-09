#include "MapEditor.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <Windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MainClass.h"

using namespace std;
using namespace rapidxml;

MapEditor::MapEditor()
{
	createCustomMap();
}

/*
MapEditor::MapEditor(int rows, int cols){
createNewMap(rows, cols);
}
*/

MapEditor::MapEditor(std::string path, TextureManager* tm){
	this->tm = tm;
	loadMapFile(path);
	validateMap();
}

MapEditor::MapEditor(TextureManager* tm, sf::RenderWindow* win, MainClass* main){
	this->tm = tm;
	this->win = win;
	this->main = main;
}

MapEditor::MapEditor(Map* map){
	createNewMap(map->getRows(), map->getCols());
	for (int i = 0; i < map->getRows(); ++i)
		for (int j = 0; j < map->getCols(); ++j)
			this->map->setTile(i, j, map->getTile(i, j));
}

MapEditor::~MapEditor(){
	win = NULL;
	tm = NULL;

	delete saveMapMsg;
	delete backMsg;
	delete loadMsg;
	delete createNewMsg;

	saveMapMsg = NULL;
	backMsg = NULL;
	loadMsg = NULL;
	createNewMsg = NULL;
}

void MapEditor::setPath(int x, int y){
	if (map->getTile(x, y) == 0)
		map->setTile(x, y, 1);
	else if (map->getTile(x, y) == 1)
		map->setTile(x, y, 0);
}

void MapEditor::setStartAndEnd(int x, int y){
	if (!startSet && (x == 0 || y == 0 || x == map->getRows() - 1 || y == map->getCols() - 1) && map->getTile(x, y) != Map::END){
		map->setTile(x, y, Map::START);
		startSet = true;
	}
	else if (startSet && map->getTile(x, y) == Map::START){
		map->setTile(x, y, Map::ENV);
		startSet = false;
	}
	else if (!endSet && startSet && (x == 0 || y == 0 || x == map->getRows() - 1 || y == map->getCols() - 1) && map->getTile(x, y) != Map::START){
		map->setTile(x, y, Map::END);
		endSet = true;
	}
	else if (endSet && map->getTile(x, y) == Map::END){
		map->setTile(x, y, Map::ENV);
		endSet = false;
	}
}

void MapEditor::loadMapFile(std::string mapDir){
	int rows;
	int cols;

	//reading in xml map file into xml_document<> doc
	std::ifstream file(mapDir);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());

	//parsing xml data
	doc.parse<0>(&content[0]);

	//instantiating handle to the map root
	xml_node<> *mapHead = doc.first_node("map");

	//iterating through map attributes
	for (xml_attribute<> *attr = mapHead->first_attribute();
		attr; attr = attr->next_attribute())
	{
		std::string name(attr->name());
		if (name == "cols") {
			cols = atoi(attr->value());
			continue;
		}
		if (name == "rows") {
			rows = atoi(attr->value());
			continue;
		}
	}

	//creating map
	createNewMap(rows, cols);

	int x = 0;
	int y = 0;

	//populating map with map data from xml
	for (xml_node<> *row = mapHead->first_node("row"); row; row = row->next_sibling()){
		for (xml_node<> *tile = row->first_node("tile"); tile; tile = tile->next_sibling("tile")){
			map->setTile(x, y++, atoi(tile->first_attribute()->value()));
			if (y >= cols)
				y = 0;
		}
		++x;
		if (x >= rows)
			x = 0;
	}

	win->create(sf::VideoMode(cols * 24, (rows + 2) * 24), "TD");
	map->printMap();
}

void MapEditor::saveMap(std::string path){
		//used as temp holding to convert c_str() to xml string
		char* val;

		int rows = map->getRows();
		int cols = map->getCols();

		//creating and setting xml header tag
		xml_document<> output;
		xml_node<>* header = output.allocate_node(node_declaration);
		header->append_attribute(output.allocate_attribute("version", "1.0"));
		header->append_attribute(output.allocate_attribute("encoding", "UTF-8"));
		output.append_node(header);

		//creating and setting map root
		xml_node<>* root = output.allocate_node(node_element, "map");

		//creating and setting root rows attribute
		val = doc.allocate_string(std::to_string(rows).c_str());
		xml_attribute<> *heightAttr = output.allocate_attribute("rows", val);

		//creating and setting root cols attribute
		val = doc.allocate_string(std::to_string(cols).c_str());
		xml_attribute<> *widthAttr = output.allocate_attribute("cols", val);

		//adding rows and cols attributes to root
		root->append_attribute(heightAttr);
		root->append_attribute(widthAttr);

		//instantiating map components
		xml_node<> *tileNode;
		xml_attribute<> *tileValue;
		xml_node<> *row;
		output.append_node(root);

		//populating xml file with map data
		for (int i = 0; i < rows; i++) {
			row = output.allocate_node(node_element, "row");
			root->append_node(row);
			for (int j = 0; j < cols; j++) {
				tileNode = output.allocate_node(node_element, "tile");
				val = doc.allocate_string(std::to_string(map->getTile(i, j)).c_str());
				tileValue = output.allocate_attribute("access", val);
				tileNode->append_attribute(tileValue);
				row->append_node(tileNode);
			}
		}

		//outputting xml data to file
		std::ofstream outputFile;
		outputFile.open(path + ".tdm");
		outputFile << output;
		outputFile.close();
		cout << "Map successfully saved!\n";
}

void MapEditor::createNewMap(int rows, int cols){
	this->map = new Map(rows, cols, tm);
}

void MapEditor::createCustomMap(){
	int cols;
	int rows;

	//gets the number of rows and columns to generate from user
	cout << "Enter number of rows: ";
	cin >> rows;
	cout << "\nEnter number of columns: ";
	cin >> cols;

	//checks that entered values are within the acceptable range of sizes of 8 and 64, inclusively
	if (rows <= Map::MAX_MAP_HEIGHT && rows >= Map::MIN_MAP_HEIGHT &&
		cols <= Map::MAX_MAP_WIDTH && cols >= Map::MIN_MAP_WIDTH)
		createNewMap(rows, cols);

	win->create(sf::VideoMode(cols * 24, (rows + 2) * 24), "TD");
}

void MapEditor::printMap() const{
	map->printMap();
}

Map* MapEditor::getMap(){
	return map;
}

void MapEditor::setTile(int row, int col, int val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = tower
	*  3 = start
	*  4 = end
	*/
	map->setTile(row, col, val);
}

bool MapEditor::validateMap() const{
	bool start = false;	//3
	bool end = false;	//4
	bool connected = false;
	int startX = 0;
	int startY = 0;

	//find start and end and setting x and y of start
	// checking top and bottom rows
	for (int col = 1; col < map->getCols() - 1; col++){
		if (map->getTile(0, col) == Map::START)
			if (!start){
			start = true;
			startX = 0;
			startY = col;
			}
			else
				//if multiple starts are found
				return false;
		else if (map->getTile(map->getRows() - 1, col) == Map::START)
			if (!start){
			start = true;
			startX = map->getRows() - 1;
			startY = col;
			}
			else
				//if multiple starts are found
				return false;
		if (map->getTile(0, col) == Map::END || map->getTile(map->getRows() - 1, col) == Map::END)
			if (!end) {
			end = true;
			}
			else { //if multiple ends are found
				return false;
			}
	}
	// checking first and last columns
	for (int row = 1; row < map->getRows() - 1; row++){
		if (map->getTile(row, 0) == Map::START){
			if (!start){
				start = true;
				startX = row;
				startY = 0;
			}
			else {
				//if multiple starts are found
				return false;
			}
		}
		else if (map->getTile(row, map->getCols() - 1) == Map::START){
			if (!start){
				start = true;
				startX = row;
				startY = map->getCols() - 1;
			}
			else {
				//if multiple starts are found
				return false;
			}
		}
		if (map->getTile(row, 0) == Map::END || map->getTile(row, map->getCols() - 1) == Map::END)
			if (!end) {
			end = true;
			}
			else {
				//if multiple ends are found
				return false;
			}
	}

	if (startX != 0 || startY != 0)
		connected = isConnected(startX, startY);

	return (start && end && connected);
}

bool MapEditor::isConnected(int x, int y) const{
	char dir;
	bool connected = true;

	//identifying and setting direction to check
	if (y == 0)
		dir = 'e';
	else if (y == map->getCols() - 1)
		dir = 'w';
	else if (x == 0)
		dir = 's';
	else if (x == map->getRows() - 1)
		dir = 'n';

	//moves along the path, identifying path tiles to the north, east, south, and west, depending on the current (x, y) position.
	do {
		//checking is path ending is next
		if (map->getTile(x + 1, y) == Map::END || map->getTile(x - 1, y) == Map::END || map->getTile(x, y + 1) == Map::END || map->getTile(x, y - 1) == Map::END){
			break;
		}
		else if (dir == 'n'){		//if heading north, check other directions
			//path goes east
			if (map->getTile(x, y + 1) == Map::PATH){
				dir = 'e';
				++y;
			}
			//path goes north
			else if (map->getTile(x - 1, y) == Map::PATH) {
				--x;
			}
			//path goes west
			else if (map->getTile(x, y - 1) == Map::PATH){
				dir = 'w';
				--y;
			}
			else
				//no further path tiles found
				connected = false;
		}
		else if (dir == 'e'){		//if heading east, check other directions
			//path goes south
			if (map->getTile(x + 1, y) == Map::PATH) {
				dir = 's';
				++x;
			}
			//path goes east
			else if (map->getTile(x, y + 1) == Map::PATH) {
				++y;
			}
			//path goes north
			else if (map->getTile(x - 1, y) == Map::PATH) {
				dir = 'n';
				--x;
			}
			else
				//not further path tiles found
				connected = false;
		}
		else if (dir == 's'){	//if heading south, check other directions
			//path goes west
			if (map->getTile(x, y - 1) == Map::PATH) {
				dir = 'w';
				--y;
			}
			//path goes south
			else if (map->getTile(x + 1, y) == Map::PATH){
				++x;
			}
			//path goes east
			else if (map->getTile(x, y + 1) == Map::PATH) {
				dir = 'e';
				++y;
			}
			else
				//no further path tiles found
				connected = false;
		}
		else if (dir == 'w'){	//if heading west, check other directions
			//path goes north
			if (map->getTile(x - 1, y) == Map::PATH){
				dir = 'n';
				--x;
			}
			//path goes west
			else if (map->getTile(x, y - 1) == Map::PATH) {
				++y;
			}
			//path goes south
			else if (map->getTile(x + 1, y) == Map::PATH) {
				dir = 's';
				++x;
			}
			else
				//no further path tiles found
				connected = false;
		}
	} while (connected);	//checks if there are still path tiles

	return connected;
}

//For testing only
void MapEditor::validityTest(){
	//setting start and end
	map->setTile(1, 0, Map::START);
	map->setTile(4, 7, Map::END);

	//creating path
	map->setTile(1, 1, Map::PATH);
	map->setTile(1, 2, Map::PATH);
	map->setTile(2, 2, Map::PATH);
	map->setTile(3, 2, Map::PATH);
	map->setTile(3, 1, Map::PATH);
	map->setTile(4, 1, Map::PATH);
	map->setTile(5, 1, Map::PATH);
	map->setTile(5, 2, Map::PATH);
	map->setTile(5, 3, Map::PATH);
	map->setTile(4, 3, Map::PATH);
	map->setTile(4, 4, Map::PATH);
	map->setTile(3, 4, Map::PATH);
	map->setTile(2, 4, Map::PATH);
	map->setTile(2, 5, Map::PATH);
	map->setTile(2, 6, Map::PATH);
	map->setTile(3, 6, Map::PATH);
	map->setTile(4, 6, Map::PATH);

	validateMap();

	//removing path tile to show detection of broken path
	map->setTile(5, 2, Map::END);

	validateMap();
}
void MapEditor::update(){
	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;
		if (x >= 0 && y >= 0){
			if (x < map->getRows()){
				setPath(x, y);
			}
			else {
				//clicking on map editor buttons.
				int margin = map->getCols() / 4;
				if (y < margin){
					//clicking on Load
					std::string path;
					path = getFilePath();
					if (path.length() != 0) {
						loadMapFile(path);
					}
				} else if (y >= margin && y < margin * 2){
					if (validateMap()){
						//clicking on Save
						std::string path;
						cout << "Enter path to save to: ";
						cin >> path;
						saveMap(path);
					}
					else
						cout << "Failed to save map: Map is not valid.\n";
				}
				else if (y >= margin * 2 && y < margin * 3){
					//return to menu via Alex's MainClass
					main->switchToContext(MainClass::CONTEXT::MENU);
				}
				else{
					createCustomMap();
				}
			}
		}
		prevClick = true;
	}

	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;

		if (x >= 0 && y >= 0){
			setStartAndEnd(x, y);
		}
		prevClick = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
		if (!prevClick)
			prevClick = true;
	}
	else
		prevClick = false;

	map->drawMap(win);

	int margin = map->getCols()/4;

	loadMsg = new TextMessage(tm, "Load", sf::Vector2f(0, win->getSize().y - 30));
	saveMapMsg = new TextMessage(tm, "Save", sf::Vector2f(margin * 24, win->getSize().y - 30));
	backMsg = new TextMessage(tm, "Back", sf::Vector2f(margin * 2 * 24, win->getSize().y - 30));
	createNewMsg = new TextMessage(tm, "New", sf::Vector2f((margin * 3) * 24, win->getSize().y - 30));

	float scale = map->getCols() < 17 ? 1.0 : 2.0;

	loadMsg->setScale(sf::Vector2f(scale, scale));
	saveMapMsg->setScale(sf::Vector2f(scale, scale));
	backMsg->setScale(sf::Vector2f(scale, scale));
	createNewMsg->setScale(sf::Vector2f(scale, scale));

	loadMsg->drawMessage(win);
	saveMapMsg->drawMessage(win);
	backMsg->drawMessage(win);
	createNewMsg->drawMessage(win);
}

std::string MapEditor::getFilePath(){
	OPENFILENAME ofn;
	char szFile[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	//project->properties->config properties->general->character set->Default is UNICODE, changed to "Not Set"
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	//project->properties->config properties->general->character set->Default is UNICODE, changed to "Not Set"
	ofn.lpstrFilter = "Tower Defence Map File\0*.tdm\00";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	return ofn.lpstrFile;
}
