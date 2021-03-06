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
	int getStartLocationX() const;
	int getStartLocationY() const;
	Direction getDirection() const;
	sf::Time getMovementTime() const;
	sf::Time getSlowDownTime() const;
	sf::Time getElapsedSlowDownTime() const;
	bool isSlowedDown() const;

	// setters
	void setHitPoints(int hp);
	void setSpeed(int speed);
	void setDefense(int defense);
	void setReward(int reward);
	void setStrength(int strength);
	void setLocationX(int locationX);
	void setLocationY(int locationY);
	void setDirection(Direction direction);
	void setMovementTime(sf::Time time);
	void setSlowDownTime(sf::Time time);
	void setElapsedSlowDownTime(sf::Time time);
	void setSlowedDown(bool slow);

	// Custom methods
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
	int startLocationX;
	int startLocationY;
	Direction direction;
	sf::Time movementTime;
	sf::Time slowDownTime;
	sf::Time elapsedSlowDowntime;
	bool slowedDown;
};