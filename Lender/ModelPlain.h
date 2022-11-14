#pragma once
#include "Renderable.h"

class ModelPlain : public Renderable
{
public:
	ModelPlain(LightModel* lm, glm::vec3 color);
};

