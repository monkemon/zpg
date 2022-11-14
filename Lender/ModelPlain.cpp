#include "ModelPlain.h"
#include "plain.h"

ModelPlain::ModelPlain(LightModel* lm, glm::vec3 color)
	: Renderable(lm, color)
{
	this->loadModel(plain, 36, 3, 2);
}
