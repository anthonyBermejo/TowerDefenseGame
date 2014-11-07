#include "MainClass.h"

using namespace std;

int main(){
	MainClass* theGame = new MainClass();//you just lost The Game :)

	//execution will remain here until a call to theGame->exit() get's called by someone
	theGame->run();

	delete theGame;
	theGame = NULL;

	return 0;
}