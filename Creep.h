#pragma once

#include <vector>
#include "Map.h"
#include "Player.h"

using namespace std;

// Enum
enum Direction { UP, DOWN, LEFT, RIGHT };

enum SPRITE_TYPE { ELF, WOLF, BULL, OGRE, SKELETON, MAGE, SLIME };

// class definition
class Creep {

public:
	Creep(TextureManager* texManager);
	Creep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, TextureManager* tex, SPRITE_TYPE spriteType);
	virtual ~Creep();

	// getters
	int getHitPoints() const;
	int getSpeed() const;
	int getDefense() const;
	int getReward() const;
	int getStrength() const;
	int getLocationX() const;
	int getLocationY() const;
	Direction getDirection() const;
	sf::Sprite* getSprite() const;

	// setters
	void setHitPoints(int hp);
	void setSpeed(int speed);
	void setDefense(int defense);
	void setReward(int reward);
	void setStrength(int strength);
	void setLocationX(int locationX);
	void setLocationY(int locationY);
	void setDirection(Direction direction);

	// Custom methods
	void printCreep() const;
	void move(Map *map);
	void damageCreep(Player *player, int damage);

private:
	int hitPoints;
	int speed;
	int defense;
	int reward;
	int strength;
	int locationX;
	int locationY;
	Direction direction;
	SPRITE_TYPE spriteType;
	TextureManager* texManager; 
	
	sf::Sprite* sprite1;
	sf::Sprite* sprite2;

	void loadCreepSprites();
};