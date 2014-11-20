#include "DrawableMap.h"
#include <iostream>

using namespace std;

DrawableMap::DrawableMap() {

}

DrawableMap::DrawableMap(Map* map, TextureManager* textureManager, sf::RenderWindow* w){
	this->map = map;
	this->w = w;
	this->texManager = textureManager;
	this->map->addObserver(this);
	
	//create sprites

	envSprite1.setTexture(texManager->getTexture(TextureManager::TEXTURE::ENV));
	envSprite1.setTextureRect(sf::IntRect(0, 0, 24, 24));

	envSprite2.setTexture(texManager->getTexture(TextureManager::ENV));
	envSprite2.setTextureRect(sf::IntRect(24, 0, 24, 24));

	pathSprite1.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite1.setTextureRect(sf::IntRect(24 * 2, 0, 24, 24));

	pathSprite2.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite2.setTextureRect(sf::IntRect(24 * 3, 0, 24, 24));

	pathSprite3.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite3.setTextureRect(sf::IntRect(24 * 4, 0, 24, 24));

	pathSprite4.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite4.setTextureRect(sf::IntRect(24 * 5, 0, 24, 24));

	pathSprite5.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite5.setTextureRect(sf::IntRect(24 * 6, 0, 24, 24));

	pathSprite6.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite6.setTextureRect(sf::IntRect(24 * 7, 0, 24, 24));

	pathSprite7.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite7.setTextureRect(sf::IntRect(24 * 8, 0, 24, 24));

	pathSprite8.setTexture(texManager->getTexture(TextureManager::ENV));
	pathSprite8.setTextureRect(sf::IntRect(24 * 9, 0, 24, 24));

	startSprite.setTexture(texManager->getTexture(TextureManager::TEXTURE::ENV));
	startSprite.setTextureRect(sf::IntRect(24 * 11, 0, 24, 24));

	endSprite.setTexture(texManager->getTexture(TextureManager::TEXTURE::ENV));
	endSprite.setTextureRect(sf::IntRect(24 * 10, 0, 24, 24));

	blockSprite.setTexture(texManager->getTexture(TextureManager::TEXTURE::ENV));
	blockSprite.setTextureRect(sf::IntRect(24 * 12, 0, 24, 24));
}


DrawableMap::~DrawableMap()
{
}

void DrawableMap::drawMap(){
	for (int i = 0; i < map->getCols(); ++i)
		for (int j = 0; j < map->getRows(); ++j){
		switch (map->getTile(j, i)){
		case Map::TILE_TYPE::ENV:
			envSprite1.setPosition(i * 24, j * 24);
			w->draw(envSprite1);
			break;
		case Map::TILE_TYPE::PATH:
			blockSprite.setPosition(i * 24, j * 24);
			w->draw(blockSprite);
			break;
		case Map::TILE_TYPE::START:
			blockSprite.setPosition(i * 24, j * 24);
			startSprite.setPosition(i * 24, j * 24);
			w->draw(blockSprite);
			w->draw(startSprite);
			break;
		case Map::TILE_TYPE::END:
			blockSprite.setPosition(i * 24, j * 24);
			endSprite.setPosition(i * 24, j * 24);
			w->draw(blockSprite);
			w->draw(endSprite);
			break;
		case Map::TILE_TYPE::CREEP:
			blockSprite.setPosition(i * 24, j * 24);
			w->draw(blockSprite);
			break;
		}
		}
}

void DrawableMap::update(){
	drawMap();
}