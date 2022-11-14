#include "Observer.h"

/*
* Returns 0 on success
*/
int Subject::attach(Observer* ob)
{
	auto size_before = this->observers.size();

	this->observers.push_back(ob);

	if (this->observers.size() > size_before)
		return 0;
	else
		return 1;
}

/*
* Returns 0 on success
*/
int Subject::detach(Observer* ob)
{
	auto size_before = this->observers.size();

	for (size_t i = 0; i < size_before; i++)
		if (this->observers[i] == ob)
			this->observers.erase(this->observers.begin() + i);
	
	if (this->observers.size() > size_before)
		return 0;
	else
		return 1;
}

/*
* Notifies all observers
*/
void Subject::notifyAll(IOdata type, void* data)
{
	for (auto& element : this->observers)
		element->notify(type, data);
	
	return;
}

