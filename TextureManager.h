#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class TextureManager{
public:
	enum TEXTURE{ENV,SPRITE,UI,FONT,TOWER,BACKGROUND};


	TextureManager();
	~TextureManager();

	sf::Texture& getTexture(TEXTURE tex) const;

private:
	sf::Texture* textures;

	const static string ENV_TEX_LOC;
	const static string SPRITE_TEX_LOC;
	const static string UI_TEX_LOC;
	const static string FONT_TEX_LOC;
	const static string TOWER_TEX_LOC;
	const static string BACKGROUND_TEX_LOC;

};
#endif