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
			if (selection = 0)
				menuLocation = location::SELECT_MAP;
			else
				menuLocation = location::MAP_EDIT;
			selection = 0;
		}

		/*	opens file selection dialog and instantiates map with map file selected
		std::string path = getFilePath();
		MapEditor editor(path);
		Map* map = editor.getMap();
		map->setTextureManager(tm);
		map->drawMap(win);
		*/

		playGameMsg->drawMessage(win);
		editorMsg->drawMessage(win);
		break;
	case location::SELECT_MAP:
		break;
	case location::MAP_EDIT:
		mapEditor();
		break;
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
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	return ofn.lpstrFile;
}

void Menu::checkInput(){
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
}

void Menu::mapEditor(){
	loadMsg = new TextMessage(tm, "Load", sf::Vector2f(0, 50));
	createNewMsg = new TextMessage(tm, "New", sf::Vector2f(0, 75));

	loadMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	createNewMsg->setScale(sf::Vector2f(3.0f, 3.0f));

	//get user input for dimensions
	int rows;
	cout << "Enter number of rows: ";
	cin >> rows;
	int cols;
	cout << "Enter number of columns: ";
	cin >> cols;

	//create and draw map
	Map map(rows, cols, tm);
	map.drawMap(win);

	//set mouse action listeners
	//button clicks
	//if tile clicked is grass, set tile. If tile, set grass.

	//drawing overlying menu options
	loadMsg->drawMessage(win);
	createNewMsg->drawMessage(win);
}