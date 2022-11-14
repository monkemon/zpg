#pragma once
#include "Renderable.h"

class ModelSphere : public Renderable
{
public:
	ModelSphere(LightModel* lm, glm::vec3 color);
};

