#include "MapEditor.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace rapidxml;

MapEditor::MapEditor()
{
	createCustomMap();
}

MapEditor::MapEditor(int rows, int cols){
	createNewMap(rows, cols);
}

MapEditor::MapEditor(std::string path){
	loadMapFile(path);
	validateMap();
}

MapEditor::~MapEditor()
{
}

void MapEditor::loadMapFile(std::string mapDir){
	int rows;
	int cols;

	//reading in xml map file into xml_document<> doc
	std::ifstream file("C:/XMLTestFile.xml");
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
			map.setTile(x, y++, atoi(tile->first_attribute()->value()));
		}
		++x;
		if (x >= cols)
			x = 0;
		if (y >= rows)
			y = 0;
	}

	cout << "Loaded map: " << endl;
	printMap();
	cout << endl;
}

void MapEditor::saveMap(std::string path){
	//used as temp holding to convert c_str() to xml string
	char* val;

	int rows = map.getRows();
	int cols = map.getCols();

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
			val = doc.allocate_string(std::to_string(map.getTile(i, j)).c_str());
			tileValue = output.allocate_attribute("access", val);
			tileNode->append_attribute(tileValue);
			row->append_node(tileNode);
		}
	}

	//outputting xml data to file
	std::ofstream outputFile;
	outputFile.open(path);
	outputFile << output;
	outputFile.close();
}

void MapEditor::createNewMap(int rows, int cols){
	this->map = Map(rows, cols);
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

	printMap();
}

void MapEditor::printMap() const{
	map.printMap();
}

void MapEditor::setTile(int row, int col, int val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = tower
	*  3 = start
	*  4 = end
	*/
	map.setTile(row, col, val);
}

bool MapEditor::validateMap() const{
	bool start = false;	//3
	bool end = false;	//4
	bool connected = false;
	int startX = 0;
	int startY = 0;

	//find start and end and setting x and y of start
	// checking top and bottom rows
	for (int col = 1; col < map.getCols() - 1; col++){
		if (map.getTile(0, col) == 3)
		if (!start){
			start = true;
			startX = 0;
			startY = col;
		}
		else
			//if multiple starts are found
			return false;
		else if (map.getTile(map.getRows() - 1, col) == 3)
		if (!start){
			start = true;
			startX = map.getRows() - 1;
			startY = col;
		}
		else
			//if multiple starts are found
			return false;
		if (map.getTile(0, col) == 4 || map.getTile(map.getRows() - 1, col) == 4)
		if (!end) {
			end = true;
		}
		else { //if multiple ends are found
			return false;
		}
	}
	// checking first and last columns
	for (int row = 1; row < map.getRows() - 1; row++){
		if (map.getTile(row, 0) == 3){
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
		else if (map.getTile(row, map.getCols() - 1) == 3){
			if (!start){
				start = true;
				startX = row;
				startY = map.getCols() - 1;
			}
			else {
				//if multiple starts are found
				return false;
			}
		}
		if (map.getTile(row, 0) == 4 || map.getTile(row, map.getCols() - 1) == 4)
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

	printMap();

	//outputting validation values
	cout << "Found start: " << start << endl;
	cout << "Found end: " << end << endl;
	cout << "Connected: " << connected << endl;

	return (start && end && connected);
}

bool MapEditor::isConnected(int x, int y) const{
	char dir;
	bool connected = true;

	//identifying and setting direction to check
	if (y == 0)
		dir = 'e';
	else if (y == map.getCols() - 1)
		dir = 'w';
	else if (x == 0)
		dir = 's';
	else if (x == map.getRows() - 1)
		dir = 'n';

	//moves along the path, identifying path tiles to the north, east, south, and west, depending on the current (x, y) position.
	do {
		//checking is path ending is next
		if (map.getTile(x + 1, y) == 4 || map.getTile(x - 1, y) == 4 || map.getTile(x, y + 1) == 4 || map.getTile(x, y - 1) == 4){
			break;
		}
		else if (dir == 'n'){		//if heading north, check other directions
			//path goes east
			if (map.getTile(x, y + 1) == 1){
				dir = 'e';
				++y;
			}
			//path goes north
			else if (map.getTile(x - 1, y) == 1) {
				--x;
			}
			//path goes west
			else if (map.getTile(x, y - 1) == 1){
				dir = 'w';
				--y;
			}
			else
				//no further path tiles found
				connected = false;
		}
		else if (dir == 'e'){		//if heading east, check other directions
			//path goes south
			if (map.getTile(x + 1, y) == 1) {
				dir = 's';
				++x;
			}
			//path goes east
			else if (map.getTile(x, y + 1) == 1) {
				++y;
			}
			//path goes north
			else if (map.getTile(x - 1, y) == 1) {
				dir = 'n';
				--x;
			}
			else
				//not further path tiles found
				connected = false;
		}
		else if (dir == 's'){	//if heading south, check other directions
			//path goes west
			if (map.getTile(x, y - 1) == 1) {
				dir = 'w';
				--y;
			}
			//path goes south
			else if (map.getTile(x + 1, y) == 1){
				++x;
			}
			//path goes east
			else if (map.getTile(x, y + 1) == 1) {
				dir = 'e';
				++y;
			}
			else
				//no further path tiles found
				connected = false;
		}
		else if (dir == 'w'){	//if heading west, check other directions
			//path goes north
			if (map.getTile(x - 1, y) == 1){
				dir = 'n';
				--x;
			}
			//path goes west
			else if (map.getTile(x, y - 1) == 1) {
				++y;
			}
			//path goes south
			else if (map.getTile(x + 1, y) == 1) {
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
	map.setTile(1, 0, 3);
	map.setTile(4, 7, 4);

	//creating path
	map.setTile(1, 1, 1);
	map.setTile(1, 2, 1);
	map.setTile(2, 2, 1);
	map.setTile(3, 2, 1);
	map.setTile(3, 1, 1);
	map.setTile(4, 1, 1);
	map.setTile(5, 1, 1);
	map.setTile(5, 2, 1);
	map.setTile(5, 3, 1);
	map.setTile(4, 3, 1);
	map.setTile(4, 4, 1);
	map.setTile(3, 4, 1);
	map.setTile(2, 4, 1);
	map.setTile(2, 5, 1);
	map.setTile(2, 6, 1);
	map.setTile(3, 6, 1);
	map.setTile(4, 6, 1);

	validateMap();

	//removing path tile to show detection of broken path
	map.setTile(5, 2, 0);

	validateMap();
}