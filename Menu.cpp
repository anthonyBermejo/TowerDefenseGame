#include "Menu.h"
#include "MapEditor.h"
#include <iostream>
#include <Windows.h>
#include <commdlg.h>

using namespace std;

Menu::Menu(TextureManager* tm, sf::RenderWindow* win) :tm(tm), win(win){
	titleMsg = new TextMessage(tm, "Tower Defense", sf::Vector2f(0, 0));
	titleMsg->setScale(sf::Vector2f(4.0f, 4.0f));
	playGameMsg = new TextMessage(tm, "PLAY GAME", sf::Vector2f(0,100));
	playGameMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	editorMsg = new TextMessage(tm, "Map Editor", sf::Vector2f(0, 150));
	editorMsg->setScale(sf::Vector2f(3.0f, 3.0f));

	menuLocation = location::START;
	selection = 0;

	this->tm = tm;
	this->win = win;

	keysPressed = new bool[5];//up,right,down,left,enter
	for (int i = 0; i < 5; ++i)
		keysPressed[i] = false;
}

Menu::~Menu(){
	delete titleMsg;
	delete playGameMsg;
	delete editorMsg;
	delete selectMapMsg;
	delete loadMsg;
	delete createNewMsg;
	delete dimensionsMsg;

	titleMsg = NULL;
	playGameMsg = NULL;
	editorMsg = NULL;
	selectMapMsg = NULL;
	loadMsg = NULL;
	createNewMsg = NULL;
	dimensionsMsg = NULL;

	tm = NULL;
	win = NULL;
	
	//delete[] keysPressed;
	//keysPressed = NULL;
}

void Menu::update(){
	titleMsg->drawMessage(win);
	checkInput();
	
	std::string path;

	switch (menuLocation){
	case location::START:
		if (keysPressed[0] && !keysPressed[2]){//select play game
			selection = 0;
			playGameMsg->setMessage("PLAY GAME");
			editorMsg->setMessage("Map Editor");		
		}

		if (keysPressed[2] && !keysPressed[0]){
			selection = 1;
			playGameMsg->setMessage("Play Game");
			editorMsg->setMessage("MAP EDITOR");
		}

		if (keysPressed[4]){
			if (selection == 0)
				menuLocation = location::SELECT_MAP;
			else
				menuLocation = location::MAP_EDIT;
			selection = 0;
		}
		playGameMsg->drawMessage(win);
		editorMsg->drawMessage(win);
		break;
	case location::SELECT_MAP:
		if (!mapSelected){
			path = getFilePath();
			editor = new MapEditor(path);
			map = editor->getMap();
			map->setTextureManager(tm);
			map->drawMap(win);
			mapSelected = true;
		}
		break;
	case location::MAP_EDIT:
		if (!customCreated)
			mapEditor();
		break;
	}
	if (map != NULL){		//print custom map, not loaded map
		map->drawMap(win);
	}
}

std::string Menu::getFilePath(){
	OPENFILENAME ofn;
	char szFile[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	//project->properties->config properties->general->character set->Default is UNICODE, changed to "Not Set"
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	//project->properties->config properties->general->character set->Default is UNICODE, changed to "Not Set"
	ofn.lpstrFilter = "XML Map File\0*.xml\00";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	return ofn.lpstrFile;
}

void Menu::checkInput(){
	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;
		if (map != NULL){
			if (map->getTile(x, y) == 0)
				map->setTile(x, y, 1);
			else if (map->getTile(x, y) == 1)
				map->setTile(x, y, 0);
			map->drawMap(win);
		}
		prevClick = true;
	}

	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;

		if (map != NULL){
			if (!startSet && (x == 0 || y == 0 || x == map->getRows() - 1 || y == map->getCols() - 1)){
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
		prevClick = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		keysPressed[0] = true;
	else
		keysPressed[0] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		keysPressed[1] = true;
	else
		keysPressed[1] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		keysPressed[2] = true;
	else
		keysPressed[2] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		keysPressed[3] = true;
	else
		keysPressed[3] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
		keysPressed[4] = true;
	else
		keysPressed[5] = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
		if (!prevClick)
			prevClick = true;
	}
	else
		prevClick = false;
}

void Menu::mapEditor(){
	loadMsg = new TextMessage(tm, "Load", sf::Vector2f(0, 50));
	createNewMsg = new TextMessage(tm, "New", sf::Vector2f(0, 75));

	loadMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	createNewMsg->setScale(sf::Vector2f(3.0f, 3.0f));

	int rows = 0;
	int cols = 0;

	
	//get user input for dimensions
	cout << "Enter number of rows: ";
	cin >> rows;
	cout << "Enter number of columns: ";
	cin >> cols;
	
	//create and draw map
	map = new Map(rows, cols, tm);
	customCreated = true;
	win->setSize(sf::Vector2u(cols * 24, rows * 24));
	map->drawMap(win);

	/* saves map sent in
	MapEditor editor(map);
	editor.saveMap("C:\\hurrdurr.xml");
	*/

	//set mouse action listeners
	//button clicks
	//if tile clicked is grass, set tile. If tile, set grass.

	//drawing overlying menu options
	loadMsg->drawMessage(win);
	createNewMsg->drawMessage(win);
}