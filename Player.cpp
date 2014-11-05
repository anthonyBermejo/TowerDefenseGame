#include "Player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player(TextureManager* tm, sf::RenderWindow* w)
{
	coins = 500;
	this->tm = tm;
	coinsText = new TextMessage(tm, "Coins: " + to_string(coins), sf::Vector2f(w->getSize().x - 100, 10));
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