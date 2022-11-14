#pragma once
#include "GeneralObject.h"

class DirectionalLight : public GeneralLight
{
private:
	glm::vec3 _dir;
public:
	DirectionalLight(LightModel* lm, glm::vec3 dir, int id, int lc);

	void draw();

	void setLightCount(int count);
};
