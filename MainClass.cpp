#include "MainClass.h"

using namespace std;

MainClass::MainClass(){

	gtfo = false;
	switchContext = false;

	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Tower Defense");
	
	currentContext = CONTEXT::MENU;
	tm = new TextureManager();

	game = NULL;
	mEdit = NULL;

	//initialize menu since it's the first one displayed
	menu = new Menu(tm, window, this);
}

MainClass::~MainClass(){
	if (menu != NULL){
		delete menu;
		menu = NULL;
	}

	if (game != NULL){
		delete game;
		game = NULL;
	}

	if (mEdit != NULL){
		delete mEdit;
		mEdit = NULL;
	}

	if (mapToPass != NULL){
		delete mapToPass;
		mapToPass = NULL;
	}

	delete tm;
	tm = NULL;

	delete window;
	window = NULL;
	
}

void MainClass::run(){
	//keep running until it's time to close the program (ie, pop out of this method)
	while (!gtfo){
		switch (currentContext){
		case MENU:
			window->clear();
			menu->update();
			window->display();
			break;
		case GAME:
			game->update();
			break;
		case MAPEDIT:
			window->clear();
			mEdit->update();
			window->display();
			break;
		}

		//has there been a call to switch context?
		if (switchContext){
			switch (contextToSwitchTo){
			case MENU:
				//delete currently running context
				switch (currentContext){
				case GAME:
					delete game;
					game = NULL;
					break;
				case MAPEDIT:
					delete mEdit;
					mEdit = NULL;
					break;
				}

				//switch to menu
				menu = new Menu(tm, window,this);
				menu->setPrevPress(true);
				window->create(sf::VideoMode(800, 600), "Tower Defense");
				currentContext = MENU;
				break;

			case GAME:
				//The only place you should switch to game is from the MENU (no validation at this time)
				delete menu;
				menu = NULL;
				game = new Game(window, mapToPass, tm,this);
				game->run();
				currentContext = GAME;
				break;
			case MAPEDIT:
				//the only place you should switch to map editor is from the MENU (no validation at this time)
				delete menu;
				menu = NULL;
				
				mEdit = new MapEditor(tm, window,this);

				//creating new map
				if (newMap){
					mEdit->createCustomMap();
				}
				else{
					std::string path = mEdit->getFilePath();
					if (path.length() != 0) {
						mEdit->loadMapFile(path);
					}
				}
				//create the map editor with one of many constructors? :P
				currentContext = MAPEDIT;
			}
		}
		//reset switchContext since it has been done :D
		switchContext = false;
	}
}

void MainClass::switchToContext(MainClass::CONTEXT context){
	switchContext = true;
	contextToSwitchTo = context;
}

void MainClass::switchToContext(MainClass::CONTEXT context, bool newMap){
	switchContext = true;
	contextToSwitchTo = context;
	this->newMap = newMap;
}

void MainClass::setMapToPass(Map* m){
	mapToPass = m;
}

void MainClass::end(){
	gtfo = true;
}



