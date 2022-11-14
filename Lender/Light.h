#pragma once
#include "Observer.h" // for later use
#include <glm/vec4.hpp>


class Light
{
private:
	glm::vec4 _position;
	glm::vec4 _diffuse;
	glm::vec4 _direction;
public:
	Light(glm::vec4 pos, glm::vec4 diffuse, glm::vec4 direction);
};

