#include "TransformationComposite.h"

glm::mat4 TransformationComposite::invoke()
{
	auto result = glm::mat4(1.0f);
	for (Component<glm::mat4>* element : this->components)
		result = result * element->invoke();
	return result;
}

glm::mat4 TransformationComposite::getTMatrix()
{
	return this->invoke();
}

Transformation::Transformation(glm::mat4 matrix) :
	Leaf<glm::mat4>(matrix)
{
	//ctor
}

glm::mat4 Transformation::invoke()
{
	return this->_value;
}
