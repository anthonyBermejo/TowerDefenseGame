#include "TextureManager.h"
#include <iostream>

using namespace std;


const string TextureManager::ENV_TEX_LOC = "test.png";
const string TextureManager::SPRITE_TEX_LOC = "creeps.png";
const string TextureManager::UI_TEX_LOC = "white-tower.png";

TextureManager::TextureManager(){
	
	//create array of textures and load them from
	//the texture files
	//texture[0] is Environment
	//texture[1] is Sprites
	//texture[2] is UI

	textures = new sf::Texture[3];
	textures[0].loadFromFile(ENV_TEX_LOC);
	textures[1].loadFromFile(SPRITE_TEX_LOC);
	textures[2].loadFromFile(UI_TEX_LOC);
}

TextureManager::~TextureManager(){
	//delete the textures
	/*for (int i = 0; i < 3; ++i){
		delete textures[i];
		textures[i] = NULL;
	}*/

	delete[] textures;
	textures = NULL;
}

sf::Texture& TextureManager::getTexture(TextureManager::TEXTURE tex) const{
	switch (tex){
	case ENV:
		return textures[0];
		break;
	case SPRITE:
		return textures[1];
		break;
	case UI:
		return textures[2];
		break;
	}
}