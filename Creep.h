#pragma once

#include <vector>
#include "Map.h"
#include "Player.h"
#include "Observable.h"

using namespace std;

// Enum
enum Direction { UP, DOWN, LEFT, RIGHT };

// class definition
class Creep : public Observable {

public:
	Creep();
	Creep(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir);
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
};