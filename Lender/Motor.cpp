#include "Motor.h"

/*
* create callbacks, create window, then init glew
*/
void Motor::configMotor()
{
	auto cam = new Camera(glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f));
	this->_scene = new Scene(cam);

	auto win = this->_scene->makeWindow(800, 800);

	this->_callbackControl = new CallbackController();
	this->_callbackControl->attach(this->_scene);
	this->_callbackControl->attach(this->_scene->getCameraPointer());

	glfwSetCursorPosCallback(win, [](GLFWwindow* win, double x, double y) -> void {
		Motor::getInstance().mouseCallback(win, x, y);
		;});

	glfwSetKeyCallback(win, [](GLFWwindow* win, int key, int scancode, int action, int mods) -> void {
		Motor::getInstance().keyboardCallback(win, key, scancode, action, mods);
		;});

	glfwSetMouseButtonCallback(win, [](GLFWwindow* win, int button, int action, int mods) -> void {
		Motor::getInstance().mouseKeyCallback(win, button, action, mods);
		; });

	glfwSetWindowSizeCallback(win, [](GLFWwindow* win, int w, int h) -> void {
		Motor::getInstance().windowResizeCallback(win, w, h);
		; });

	glfwSetScrollCallback(win, [](GLFWwindow* win, double x, double y) -> void {
		Motor::getInstance().scrollCallback(win, x, y);
		; });

	this->initGlew();
}

void Motor::run()
{
	if (!this->_gl_context_created) return;
	this->configMotor();
	this->_scene->mainLoop();
}

void Motor::initGLFW()
{
	// bind error callback
	auto lambda = [](int error_code, const char* description) {
		std::string message;
		message = "Error code: [" + std::to_string(error_code) + "] - " + description;
		std::cout << message << std::endl;
	};
	glfwSetErrorCallback(lambda);


	const char* versionString = glfwGetVersionString();
	std::cout << "GLFW Version: " << versionString << std::endl;

	if (!glfwInit())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	this->_gl_context_created = true;
	
	std::cout << "GLFW successfully initialised" << std::endl;

}
void Motor::setGlfwWindowHint(int what, int value)
{
	if (!this->_gl_context_created) return;
	glfwWindowHint(what, value);
}

void Motor::initGlew()
{
	glewExperimental = GL_TRUE;
	// glew returns 0 if successfull
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Glew not initialised properly" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Loaded GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
}

void Motor::setWindowSize(int x, int y)
{
	this->_windowSizeX = x;
	this->_windowSizeY = y;
}

// callbacks
void Motor::mouseCallback(GLFWwindow* win, double x, double y)
{
	double data[] = {x, y};
	this->_callbackControl->notifyAll(IOdata::MOUSE_POS, &data);
}

void Motor::mouseKeyCallback(GLFWwindow* win, int button, int action, int mods)
{
	int data[] = { button, action, mods };
	this->_callbackControl->notifyAll(IOdata::MOUSE_KEY, &data);
}

void Motor::keyboardCallback(GLFWwindow* win, int key, int action, int scancode, int mods)
{
	int data[] = {key, action, scancode, mods};
	this->_callbackControl->notifyAll(IOdata::KBD_PRESS, &data);
}

void Motor::windowResizeCallback(GLFWwindow* win, int w, int h)
{
	int width, height;
	glfwGetFramebufferSize(win, &width, &height);

	glViewport(0, 0, w, h);

	int data[] = { w, h};
	this->_callbackControl->notifyAll(IOdata::WINDOW_RESIZE, &data);
}

void Motor::scrollCallback(GLFWwindow* win, double x, double y)
{
	double data[] = { x, y};
	this->_callbackControl->notifyAll(IOdata::SCROLL, &data);
}

Motor::~Motor()
{
	delete this->_callbackControl;
	delete this->_scene;
}



