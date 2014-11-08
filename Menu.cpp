#include "Menu.h"
#include "MapEditor.h"
#include <iostream>
#include "MainClass.h"

using namespace std;

Menu::Menu(TextureManager* tm, sf::RenderWindow* win, MainClass* main) :tm(tm), win(win),main(main){
	titleMsg = new TextMessage(tm, "Tower Defense", sf::Vector2f(0, 0));
	titleMsg->setScale(sf::Vector2f(4.0f, 4.0f));
	playGameMsg = new TextMessage(tm, "PLAY GAME", sf::Vector2f(0, 100));
	playGameMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	editorMsg = new TextMessage(tm, "Map Editor", sf::Vector2f(0, 150));
	editorMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	exitMsg = new TextMessage(tm, "Exit", sf::Vector2f(0, 200));
	exitMsg->setScale(sf::Vector2f(3.0f, 3.0f));

	newMapMsg = new TextMessage(tm, "NEW MAP", sf::Vector2f(0, 100));
	newMapMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	loadMapMsg = new TextMessage(tm, "Load Map", sf::Vector2f(0, 150));
	loadMapMsg->setScale(sf::Vector2f(3.0f, 3.0f));

	menuLocation = location::START;
	selection = 0;
	prevClick = false;
	prevPress = false;

	this->tm = tm;
	this->win = win;
	
	editor = new MapEditor(tm, win,main);

	background = new sf::Sprite();
	background->setTexture(tm->getTexture(TextureManager::TEXTURE::BACKGROUND));
	background->setPosition(sf::Vector2f(288, 100));

	keysPressed = new bool[5];//up,right,down,left,enter
	for (int i = 0; i < 5; ++i)
		keysPressed[i] = false;
}

Menu::~Menu(){
	delete titleMsg;
	delete playGameMsg;
	delete editorMsg;
	delete newMapMsg;
	delete loadMapMsg;
	delete background;

	titleMsg = NULL;
	playGameMsg = NULL;
	editorMsg = NULL;
	newMapMsg = NULL;
	loadMapMsg = NULL;

	tm = NULL;
	win = NULL;
	background = NULL;

	delete editor;
	editor = NULL;

	//delete[] keysPressed;
	//keysPressed = NULL;
}

void Menu::update(){
	
	titleMsg->drawMessage(win);
	win->draw(*background);
	checkInput();

	std::string path;

	switch (menuLocation){
	case location::START:
		if (keysPressed[0] && !keysPressed[2]){//up

			selection--;
			if (selection < 0)selection = 0;
			switch (selection){
			case 0:
				playGameMsg->setMessage("PLAY GAME");
				editorMsg->setMessage("Map Editor");
				break;
			case 1:
				editorMsg->setMessage("MAP EDITOR");
				exitMsg->setMessage("Exit");
				break;
			}
		}

		if (keysPressed[2] && !keysPressed[0]){//down
			
			selection++;
			if (selection > 2)selection = 2;
			switch (selection){
			case 1:
				playGameMsg->setMessage("Play Game");
				editorMsg->setMessage("MAP EDITOR");
				break;
			case 2:
				editorMsg->setMessage("Map Editor");
				exitMsg->setMessage("EXIT");
				break;
			}
		}

		if (keysPressed[4]){
			switch (selection){
			case 0:
				menuLocation = location::SELECT_MAP;
				break;
			case 1:
				menuLocation = location::MAP_EDIT;
				break;
			case 2:
				main->end();
				break;
			}
			
			selection = 0;
		}
		playGameMsg->drawMessage(win);
		editorMsg->drawMessage(win);
		exitMsg->drawMessage(win);
		break;
	case location::SELECT_MAP:
		path = editor->getFilePath();
		if (path.length() != 0) {
			editor->loadMapFile(path);
			//here is your Map instance, my dear sir.
			//
			// :D
			map = editor->getMap();
			//pass map to MainClass
			main->setMapToPass(map);
			//get rid of pointer, then switch context
			map = NULL;
			main->switchToContext(MainClass::CONTEXT::GAME);
			break;
		}
		break;
	case location::MAP_EDIT:
		//editor->createCustomMap();
		if (keysPressed[0] && !keysPressed[2]){//up
			selection = 0;
			newMapMsg->setMessage("NEW MAP");
			loadMapMsg->setMessage("Load Map");
			break;
		}

		if (keysPressed[2] && !keysPressed[0]){//down
			selection = 1;
			newMapMsg->setMessage("New Map");
			loadMapMsg->setMessage("LOAD MAP");
			break;
		}

		if (keysPressed[4]){//enter
			switch (selection){
			case 0://create map
				menuLocation = CREATE_MAP;
				break;
			case 1:
				menuLocation = LOAD_MAP;
			}

		}

		newMapMsg->drawMessage(win);
		loadMapMsg->drawMessage(win);
		break;

	case CREATE_MAP:
		main->switchToContext(MainClass::CONTEXT::MAPEDIT, true);
		break;

	case LOAD_MAP:
		//dito
		main->switchToContext(MainClass::CONTEXT::MAPEDIT, false);
		break;
	}


}

void Menu::checkInput(){

	for (int i = 0; i < 5; ++i)
		keysPressed[i] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
		if (!prevPress){
			prevPress = true;
			keysPressed[0] = true;
		}
		else
			keysPressed[0] = false;

		return;
	}
	else{
		keysPressed[0] = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !prevPress)
		keysPressed[1] = true;
	else
		keysPressed[1] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
		if (!prevPress){
			prevPress = true;
			keysPressed[2] = true;
		}
		else
			keysPressed[2] = false;

		return;
	}
	else{
		keysPressed[2] = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !prevPress)
		keysPressed[3] = true;
	else
		keysPressed[3] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
		if (!prevPress){
			keysPressed[4] = true;
			prevPress = true;
		}
		else
			keysPressed[4] = false;

		return;
	}
	else{
		keysPressed[4] = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
		if (!prevClick)
			prevClick = true;
	}
	else
		prevClick = false;

	
	if (!keysPressed[0] && !keysPressed[2] && !keysPressed[4])
		prevPress = false;

}

void Menu::setPrevPress(bool b){
	prevPress = b; //Should only be used when returning from game. Since you return from game by pressing enter
	//when you return to the Menu, on the first iteration of the update loop it's likely the enter key will be pressed
}