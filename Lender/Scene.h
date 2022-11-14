#pragma once
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Observer.h"
#include "Renderable.h"
#include "ModelSuzi.h"
#include "ModelSphere.h"
#include "ModelGift.h"
#include "ModelTree.h"
#include "ModelBushes.h"
#include "ModelPlain.h"
#include "Camera.h"
#include "LightModel.h"
#include "Light.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Scene : public Observer
{
private:
	GLFWwindow* _window = nullptr;

	Camera* _cam = nullptr;
	
	std::vector<Renderable*> _renderList;
	std::vector<Light*> _lightList;
	std::vector<GeneralObject*> _objectList;

	LightModel* _lm;

	int index = 0;
	int _lightCount = 0;
public:
	Scene();
	Scene(Camera* cam);
	~Scene();

	GLFWwindow* makeWindow(int x, int y);
	void mainLoop();
	void notify(IOdata type, void* data);
	Camera* getCameraPointer();
	void configScene();

	void addObject(Renderable* r);
	void addObject(GeneralObject* o);
	void addLight(Light* l);
};

