#include "DrawableTower.h"

using namespace std;

DrawableTower::DrawableTower(TOWER_TYPE type, int level, sf::Vector2i mapPos, CreepSquad* squad, Player* p, TextureManager* tm, int mapCols, int mapRows) :
Tower(type, level, mapPos, squad, p), tm(tm){

	//set the proper sprite
	sprite.setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
	sprite.setPosition(sf::Vector2f(mapPosition.x * 24.0f, mapPosition.y * 24.0f));

	switch (type){
	case REGULAR:
		sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
		break;
	case ICE:
		sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
		break;
	case CANNON:
		sprite.setTextureRect(sf::IntRect(48, 0, 24, 24));
		break;
	case SUPER:
		sprite.setTextureRect(sf::IntRect(72, 0, 24, 24));
		break;
	}

	//calculate the proper size and position for the rectangle which displays the tower's range
	float left = mapPos.x - range;
	float top = mapPos.y - range;
	
	float width;
	if (left + (range * 2 + 1) > mapCols)//width goes outside of map
		width = mapCols - left;
	else
		width = range * 2 + 1;

	float height;
	if (top + (range * 2 + 1) > mapRows)//height goes outside of map
		height = mapRows - top;
	else
		height = range * 2 + 1;

	rangeRect.setPosition(left*24, top*24);
	rangeRect.setSize(sf::Vector2f(width*24, height*24));
	rangeRect.setFillColor(sf::Color::Color(0, 0, 255, 120));
	rangeRect.setOutlineThickness(1);
	rangeRect.setOutlineColor(sf::Color::Color(0, 0, 0, 170));

}

void DrawableTower::Draw(sf::RenderWindow* w,bool isSelected){
	w->draw(sprite);
	if (isSelected) //draw range rectangle when the Tower is selected
		w->draw(rangeRect);
}