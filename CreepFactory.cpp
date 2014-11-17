#include "CreepFactory.h"


CreepFactory::CreepFactory(TextureManager *textureManager)
{
	this->texManager = textureManager;
}


CreepFactory::~CreepFactory()
{
}

DrawableCreep* CreepFactory::getCreepAtLevel(int level, int startLocationX, int startLocationY)
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(texManager->getTexture(TextureManager::TEXTURE::SPRITE));

	switch (level)
	{
	case 1:
		sprite->setTextureRect(sf::IntRect(0, 0, 24, 24));
		return new Blob(20, 1, 5, 5, 50, startLocationX, startLocationY, Direction::RIGHT, sprite);
		break;
	case 2:
		sprite->setTextureRect(sf::IntRect(24 * 4, 0, 24, 24));
		return new Skeleton(30, 1, 10, 10, 50, startLocationX, startLocationY, Direction::RIGHT, sprite);

		break;
	case 3:
		sprite->setTextureRect(sf::IntRect(24 * 8, 0, 24, 24));
		return new Bull(100, 1, 5, 15, 50, startLocationX, startLocationX, Direction::RIGHT, sprite);

		break;
	case 4:
		sprite->setTextureRect(sf::IntRect(24 * 2, 0, 24, 24));
		return new Mage(40, 2, 10, 20, 60, startLocationX, startLocationY, Direction::RIGHT, sprite);
		break;
	case 5:
		sprite->setTextureRect(sf::IntRect(24 * 12, 0, 24, 24));
		return new Elf(40, 1, 25, 20, 60, startLocationX, startLocationY, Direction::RIGHT, sprite);
		break;
	case 6:
		sprite->setTextureRect(sf::IntRect(24 * 10, 0, 24, 24));
		return new Wolf(50, 3, 25, 30, 60, startLocationX, startLocationY, Direction::RIGHT, sprite);
		break;
	case 7:
		sprite->setTextureRect(sf::IntRect(24 * 6, 0, 24, 24));
		return new Ogre(1000, 1, 25, 1000, 60, startLocationX, startLocationY, Direction::RIGHT, sprite);
		break;
	default:
		sprite->setTextureRect(sf::IntRect(0, 0, 24, 24));
		return new Blob(20, 1, 5, 5, 50, startLocationX, startLocationY, Direction::RIGHT, sprite);
		break;
	}
}