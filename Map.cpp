#include "Map.h"
#include <iostream>
#include <vector>
#include <stdlib.h> 

using namespace std;

Map::Map(int rows, int cols, TextureManager* texManager) :rows(rows), cols(cols), texManager(texManager)
{
	this->map = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 0));

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
}

Map::~Map()
{

}

void Map::setTile(int x, int y, TILE_TYPE val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = start
	*  3 = end
	*/

	//checking that x and y are within map range and that value is valid
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1) &&
		(val >= 0 && val <= 3))
		map[x][y] = val;
}

//printing map for testing
void Map::printMap() const {
	for (int i = 0; i < (int)map.size(); i++){
		for (int j = 0; j < (int)map[i].size(); j++)
			cout << "|" << map[i][j] << "|";
		cout << "\n";
	}
}

/*
const std::vector<std::vector<int>> Map::getMap(){
return map;
}
*/

//return the number of rows in the map
int Map::getRows() const{
	return map.size();
}

//returns the number of columns in the map
int Map::getCols() const{
	return map[0].size();
}

//retrieves that value at a specified x, y index
int Map::getTile(int x, int y) const {
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1))
		return map[x][y];
}

void Map::drawMap(sf::RenderWindow* w){

	int randNum;

	for (int i = 0; i < (int)map.size(); ++i)
		for (int j = 0; j < (int)map[i].size(); ++j){ 
		switch (map[i][j]){
			case TILE_TYPE::ENV:
				/*randNum = rand() % 100;
				if (randNum <= 50){
					envSprite1.setPosition(i * 24, j * 24);
					w->draw(envSprite1);
				}
				else{
					envSprite2.setPosition(i * 24, j * 24);
					w->draw(envSprite2);
				}*/
				envSprite1.setPosition(i * 24, j * 24);
				w->draw(envSprite1);

				break;
			case TILE_TYPE::PATH :
				//FUCK SO MUCH TO DO
				pathSprite1.setPosition(i * 24, j * 24);
				envSprite1.setPosition(i * 24, j * 24);
				w->draw(envSprite1);
				w->draw(pathSprite1);
				break;
			case TILE_TYPE::START:
				envSprite1.setPosition(i * 24, j * 24);
				startSprite.setPosition(i * 24, j * 24);
				w->draw(envSprite1);
				w->draw(startSprite);
				break;
			case TILE_TYPE::END:
				envSprite1.setPosition(i * 24, j * 24);
				endSprite.setPosition(i * 24, j * 24);
				w->draw(envSprite1);
				w->draw(endSprite);
				break;
			}
		}
}