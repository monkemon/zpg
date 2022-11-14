#pragma once

// GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// C/C++ stuff
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

// My classes
#include "CallbackController.h"
#include "Scene.h"

class Motor
{
private:
	int _windowSizeX;
	int _windowSizeY;

	bool _gl_context_created;

	Scene* _scene;
	CallbackController* _callbackControl;

public:
	//static Motor& getInstance();
	static Motor& getInstance()
	{
		static Motor m;
		return m;
	}

	void configMotor();
	void run();
	void initGLFW();
	void setGlfwWindowHint(int what, int value);
	void initGlew();
	void setWindowSize(int x, int y);
	// callbacks
	void mouseCallback(GLFWwindow* win, double x, double y);
	void mouseKeyCallback(GLFWwindow* win, int button, int action, int mods);
	void keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	void windowResizeCallback(GLFWwindow* win, int w, int h);
	void scrollCallback(GLFWwindow* win, double x, double y);

	~Motor();
};
