#include "ModelGift.h"
#include "gift.h"

ModelGift::ModelGift(LightModel* lm, glm::vec3 color)
	: Renderable(lm, color)
{
	this->loadModel(gift, 399744, 3, 2);
}
