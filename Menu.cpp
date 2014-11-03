#include "Menu.h"

using namespace std;

Menu::Menu(TextureManager* tm, sf::RenderWindow* win) :tm(tm), win(win){
	titleMsg = new TextMessage(tm, "Tower Defense", sf::Vector2f(0, 0));
	titleMsg->setScale(sf::Vector2f(4.0f, 4.0f));
	playGameMsg = new TextMessage(tm, "PLAY GAME", sf::Vector2f(0,100));
	playGameMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	editorMsg = new TextMessage(tm, "Map Editor", sf::Vector2f(0, 150));
	editorMsg->setScale(sf::Vector2f(3.0f, 3.0f));
	selectMapMsg = new TextMessage(tm, "Select map:", sf::Vector2f(0, 0));
	loadMsg = new TextMessage(tm, "Load existing map", sf::Vector2f(0, 0));
	createNewMsg = new TextMessage(tm, "Create new map", sf::Vector2f(0, 0));
	dimensionsMsg = new TextMessage(tm, "Enter map dimensions", sf::Vector2f(0, 0));

	menuLocation = location::START;
	selection = 0;

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

		playGameMsg->drawMessage(win);
		editorMsg->drawMessage(win);
		break;
	case location::SELECT_MAP:
		break;

	}
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

