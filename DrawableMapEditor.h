#pragma once
#include "Observer.h"
#include "MapEditor.h"
#include "TextureManager.h"

class DrawableMapEditor :
	public Observer
{
public:
	//Constructors and destructor
	DrawableMapEditor();
	DrawableMapEditor(TextureManager* tm, sf::RenderWindow* win, MainClass* main);
	~DrawableMapEditor();

	//Utility methods
	void update();
	void createCustomMap();
	std::string getFilePath();
	void loadMapFile(std::string path);
	void draw();
private:
	//Pointers to interdependant parts
	MapEditor* editor;
	TextureManager* tm;
	sf::RenderWindow* win;
	MainClass* main;

	//Pointers to buttons
	TextMessage* saveMapMsg;
	TextMessage* backMsg;
	TextMessage* loadMsg;
	TextMessage* createNewMsg;

	//Boolean preventing double-clicks
	bool prevClick;
};

