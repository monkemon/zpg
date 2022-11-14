#pragma once
#include <vector>
#include <iostream>

template <typename T> class Component
{
public:
	virtual T invoke() = 0;
};

template <typename T> class Composite : public Component<T>
{
protected:
	std::vector<Component<T>*> components;
public:
	/*
	* Returns 0 on success
	*/
	int addItem(Component<T>* c)
	{
		auto self = this;
		auto size_before = this->components.size();
		if (c == self) return 1;
		this->components.push_back(c);
		if (this->components.size() > size_before)
			return 0;
		else
			return 1;
	}

	/*
	* Returns 0 on success
	*/
	int deleteItem(Component<T>* c)
	{
		auto size_before = this->components.size();

		for (size_t i = 0; i < size_before; i++)
			if (this->components[i] == c)
				this->components.erase(this->components.begin() + i);
		
		if (this->components.size() < size_before)
			return 0;
		else
			return 1;
	}

	virtual T invoke() override = 0;
};

template <typename T> class Leaf : public Component<T>
{
protected:
	T _value;
public:
	Leaf(T leaf_value)
	{
		this->_value = leaf_value;
	}
	T invoke()
	{
		return this->_value;
	}
};
