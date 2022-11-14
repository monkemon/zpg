#include "SpotLight.h"

SpotLight::SpotLight(LightModel* lm,
	glm::vec3 pos,
	glm::vec3 attenuation,
	glm::vec3 direction,
	float cutoff,
	float outercut,
	int id,
	int lc) :
	GeneralLight(lm, id),
	_position(pos.x, pos.y, pos.z, 1.0f),
	_attenuation(attenuation),
	_direction(direction),
	_cutoff(cutoff),
	_outerCutoff(outercut)
{
	_shaderIndexString.append("Slights[");
	_shaderIndexString.append(std::to_string(_index));
	_shaderIndexString.append("]");
	_gLightCount = lc;
}

void SpotLight::draw()
{
	auto ss = _shaderIndexString;
	auto cutoff = glm::cos(glm::radians(_cutoff));
	auto outer = glm::cos(glm::radians(_outerCutoff));

	_lightmodel->useMe();

	_lightmodel->sendInt("spotLightCount", _gLightCount);
	_lightmodel->sendVec4((ss + ".position").c_str(), _position);
	_lightmodel->sendVec3((ss + ".attenuation").c_str(), _attenuation);
	_lightmodel->sendVec3((ss + ".direction").c_str(), _direction);
	_lightmodel->sendFloat((ss + ".cutoff").c_str(), cutoff);
	_lightmodel->sendFloat((ss + ".outerCutoff").c_str(), outer);
}

void SpotLight::setLightCount(int count)
{
	_gLightCount = count;
}

void SpotLight::notify(IOdata type, void* data)
{
	if (type == IOdata::CAMERA_MOVED)
	{
		float* ptr = (float*)data;

		_position.x = ptr[0];
		_position.y = ptr[1];
		_position.z = ptr[2];

		_direction.x = ptr[3];
		_direction.y = ptr[4];
		_direction.z = ptr[5];
	}
}
