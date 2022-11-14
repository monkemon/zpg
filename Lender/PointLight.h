#pragma once
#include "GeneralObject.h"

class PointLight : public GeneralLight
{
private:
	glm::vec3 _attenuation;
	glm::vec4 _pos;
public:
	PointLight(LightModel* lm,
		float xpos, 
		float ypos, 
		float zpos, 
		int id, 
		int lc);

	void setAttenuation(float c, float l, float q);

	void addAttenuation(float c, float l, float q);

	void draw();

	void setLightCount(int count);
};


