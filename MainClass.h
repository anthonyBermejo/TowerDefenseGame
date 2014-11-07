#pragma once

#include <SFML/Graphics.hpp>
#include "MapEditor.h"
#include "TextureManager.h"
#include <iostream>
#include "CreepSquad.h"
#include "Menu.h"
#include "Game.h"

using namespace std;

class MainClass{
public:
	enum CONTEXT{MENU,GAME,MAPEDIT};
	
	MainClass();
	virtual ~MainClass();

	void switchToContext(CONTEXT context);
	void switchToContext(CONTEXT context, bool newMap);

	void run();

	void setMapToPass(Map* m);

	void end();

private:
	bool gtfo;
	bool switchContext;
	CONTEXT currentContext;
	CONTEXT contextToSwitchTo;

	sf::RenderWindow* window;
	TextureManager* tm;

	Game* game;
	MapEditor* mEdit;
	Menu* menu;

	Map* mapToPass;//used to hold map when switching between the menu and (map editor or game)
	bool newMap;//used to determine if a new map is being created, or if a map is being loaded (when witching to map editor)
};