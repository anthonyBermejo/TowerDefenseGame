#include "Player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player(TextureManager* tm, sf::RenderWindow* w)
{
	coins = 500;
	health = 20;
	this->tm = tm;
	healthText = new TextMessage(tm, "Health: " + to_string(health), sf::Vector2f(w->getSize().x - 100, 10));
	coinsText = new TextMessage(tm, "Coins: " + to_string(coins), sf::Vector2f(w->getSize().x - 100, 20));
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

int Player::getHealth() const
{
	return health;
}

// Setters
void Player::setCoins(int coins)
{
	this->coins = coins;
	coinsText->setMessage("Coins: " + to_string(coins));
}

void Player::setHealth(int health)
{
	this->health = health;
	healthText->setMessage("Health: " + to_string(health));
	
}

void Player::Draw(sf::RenderWindow* w)
{
	coinsText->drawMessage(w);
	healthText->drawMessage(w);
}

// Custom methods

// Prints out the current attributes of a player
void Player::printPlayer() const
{
	cout << "Coins: " << coins;
	cout << "Health: " << health;
}