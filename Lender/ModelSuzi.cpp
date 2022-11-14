#include "ModelSuzi.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"

ModelSuzi::ModelSuzi(LightModel* lm, bool flat, glm::vec3 color)
	: Renderable(lm, color)
{
	if (flat)
		this->loadModel(suziFlat, 17424, 3, 2);
	else
		this->loadModel(suziSmooth, 17424, 3, 2);
}
