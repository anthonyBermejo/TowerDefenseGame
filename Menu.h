#pragma once
#include "TextureManager.h";
#include "TextMessage.h";
#include "Map.h"
#include "MapEditor.h"
#include "SFML/Graphics.hpp"


class Menu{
public:
	Menu(TextureManager* tm, sf::RenderWindow* window);
	virtual ~Menu();
	void update();

private:
	TextMessage* titleMsg;
	TextMessage* playGameMsg;
	TextMessage* editorMsg;
	TextMessage* selectMapMsg;
	TextMessage* dimensionsMsg;

	TextMessage* userInput;

	bool* keysPressed;
	void saveInput();

	TextureManager* tm;
	sf::RenderWindow* win;
	MapEditor* editor;

	bool customCreated;
	bool mapSelected;
	bool prevClick;

	int selection;
	enum location{START,SELECT_MAP,MAP_EDIT,LOAD_MAP,CREATE_MAP};
	location menuLocation;

	void checkInput();
	std::string getFilePath();
};