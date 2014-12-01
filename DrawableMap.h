#pragma once
#include "Map.h"
#include "TextMessage.h"

class DrawableMap :
	public Observer
{
public:
	//Constructors and destructor
	DrawableMap();
	DrawableMap(Map* map, TextureManager* textureManager, sf::RenderWindow* w);
	~DrawableMap();

	//Utility methods
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
	void drawMap();
	void update();
private:
	//Pointers to the interworking parts
	Map* map;
	TextureManager* texManager;
	sf::RenderWindow* w;

	//Handle to game sprites
	sf::Sprite envSprite1; // solid green
	sf::Sprite envSprite2; // green with "grass"
	sf::Sprite pathSprite1;// verticle solid
	sf::Sprite pathSprite2;// vertical with variety
	sf::Sprite pathSprite3;// horizontal solid
	sf::Sprite pathSprite4;// horizontal with variety
	sf::Sprite pathSprite5;// top right
	sf::Sprite pathSprite6;// top left
	sf::Sprite pathSprite7;// bottom right
	sf::Sprite pathSprite8;// bottom left
	sf::Sprite startSprite;// start
	sf::Sprite endSprite;  // end
	sf::Sprite blockSprite;// block path
};