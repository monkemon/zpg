#pragma once

#include "GeneralObject.h"
#include "Observer.h"

class SpotLight : public GeneralLight, public Observer
{
private:
	glm::vec4 _position;
	glm::vec3 _attenuation;
	glm::vec3 _direction;
	float _cutoff;
	float _outerCutoff;
public:
	SpotLight(LightModel* lm,
		glm::vec3 pos,
		glm::vec3 attenuation,
		glm::vec3 direction,
		float cutoff,
		float outercut,
		int id,
		int lc);

	void draw();
	void setLightCount(int count);
	void notify(IOdata type, void* data);
};

