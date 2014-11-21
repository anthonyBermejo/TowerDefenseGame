#include "DrawableMapEditor.h"
#include "MainClass.h"
#include <iostream>

using namespace std;

DrawableMapEditor::DrawableMapEditor()
{

}


DrawableMapEditor::DrawableMapEditor(TextureManager* tm, sf::RenderWindow* win, MainClass* main)
{
	this->tm = tm;
	this->win = win;
	this->main = main;

	this->editor = new MapEditor(this->tm, this->win, this->main);
	this->editor->addObserver(this);
}

DrawableMapEditor::~DrawableMapEditor()
{
	win = NULL;
	tm = NULL;

	delete saveMapMsg;
	delete backMsg;
	delete loadMsg;
	delete createNewMsg;

	saveMapMsg = NULL;
	backMsg = NULL;
	loadMsg = NULL;
	createNewMsg = NULL;
}

void DrawableMapEditor::update(){

	int margin = editor->getMap()->getCols() / 4;

	loadMsg = new TextMessage(tm, "Load", sf::Vector2f(0, win->getSize().y - 30));
	saveMapMsg = new TextMessage(tm, "Save", sf::Vector2f(margin * 24, win->getSize().y - 30));
	backMsg = new TextMessage(tm, "Back", sf::Vector2f(margin * 2 * 24, win->getSize().y - 30));
	createNewMsg = new TextMessage(tm, "New", sf::Vector2f((margin * 3) * 24, win->getSize().y - 30));

	float scale = editor->getMap()->getCols() < 17 ? 1.0 : 2.0;

	loadMsg->setScale(sf::Vector2f(scale, scale));
	saveMapMsg->setScale(sf::Vector2f(scale, scale));
	backMsg->setScale(sf::Vector2f(scale, scale));
	createNewMsg->setScale(sf::Vector2f(scale, scale));

	loadMsg->drawMessage(win);
	saveMapMsg->drawMessage(win);
	backMsg->drawMessage(win);
	createNewMsg->drawMessage(win);

}

void DrawableMapEditor::draw(){
	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;
		if (x >= 0 && y >= 0){
			if (editor->getMap() != NULL){
				if (x < editor->getMap()->getRows()){
					editor->setPath(x, y);
				}
				else {
					//clicking on map editor buttons.
					int margin = editor->getMap()->getCols() / 4;
					if (y < margin){
						//clicking on Load
						std::string path;
						path = getFilePath();
						if (path.length() != 0) {
							loadMapFile(path);
						}
					}
					else if (y >= margin && y < margin * 2){
						if (editor->validateMap()){
							//clicking on Save
							std::string path;
							cout << "Enter path to save to: ";
							cin >> path;
							editor->saveMap(path);
						}
						else
							cout << "Failed to save map: Map is not valid.\n";
					}
					else if (y >= margin * 2 && y < margin * 3){
						main->switchToContext(MainClass::CONTEXT::MENU);
					}
					else{
						createCustomMap();
					}
				}
			}
		}
		prevClick = true;
	}

	if (!prevClick && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		int x = sf::Mouse::getPosition(*win).y / 24;
		int y = sf::Mouse::getPosition(*win).x / 24;

		if (x >= 0 && y >= 0){
			editor->setStartAndEnd(x, y);
		}
		prevClick = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
		if (!prevClick)
			prevClick = true;
	}
	else
		prevClick = false;

	if (editor->getMap() != NULL){
		update();
		editor->drawMap();
	}
}

void DrawableMapEditor::createCustomMap(){
	editor->createCustomMap();
}

std::string DrawableMapEditor::getFilePath(){
	return editor->getFilePath();
}

void DrawableMapEditor::loadMapFile(std::string path){
	editor->loadMapFile(path);
}