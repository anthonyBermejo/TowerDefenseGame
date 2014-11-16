#pragma once
#include "Observer.h"

class Observable
{
public:
	Observable();
	virtual ~Observable();
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
protected:
	void notify() const;
private:
	Observer** observers;
	static const int MAX_OBSERVERS;
	int numObservers;
};

