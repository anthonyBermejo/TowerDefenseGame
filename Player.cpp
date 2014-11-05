#include "Player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player(TextureManager* tm)
{
	coins = 500;
	this->tm = tm;
	coinsText = new TextMessage(tm, "Coins: " + to_string(coins), sf::Vector2f(120, 10));
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
	coinsText->setMessage("Coins: " + to_string(coins));
}

void Player::Draw(sf::RenderWindow* w)
{
	coinsText->drawMessage(w);
}

// Custom methods

// Prints out the current attributes of a player
void Player::printPlayer() const
{
	cout << "Coins: " << coins << endl << endl;
}