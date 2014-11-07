#pragma once
#include "TextureManager.h"
#include "TextMessage.h"
#include "Map.h"
#include "MapEditor.h"
#include "SFML/Graphics.hpp"

class MainClass;


class Menu{
public:
	Menu(TextureManager* tm, sf::RenderWindow* window, MainClass* main);
	virtual ~Menu();
	void update();

private:
	TextMessage* titleMsg;
	TextMessage* playGameMsg;
	TextMessage* editorMsg;
	TextMessage* selectMapMsg;
	TextMessage* dimensionsMsg;
	TextMessage* exitMsg;

	TextMessage* userInput;

	bool* keysPressed;
	void saveInput();

	TextureManager* tm;
	sf::RenderWindow* win;
	MapEditor* editor;
	Map* map;
	MainClass* main;

	bool customCreated;
	bool mapSelected;
	bool prevClick;
	bool prevPress;

	int selection;
	enum location{START,SELECT_MAP,MAP_EDIT,LOAD_MAP,CREATE_MAP};
	location menuLocation;

	void checkInput();
	std::string getFilePath();
};