#pragma once
#include "Observer.h"
#include "MapEditor.h"
#include "TextureManager.h"

class DrawableMapEditor :
	public Observer
{
public:
	DrawableMapEditor();
	DrawableMapEditor(TextureManager* tm, sf::RenderWindow* win, MainClass* main);
	~DrawableMapEditor();

	void update();
	void createCustomMap();
	std::string getFilePath();
	void loadMapFile(std::string path);
	void draw();
private:
	MapEditor* editor;
	TextureManager* tm;
	sf::RenderWindow* win;
	MainClass* main;

	TextMessage* saveMapMsg;
	TextMessage* backMsg;
	TextMessage* loadMsg;
	TextMessage* createNewMsg;

	bool prevClick;
};

