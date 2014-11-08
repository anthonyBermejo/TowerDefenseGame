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

	blockSprite.setTexture(texManager->getTexture(TextureManager::TEXTURE::ENV));
	blockSprite.setTextureRect(sf::IntRect(24 * 12, 0, 24, 24));
}

Map::Map()
{
	this->map = std::vector<std::vector<int> >(0, std::vector<int>(0));
}

Map::Map(int rows, int cols)
{
	this->map = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 0));
}

Map::~Map()
{
	//delete this;
	//this = NULL;
}

void Map::setTile(int x, int y, int val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = start
	*  3 = end
	*/

	//checking that x and y are within map range and that value is valid
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1) &&
		(val >= 0 && val <= 3)){
			if (val >= 0 && val <= 4){
				if (val == Map::START){
					start[0] = x;
					start[1] = y;
				}
				else if (val == Map::END) {
					end[0] = x;
					end[1] = y;
				}
				map[x][y] = val;
			}
		}
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
		(val >= 0 && val <= 4)){

		if (val == Map::START){
			start[0] = x;
			start[1] = y;
		}
		else if (val == Map::END) {
			end[0] = x;
			end[1] = y;
		}

		map[x][y] = val;
	}
}

int* Map::getStart(){
	return start;
}

int* Map::getEnd(){
	return end;
}

