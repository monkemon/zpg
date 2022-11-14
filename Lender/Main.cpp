#include <iostream>
#include "Motor.h"

int main(int argc, char** args)
{
	Motor& motor = Motor::getInstance();

	motor.initGLFW();

	motor.setWindowSize(800, 600);

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	motor.setGlfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	motor.setGlfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	motor.setGlfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	motor.setGlfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	motor.run();
}