#include "Observable.h"

// ___________________________________________________
//
// Class representing an Observerable class
//
//____________________________________________________

const int Observable::MAX_OBSERVERS = 10;

// Constructor
Observable::Observable()
{
	observers = new Observer*[MAX_OBSERVERS];
	numObservers = 0;
}

// Destructor
Observable::~Observable()
{
	delete observers;
}

// Adds an observer to it's list of observers
void Observable::addObserver(Observer* obs)
{
	if (numObservers < MAX_OBSERVERS) {
		for (int i = 0; i < MAX_OBSERVERS; ++i) {
			if (observers[i] == obs)
				return;
		}

		observers[numObservers] = obs;
		++numObservers;
	}
}

// Calls the update of all observers that observe this class
void Observable::notify() const
{
	for (int i = 0; i < numObservers; ++i)
		observers[i]->update();
}
