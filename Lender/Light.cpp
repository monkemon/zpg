#include "Light.h"

Light::Light(glm::vec4 pos, glm::vec4 diff, glm::vec4 dir)
	: _position(pos), _diffuse(diff), _direction(dir)
{
}