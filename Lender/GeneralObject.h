#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp> // glm::cos

#include <vector>
#include <iostream>

#include "LightModel.h"


class GeneralObject
{
protected:
	LightModel* _lightmodel;
	GeneralObject(LightModel* lm);
public:
	virtual void draw() = 0;
};

class GeneralModel : public GeneralObject
{
public:
	virtual void draw() = 0;
	virtual void loadModel(float* data) = 0;
};

class GeneralLight : public GeneralObject
{
protected:
	int _index;
	int _gLightCount;
	glm::vec3 _ads; //ambient, diffuse, specular
	std::string _shaderIndexString;
	GeneralLight(LightModel* lm, int id);
public:
	virtual void draw() = 0;
	virtual void setLightCount(int count) = 0;
	GeneralLight* setADS(glm::vec3 ads);
};
