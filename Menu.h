#pragma once
#include "TextureManager.h";
#include "TextMessage.h";
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
	TextMessage* loadMsg;
	TextMessage* createNewMsg;
	TextMessage* dimensionsMsg;

	TextMessage* userInput;

	bool* keysPressed;
	void saveInput();

	TextureManager* tm;
	sf::RenderWindow* win;

	int selection;
	enum location{START,SELECT_MAP,MAP_EDIT,LOAD_MAP,CREATE_MAP};
	location menuLocation;

	void checkInput();

};