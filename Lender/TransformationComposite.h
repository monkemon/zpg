#pragma once

#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Composite.h"

class TransformationComposite :
	public Composite<glm::mat4>
{
public:
	glm::mat4 invoke();
	glm::mat4 getTMatrix();
};

class Transformation :
	public Leaf<glm::mat4>
{
public:
	Transformation(glm::mat4 matrix);
	glm::mat4 invoke();
};

