#include "Blob.h"

// __________________________________
//
// Class representing a Blob creep
//
//___________________________________

// Constructors
Blob::Blob(sf::Sprite sprite) : DrawableCreep()
{
}

Blob::Blob(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Deconstructor
Blob::~Blob()
{}
