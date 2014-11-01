//used to hold a text message that will be drawn to the screen

#pragma once
#include "TextureManager.h";
#include <string>;

using namespace std;

class TextMessage{
public:
	TextMessage(TextureManager* tm, string msg, sf::Vector2f pos);

	void drawMessage(sf::RenderWindow* win);
public:
	void setLetter(int pos);

	sf::Sprite letter;
	string message;
	sf::Vector2f pos;

	const static string upperCase;
	const static string lowerCase;
	const static string symbols;
	const static string numbers;

};