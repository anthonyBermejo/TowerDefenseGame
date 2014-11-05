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

	// setters
	void setCoins(int coins);

	// custom methods
	void printPlayer() const;

	void Draw(sf::RenderWindow* w);

private:
	int coins;
	TextMessage* coinsText;
	TextureManager* tm;
};

