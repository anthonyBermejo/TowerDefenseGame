#pragma once

class Player
{
public:
	// constructor
	Player();

	// destructor
	virtual ~Player();

	// getters
	int getCoins() const;

	// setters
	void setCoins(int coins);

	// custom methods
	void printPlayer() const;

private:
	int coins;
};

