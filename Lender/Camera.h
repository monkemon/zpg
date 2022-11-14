#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Observer.h"

class Camera : public Observer, public Subject
{
private:
	glm::vec3 _up;
	glm::vec3 _eye;
	glm::vec3 _target;

	glm::vec3 _direction;

	glm::mat4 _projection;



	float _lastX = 0.0f;
	float _lastY = 0.0f;

	float _pitch = 0.0f;
	float _yaw = 0.0f;

	float _sensitivity = 0.02f;
	float _speed = 0.01f;

	bool _is_moving = 0;

	int _just_pressed = 0;
	int _mouse_pressed = 0;

	int _dforward = 0;
	int _dside = 0;
	int _dup = 0;

public:
	Camera(glm::mat4 proj):
		_projection(proj)
	{
		this->_up = glm::vec3(0,1,0.0f);
		this->_eye = glm::vec3(0, 1, 5.0f);
		this->_target = glm::vec3(0,0,-1.0f);
		this->_direction = glm::vec3(0, 0, 0.0f);

		this->_just_pressed = 1;  // important for first click, hard set here
	}

	glm::vec3 position()
	{
		return this->_eye;
	}

	void notify(IOdata type, void* data)
	{
		switch (type)
		{
		case IOdata::MOUSE_POS:
			this->handleMouse(data);
			break;
		case IOdata::MOUSE_KEY:
			this->handleMousePress(data);
			break;
		case IOdata::KBD_PRESS:
			this->handleKbd(data);
			break;
		case IOdata::WINDOW_RESIZE:
			this->handleWindowResize(data);
			break;
		case IOdata::SCROLL:
			this->handleScroll(data);
			break;
		default:
			break;
		}
	}

	void move()
	{
		auto leftVector = glm::normalize(glm::cross(this->_target, this->_up));

		this->_direction =
			(float)this->_dforward * this->_target +
			(float)this->_dside  * -leftVector +
			(float)this->_dup * this->_up;

		this->_eye += this->_direction * this->_speed;
	}

	glm::mat4 getMatrix()
	{
		return glm::lookAt(this->_eye, this->_eye + this->_target, this->_up);
	}

	void sendViewProjectionToShaders()
	{
		glm::mat4 modelMatrix = this->getMatrix();
		glm::mat4 projectionMatrix = this->_projection;
		glm::mat4 data[] = { modelMatrix, projectionMatrix };
		for (auto& x : this->observers)
			x->notify(IOdata::CAMERA_DATA, data);
	}

	void handleScroll(void* data)
	{
		double* ptr = (double*)data;
		this->_speed += 0.01f * (float)ptr[1];
	}

	void handleWindowResize(void* data)
	{
		std::cout << "window resize" << std::endl;
		int* ptr = (int*)data;
		int x = ptr[0];
		int y = ptr[1];

		float ratio = x / (float)y;
		auto radians = glm::radians(45.0f);

		this->_projection = glm::perspective(radians, ratio, 0.1f, 100.0f);
	}

	void handleMousePress(void* data)
	{
		int* ptr = (int*)data;
		int button = ptr[0];
		int action = ptr[1];
		int mods = ptr[2];

		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (action == GLFW_PRESS)
			{
				this->_mouse_pressed = 1;
				this->_just_pressed = 1;
			}

			else if (action == GLFW_RELEASE)
			{
				this->_mouse_pressed = 0;
			}
		}

	}
		
	void handleMouse(void* data)
	{
		if (this->_mouse_pressed == 0) return;
	
		double* ptr = (double*)data;
		float x = (float)ptr[0];
		float y = (float)ptr[1];

		if (this->_just_pressed)
		{
			this->_lastX = x;
			this->_lastY = y;

			this->_just_pressed = 0;

			return;
		}


		float deltaX = x - this->_lastX;
		float deltaY = this->_lastY - y; // y is 0 at top, max at bottom

		this->_lastY = y;
		this->_lastX = x;

		deltaX *= this->_sensitivity;
		deltaY *= this->_sensitivity;

		this->_yaw += deltaX;
		this->_pitch -= deltaY;

		// prevent gimbal lock
		if (this->_pitch < 0.001f) this->_pitch = 0.001f;
		if (this->_pitch > 3.13f) this->_pitch = 3.13f;

		this->_target.x = sin(this->_pitch) * cos(this->_yaw);
		this->_target.z = sin(this->_pitch) * sin(this->_yaw);
		this->_target.y = cos(this->_pitch);

		this->_target = glm::normalize(this->_target);
		notifyAll();
	}

	void handleKbd(void* data)
	{
		int* ptr = (int*)data;
		int key = ptr[0];
		int scancode = ptr[1];
		int action = ptr[2];
		int mods = ptr[3];

		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_A:
				this->_dside = 1;
				break;
			case GLFW_KEY_D:
				this->_dside = -1;
				break;
			case GLFW_KEY_W:
				this->_dforward = 1;
				break;
			case GLFW_KEY_S:
				this->_dforward = -1;
				break;
			case GLFW_KEY_LEFT_CONTROL:
				this->_dup = -1;
				break;
			case GLFW_KEY_LEFT_SHIFT:
				this->_dup = 1;
			default:
				break;
			}
		}
		if (action == GLFW_RELEASE)
		{
			switch (key)
			{
			case GLFW_KEY_A:
				if (this->_dside > 0)
					this->_dside--;
				break;
			case GLFW_KEY_D:
				if (this->_dside < 0)
					this->_dside++;
				break;
			case GLFW_KEY_W:
				if (this->_dforward > 0)
					this->_dforward--;
				break;
			case GLFW_KEY_S:
				if (this->_dforward < 0)
					this->_dforward++;
				break;
			case GLFW_KEY_LEFT_SHIFT:
				if (this->_dup > 0)
					this->_dup--;
				break;
			case GLFW_KEY_LEFT_CONTROL:
				if (this->_dup < 0)
					this->_dup++;
				break;
			default:
				break;
			}
		}
	
		move();

		// notify all observers about position change
		// light, shaders..
		this->notifyAll();
	}

	void notifyAll()
	{
		auto pos = _eye;
		auto dir = _target;
		float posndir[] = { pos.x, pos.y, pos.z, dir.x, dir.y, dir.z };
		for (auto& obs : observers)
		{
			obs->notify(IOdata::CAMERA_MOVED, &posndir);
		}
	}
};

