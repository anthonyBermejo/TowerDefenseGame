#include "Player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player()
{
	coins = 0;
}

// Destructors
Player::~Player()
{
}

// Getters
int Player::getCoins() const
{
	return coins;
}

// Setters
void Player::setCoins(int coins)
{
	this->coins = coins;
}

// Custom methods

// Prints out the current attributes of a player
void Player::printPlayer() const
{
	cout << "Coins: " << coins << endl << endl;
}