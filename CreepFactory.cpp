#include "CreepFactory.h"


CreepFactory::CreepFactory(TextureManager *textureManager, Map* map)
{
	this->texManager = textureManager;
	this->map = map;
}


CreepFactory::~CreepFactory()
{
}

DrawableCreep* CreepFactory::getCreepAtLevel(int level)
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));
	Direction dir;

	// get x,y position of start tile of the map
	int startLocationX = map->getStart()[0];
	int startLocationY = map->getStart()[1];

	if (startLocationX == 0)
		dir = Direction::DOWN;
	else if (startLocationX == map->getRows() - 1)
		dir = Direction::UP;
	else if (startLocationY == 0)
		dir = Direction::RIGHT;
	else if (startLocationY == map->getCols() - 1)
		dir = Direction::LEFT;


	switch (level)
	{
	case 1:
		sprite->setTextureRect(sf::IntRect(0, 0, 24, 24));
		return new Blob(20, 1, 5, 5, 50, startLocationX, startLocationY, dir, sprite);
		break;
	case 2:
		sprite->setTextureRect(sf::IntRect(24 * 4, 0, 24, 24));
		return new Skeleton(30, 1, 10, 10, 50, startLocationX, startLocationY, dir, sprite);

		break;
	case 3:
		sprite->setTextureRect(sf::IntRect(24 * 8, 0, 24, 24));
		return new Bull(100, 1, 5, 15, 50, startLocationX, startLocationX, dir, sprite);

		break;
	case 4:
		sprite->setTextureRect(sf::IntRect(24 * 2, 0, 24, 24));
		return new Mage(40, 2, 10, 20, 60, startLocationX, startLocationY, dir, sprite);
		break;
	case 5:
		sprite->setTextureRect(sf::IntRect(24 * 12, 0, 24, 24));
		return new Elf(40, 1, 25, 20, 60, startLocationX, startLocationY, dir, sprite);
		break;
	case 6:
		sprite->setTextureRect(sf::IntRect(24 * 10, 0, 24, 24));
		return new Wolf(50, 3, 25, 30, 60, startLocationX, startLocationY, dir, sprite);
		break;
	case 7:
		sprite->setTextureRect(sf::IntRect(24 * 6, 0, 24, 24));
		return new Ogre(1000, 1, 25, 1000, 60, startLocationX, startLocationY, dir, sprite);
		break;
	default:
		sprite->setTextureRect(sf::IntRect(0, 0, 24, 24));
		return new Blob(20, 1, 5, 5, 50, startLocationX, startLocationY, dir, sprite);
		break;
	}
}