#pragma once
#include<unordered_map>

#include "LightModel.h"

class Factory
{
};

class Flyweight;

class SharedState
{
private:
	int VBO;
};

class FlyweightFactory
{
private:
	std::unordered_map<std::string, Flyweight*> _flyweights;
};

