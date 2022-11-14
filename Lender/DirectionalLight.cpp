#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(LightModel* lm, glm::vec3 dir, int id, int lc) :
	GeneralLight(lm, id), _dir(dir)
{
	_shaderIndexString.append("Dlights[");
	_shaderIndexString.append(std::to_string(id));
	_shaderIndexString.append("]");
	_gLightCount = lc;
}

void DirectionalLight::draw()
{
	auto ss = _shaderIndexString;

	_lightmodel->useMe();

	_lightmodel->sendInt("dirLightCount", _gLightCount);
	_lightmodel->sendVec3((ss + ".direction").c_str(), _dir);
	_lightmodel->sendVec3((ss + ".ads").c_str(), _ads);
}

void DirectionalLight::setLightCount(int count)
{
	_gLightCount = count;
}
