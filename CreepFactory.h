#pragma once

#include "Creep.h"
#include "Blob.h"
#include "Bull.h"
#include "Elf.h"
#include "Mage.h"
#include "Ogre.h"
#include "Skeleton.h"
#include "Wolf.h"
#include "DrawableCreep.h"

class CreepFactory
{
public:
	CreepFactory(TextureManager* textureManager);
	~CreepFactory();

	DrawableCreep* getCreepAtLevel(int, int, int);

private:
	TextureManager * texManager;
};

