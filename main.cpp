#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include "Map.h"
#include "CreepSquad.h"
#include <ctime>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	TextureManager* tm = new TextureManager();
	
	Map* m = new Map(20, 20, tm);

	CreepSquad* creepSquad = new CreepSquad(m, tm);
	creepSquad->resetCreepSquad(1);

	Player* player = new Player();

	for (int i = 0; i < 20; ++i)
		for (int j = 0; j < 20; ++j)
			m->setTile(i, j, Map::TILE_TYPE::ENV);

	m->setTile(5, 10, Map::TILE_TYPE::PATH);

	m->setTile(0, 4, Map::TILE_TYPE::START);
	m->setTile(15, 11, Map::TILE_TYPE::END);

	double elapsedTime = 0;
	double timePerFrame = 1 / 60; //60 frames per second
	std::clock_t startTime = std::clock();
	

	// test
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}


		//keep adding to elapsed time until it reaches timePerFrame
		if (elapsedTime <= timePerFrame)
			elapsedTime = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
		else{
			//update logic

			window.clear();
			m->drawMap(&window);
			creepSquad->move(player, &window);
			window.display();

			//reset clock
			elapsedTime = 0;
			startTime = std::clock();
		}
		

	}

	delete tm;
	tm = NULL;

	delete m;
	m = NULL;


	return 0;
}