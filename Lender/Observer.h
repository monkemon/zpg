#pragma once
#include <iostream>
#include <vector>

enum class IOdata
{
	MOUSE_POS,
	KBD_PRESS,
	MOUSE_KEY,
	CAMERA_MOVED,
	CAMERA_DATA,
	WINDOW_RESIZE,
	SCROLL
};

class Observer
{
public:
	virtual void notify(IOdata type, void* data) = 0;
};

class Subject
{
protected:
	std::vector<Observer*> observers;
public:
	int attach(Observer* ob);
	int detach(Observer* ob);
	virtual void notifyAll(IOdata type, void* data);
};

