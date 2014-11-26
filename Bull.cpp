#include "Bull.h"

// __________________________________
//
// Class representing a Bull creep
//
//___________________________________

// Constructors
Bull::Bull(sf::Sprite* sprite) : DrawableCreep()
{
}

Bull::Bull(int hp, int speed, int defense, int reward, int strength, int locationX, int locationY, Direction dir, sf::Sprite* sprite) : DrawableCreep(hp, speed, defense, reward, strength, locationX, locationY, dir, sprite)
{
}

// Deconstructor
Bull::~Bull()
{
}