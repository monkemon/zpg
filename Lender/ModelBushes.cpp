#include "ModelBushes.h"
#include "bushes.h"

ModelBushes::ModelBushes(LightModel* lm, glm::vec3 color)
	: Renderable(lm, color)
{
	this->loadModel(plain, 54210, 3, 2);
}
