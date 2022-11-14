#include "GeneralObject.h"

GeneralObject::GeneralObject(LightModel* lm) :
	_lightmodel(lm)
{
	// ctor
}


GeneralLight::GeneralLight(LightModel* lm, int id) :
	GeneralObject(lm), _index(id), _ads({ 0.5f, 0.5f, 0.5f }), _gLightCount(0)
{
	// ctor
}

GeneralLight* GeneralLight::setADS(glm::vec3 ads)
{
	_ads = ads;
	return this;
}
