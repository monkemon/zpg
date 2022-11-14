#include "PointLight.h"

PointLight::PointLight(LightModel* lm, float xpos, float ypos, float zpos, int id, int lc) :
	GeneralLight(lm, id)
{
	_shaderIndexString.append("Plights[");
	_shaderIndexString.append(std::to_string(id));
	_shaderIndexString.append("]");
	_pos = glm::vec4(xpos, ypos, zpos, 1.0);
	_attenuation = glm::vec3(1.0f, 0.1, 0.01);
	_gLightCount = lc;
}

void PointLight::setAttenuation(float c, float l, float q)
{
	_attenuation = glm::vec3(c, l, q);
}

void PointLight::addAttenuation(float c, float l, float q)
{
	_attenuation += glm::vec3(c, l, q);
}

void PointLight::draw()
{
	auto ss = _shaderIndexString;

	_lightmodel->useMe();
	
	_lightmodel->sendInt("pointLightCount", _gLightCount);
	_lightmodel->sendVec4((ss + ".position").c_str(), _pos);
	_lightmodel->sendVec3((ss + ".attenuation").c_str(), _attenuation);
}

void PointLight::setLightCount(int count)
{
	_gLightCount = count;
}
