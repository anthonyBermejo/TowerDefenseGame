#include "TextureManager.h"
#include <iostream>

using namespace std;


const string TextureManager::ENV_TEX_LOC = "test.png";
const string TextureManager::SPRITE_TEX_LOC = "creeps.png";
const string TextureManager::UI_TEX_LOC = "towerIcons.png";
const string TextureManager::FONT_TEX_LOC = "thickFont.png";
const string TextureManager::TOWER_TEX_LOC = "towers.png";
const string TextureManager::BACKGROUND_TEX_LOC = "background.png";

TextureManager::TextureManager(){
	
	//create array of textures and load them from
	//the texture files
	//texture[0] is Environment
	//texture[1] is Sprites
	//texture[2] is UI
	//texture[3] is FONT
	//texture[4] is TOWERS
	//texture[5] is BACKGROUND

	textures = new sf::Texture[6];
	textures[0].loadFromFile(ENV_TEX_LOC);
	textures[1].loadFromFile(SPRITE_TEX_LOC);
	textures[2].loadFromFile(UI_TEX_LOC);
	textures[3].loadFromFile(FONT_TEX_LOC);
	textures[4].loadFromFile(TOWER_TEX_LOC);
	textures[5].loadFromFile(BACKGROUND_TEX_LOC);
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
	case FONT:
		return textures[3];
		break;
	case TOWER:
		return textures[4];
		break;
	case BACKGROUND:
		return textures[5];
		break;
	}
}