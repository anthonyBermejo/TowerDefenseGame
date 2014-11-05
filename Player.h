#pragma once

#include "TextMessage.h"
#include "TextureManager.h"

class Player
{
public:
	// constructor
	Player(TextureManager* tm, sf::RenderWindow* w);

	// destructor
	virtual ~Player();

	// getters
	int getCoins() const;
	int getHealth() const;

	// setters
	void setCoins(int coins);
	void setHealth(int health);

	// custom methods
	void printPlayer() const;

	void Draw(sf::RenderWindow* w);

private:
	int coins;
	int health;
	TextMessage* coinsText;
	TextMessage* healthText;
	TextureManager* tm;
};

