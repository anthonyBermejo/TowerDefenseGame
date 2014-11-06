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
	delete dimensionsMsg;

	titleMsg = NULL;
	playGameMsg = NULL;
	editorMsg = NULL;
	selectMapMsg = NULL;
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
			cout << "path compare: " << path.compare("") << endl;
			if (path.compare("") != 0) {
				MapEditor editor(path, tm);
				map = editor.getMap();
				map->printMap();
				map->setTextureManager(tm);
				map->drawMap(win);
				mapSelected = true;
			}
			else
				menuLocation = location::START;
		}
		break;
	case location::MAP_EDIT:
		MapEditor editor(tm, win);
		editor.createCustomMap();
		break;
	}
}

std::string Menu::getFilePath(){
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

void Menu::checkInput(){
	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;
		if (editor != NULL && x >= 0 && y>= 0){
			editor->setPath(x, y);
		}
		prevClick = true;
	}

	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;

		if (editor != NULL && x >= 0 && y >= 0){
			editor->setStartAndEnd(x, y);
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