//printing map for testing
void Map::printMap() const {
	for (int i = 0; i < getRows(); i++){
		for (int j = 0; j < getCols(); j++)
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

	//int randNum;

	for (int i = 0; i < getCols(); ++i)
		for (int j = 0; j < getRows(); ++j){
		switch (map[j][i]){
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
			case TILE_TYPE::PATH:
				blockSprite.setPosition(i * 24, j * 24);
				w->draw(blockSprite);
				break;
			case TILE_TYPE::START:
				//drawPath(w);
				blockSprite.setPosition(i * 24, j * 24);
				startSprite.setPosition(i * 24, j * 24);
				w->draw(blockSprite);
				w->draw(startSprite);
				break;
			case TILE_TYPE::END:
				blockSprite.setPosition(i * 24, j * 24);
				endSprite.setPosition(i * 24, j * 24);
				w->draw(blockSprite);
				w->draw(endSprite);
				break;
			case TILE_TYPE::CREEP:
				blockSprite.setPosition(i * 24, j * 24);
				w->draw(blockSprite);
				break;
			}
		}
}

void Map::pathTest(){
	//setting start and end
	setTile(1, 0, Map::START);
	setTile(4, 7, Map::END);

	//creating path
	setTile(1, 1, Map::PATH);
	setTile(1, 2, Map::PATH);
	setTile(2, 2, Map::PATH);
	setTile(3, 2, Map::PATH);
	setTile(3, 1, Map::PATH);
	setTile(4, 1, Map::PATH);
	setTile(5, 1, Map::PATH);
	setTile(5, 2, Map::PATH);
	setTile(5, 3, Map::PATH);
	setTile(4, 3, Map::PATH);
	setTile(4, 4, Map::PATH);
	setTile(3, 4, Map::PATH);
	setTile(2, 4, Map::PATH);
	setTile(2, 5, Map::PATH);
	setTile(2, 6, Map::PATH);
	setTile(3, 6, Map::PATH);
	setTile(4, 6, Map::PATH);
}

void Map::startTest(){
	//setting start and end
	setTile(4, 10, Map::END);

	//creating path
	setTile(1, 1, Map::PATH);
	setTile(1, 2, Map::PATH);
	setTile(2, 2, Map::PATH);
	setTile(3, 2, Map::PATH);
	setTile(3, 1, Map::PATH);
	setTile(4, 1, Map::PATH);
	setTile(5, 1, Map::PATH);
	setTile(5, 2, Map::PATH);
	setTile(5, 3, Map::PATH);
	setTile(4, 3, Map::PATH);
	setTile(4, 4, Map::PATH);
	setTile(3, 4, Map::PATH);
	setTile(2, 4, Map::PATH);
	setTile(2, 5, Map::PATH);
	setTile(2, 6, Map::PATH);
	setTile(3, 6, Map::PATH);
	setTile(4, 6, Map::PATH);
	setTile(4, 7, Map::PATH);
	setTile(4, 8, Map::PATH);
	setTile(4, 9, Map::PATH);
}

void Map::endTest(){
	//setting start and end
	setTile(1, 0, Map::START);

	//creating path
	setTile(1, 1, Map::PATH);
	setTile(1, 2, Map::PATH);
	setTile(2, 2, Map::PATH);
	setTile(3, 2, Map::PATH);
	setTile(3, 1, Map::PATH);
	setTile(4, 1, Map::PATH);
	setTile(5, 1, Map::PATH);
	setTile(5, 2, Map::PATH);
	setTile(5, 3, Map::PATH);
	setTile(4, 3, Map::PATH);
	setTile(4, 4, Map::PATH);
	setTile(3, 4, Map::PATH);
	setTile(2, 4, Map::PATH);
	setTile(2, 5, Map::PATH);
	setTile(2, 6, Map::PATH);
	setTile(3, 6, Map::PATH);
	setTile(4, 6, Map::PATH);
	setTile(4, 7, Map::PATH);
	setTile(4, 8, Map::PATH);
}

void Map::brokenTest(){
	//setting start and end
	setTile(1, 0, Map::START);
	setTile(2, 8, Map::END);

	//creating path
	setTile(1, 1, Map::PATH);
	setTile(1, 2, Map::PATH);
	setTile(2, 2, Map::PATH);
	setTile(3, 2, Map::PATH);
	setTile(3, 1, Map::PATH);
	setTile(4, 1, Map::PATH);
	setTile(5, 1, Map::PATH);
	setTile(5, 2, Map::PATH);
	setTile(5, 3, Map::PATH);
	setTile(4, 3, Map::PATH);
	setTile(4, 4, Map::PATH);
	setTile(3, 4, Map::PATH);
	setTile(2, 4, Map::PATH);
	setTile(2, 5, Map::PATH);
	setTile(2, 7, Map::PATH);
}

void Map::drawPath(sf::RenderWindow* w){
	char dir;
	bool connected = true;
	int x = getStart()[0];
	int y = getStart()[1];

	//identifying and setting direction to check
	if (y == 0)
		dir = 'e';
	else if (y == getCols() - 1)
		dir = 'w';
	else if (x == 0)
		dir = 's';
	else if (x == getRows() - 1)
		dir = 'n';

	//moves along the path, identifying path tiles to the north, east, south, and west, depending on the current (x, y) position.
	do {
		//checking is path ending is next
		if (getTile(x + 1, y) == 4 || getTile(x - 1, y) == 4 || getTile(x, y + 1) == 4 || getTile(x, y - 1) == 4){
			break;
		}
		else if (dir == 'n'){		//if heading north, check other directions
			//path goes east
			if (getTile(x, y + 1) == 1){
				dir = 'e';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite5.setPosition(x * 24, y * 24);
				w->draw(pathSprite5);
				++y;
			}
			//path goes north
			else if (getTile(x - 1, y) == 1) {
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite1.setPosition(x * 24, y * 24);
				w->draw(pathSprite1);
				--x;
			}
			//path goes west
			else if (getTile(x, y - 1) == 1){
				dir = 'w';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite6.setPosition(x * 24, y * 24);
				w->draw(pathSprite6);
				--y;
			}
			else
				//no further path tiles found
				connected = false;
		}
		else if (dir == 'e'){		//if heading east, check other directions
			//path goes south
			if (getTile(x + 1, y) == 1) {
				dir = 's';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite7.setPosition(x * 24, y * 24);
				w->draw(pathSprite7);
				++x;
			}
			//path goes east
			else if (getTile(x, y + 1) == 1) {
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite3.setPosition(x * 24, y * 24);
				w->draw(pathSprite3);
				++y;
			}
			//path goes north
			else if (getTile(x - 1, y) == 1) {
				dir = 'n';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite8.setPosition(x * 24, y * 24);
				w->draw(pathSprite8);
				--x;
			}
			else
				//not further path tiles found
				connected = false;
		}
		else if (dir == 's'){	//if heading south, check other directions
			//path goes west
			if (getTile(x, y - 1) == 1) {
				dir = 'w';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite8.setPosition(x * 24, y * 24);
				w->draw(pathSprite8);
				--y;
			}
			//path goes south
			else if (getTile(x + 1, y) == 1){
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite1.setPosition(x * 24, y * 24);
				w->draw(pathSprite1);
				++x;
			}
			//path goes east
			else if (getTile(x, y + 1) == 1) {
				dir = 'e';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite7.setPosition(x * 24, y * 24);
				w->draw(pathSprite7);
				++y;
			}
			else
				//no further path tiles found
				connected = false;
		}
		else if (dir == 'w'){	//if heading west, check other directions
			//path goes north
			if (getTile(x - 1, y) == 1){
				dir = 'n';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite6.setPosition(x * 24, y * 24);
				w->draw(pathSprite6);
				--x;
			}
			//path goes west
			else if (getTile(x, y - 1) == 1) {
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite3.setPosition(x * 24, y * 24);
				w->draw(pathSprite3);
				++y;
			}
			//path goes south
			else if (getTile(x + 1, y) == 1) {
				dir = 's';
				envSprite1.setPosition(x * 24, y * 24);
				pathSprite8.setPosition(x * 24, y * 24);
				w->draw(pathSprite8);
				++x;
			}
			else
				//no further path tiles found
				connected = false;
		}
	} while (connected);	//checks if there are still path tiles
}

void Map::setTextureManager(TextureManager* tm){
	this->texManager = tm;
}