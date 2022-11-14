#include "ModelSphere.h"
#include "Sphere.h"

ModelSphere::ModelSphere(LightModel* lm, glm::vec3 color)
	: Renderable(lm, color)
{
	this->loadModel(sphere, 17280, 3, 2);
}
