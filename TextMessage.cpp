#include "TextMessage.h"

using namespace std;

const string TextMessage::upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string TextMessage::lowerCase = "abcdefghijklmnopqrstuvwxyz";
const string TextMessage::symbols = "!@#$%^&*()[]{}+-=:;?/\\_.,\'\"";
const string TextMessage::numbers = "0123456789><~` "; // > and < look like arrows, ~ is a blank box, ` is a checked box

TextMessage::TextMessage(TextureManager* tm, string msg, sf::Vector2f pos) :message(msg), pos(pos){
	letter = sf::Sprite();
	letter.setTexture(tm->getTexture(TextureManager::TEXTURE::FONT));
	letter.setPosition(pos);

}

void TextMessage::drawMessage(sf::RenderWindow* win){
	
	for (int i = 0; i < message.length(); ++i){
		//update letter sprite based on the character we're at
		setLetter(i);
		win->draw(letter);
	}

	//reset x position of letter
	pos.x -= ((8 * letter.getScale().x) * (message.length()-1));
	letter.setPosition(pos);

}

void TextMessage::setColor(sf::Color c){
	letter.setColor(c);
}

void TextMessage::setMessage(string msg){
	message = msg;
}

void TextMessage::setScale(sf::Vector2f scale){
	letter.setScale(scale);
}

void TextMessage::setLetter(int pos){
	
	int x;
	
	//determine what type of character is at the current position
	if (upperCase.find(message[pos]) != -1){
		//it is an uppercase letter
		x = 8 * upperCase.find(message[pos]);
		letter.setTextureRect(sf::IntRect(x, 0, 8, 8));
	}else
		if (lowerCase.find(message[pos]) != -1){
			//it is an lower case letter
			x = 8 * lowerCase.find(message[pos]);
			letter.setTextureRect(sf::IntRect(x, 8, 8, 8));
		}
		else
			if (symbols.find(message[pos]) != -1){
				//it is a symbol
				x = 8 * symbols.find(message[pos]);
				letter.setTextureRect(sf::IntRect(x, 16, 8, 8));
			}else
				if (numbers.find(message[pos]) != -1){
					//it is a number
					x = 8 * numbers.find(message[pos]);
					letter.setTextureRect(sf::IntRect(x, 24, 8, 8));;
				}
				

	//phew
	if (pos != 0){
		this->pos.x += 8 * letter.getScale().x; //increment the position of the sprite by the width of a charater
		letter.setPosition(this->pos);
	}

//	cout << x;
}