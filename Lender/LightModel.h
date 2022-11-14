#pragma once
#include "ShaderLoader.h"
#include "Observer.h"

#include <glm/mat4x4.hpp>

class LightModel : public ShaderLoader, public Observer
{
public:
	void useMe()
	{
		glUseProgram(this->shaderProgramID);
	}

	GLint registerVariable(const char* name)
	{
		return glGetUniformLocation(this->shaderProgramID, name);
	}

	GLint sendInt(const char* name, int data)
	{
		auto id = glGetUniformLocation(shaderProgramID,name);
		if (id < 0)
		{
			std::cout << "Could not load " << name << std::endl;
			return id;
		}
		glUniform1i(id, data);
		return id;
	}

	GLint sendFloat(const char* name, float data)
	{
		auto id = glGetUniformLocation(shaderProgramID,name);
		if (id < 0)
		{
			std::cout << "Could not load " << name << std::endl;
			return id;
		}
		glUniform1f(id, data);
		return id;
	}

	GLint sendVec3(const char* name, glm::vec3 data)
	{
		auto id = glGetUniformLocation(shaderProgramID,name);
		if (id < 0)
		{
			std::cout << "Could not load " << name << std::endl;
			return id;
		}
		glUniform3fv(id, 1, &data[0]);
		return id;
	}

	GLint sendVec4(const char* name, glm::vec4 data)
	{
		auto id = glGetUniformLocation(shaderProgramID,name);
		if (id < 0)
		{
			std::cout << "Could not load " << name << std::endl;
			return id;
		}
		glUniform4fv(id, 1, &data[0]);
		return id;
	}

	void notify(IOdata type, void* data)
	{
		if (type == IOdata::CAMERA_MOVED)
		{
			this->useMe();
			float* pos = (float*)data;

			GLint cameraLocation = this->registerVariable("camera");

			//std::cout << "camera moving to: " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;

			glm::vec3 inCameraPos(pos[0], pos[1], pos[2]);

			glUniform3fv(cameraLocation, 1, &inCameraPos[0]);
		}

		if (type == IOdata::CAMERA_DATA)
		{
			this->useMe();
			glm::mat4* ptr = (glm::mat4*)data;

			GLint viewMatID = this->registerVariable("viewMatrix");
			GLint projectionMatID = this->registerVariable("projectionMatrix");

			glUniformMatrix4fv(viewMatID, 1, GL_FALSE, &ptr[0][0][0]);
			glUniformMatrix4fv(projectionMatID, 1, GL_FALSE, &ptr[1][0][0]);
			
		}
	}
};

