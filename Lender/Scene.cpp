#include "Scene.h"

static int modes[] =
{
	GL_POINTS,
	GL_LINES,
	GL_LINE_LOOP,
	GL_LINE_STRIP,
	GL_LINE_STRIP_ADJACENCY,
	GL_LINES_ADJACENCY,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP_ADJACENCY,
	GL_TRIANGLES_ADJACENCY,
	GL_PATCHES
};

Scene::Scene() :
	_lm(nullptr),
	_cam(nullptr)
{

}

Scene::Scene(Camera* cam) :
	_lm(nullptr),
	_cam(cam)
{

}

Camera* Scene::getCameraPointer()
{
	return this->_cam;
}

GLFWwindow* Scene::makeWindow(int x, int y)
{
	this->_window = glfwCreateWindow(
		x,
		y,
		"Lender gaming engine pro",
		NULL,
		NULL
	);

	if (!this->_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->_window);
	glfwSwapInterval(1);

	int width, height;
	glfwGetFramebufferSize(this->_window, &width, &height);

	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	return this->_window;
}

void Scene::configScene()
{

	this->index = 8; // GL_TRIANGLES as first mode 

	//ShaderLoader* sl = new ShaderLoader();
	LightModel* phong = new LightModel();
	LightModel* blinn = new LightModel();
	LightModel* lambert = new LightModel();
	LightModel* constant = new LightModel();
	LightModel* lights_phong = new LightModel();

	LightModel* lightmodel_ptr[] = { constant, lambert, phong, blinn };

	constant->loadShader("basic_vertex.glsl", "basic_fragment.glsl");
	lambert->loadShader("lambert_vertex.glsl", "lambert_fragment.glsl");
	phong->loadShader("phong_vertex.glsl", "phong_fragment.glsl");
	blinn->loadShader("blinn_vertex.glsl", "blinn_fragment.glsl");
	lights_phong->loadShader("multiple_light_phong_V.glsl", "multiple_light_phong_F.glsl");

	this->_cam->attach(phong);
	this->_cam->attach(blinn);
	this->_cam->attach(lambert);
	this->_cam->attach(constant);
	this->_cam->attach(lights_phong);

	srand(time(0));

	Renderable* balls[20];
	for (int i = 0; i < 20; i++)
	{
		balls[i] = new ModelSphere(lights_phong, glm::vec3(
			(float)(rand() % 10 / (float)10),
			(float)(rand() % 10 / (float)10),
			(float)(rand() % 10 / (float)10)
		));

		balls[i]->doTranslate(glm::vec3(
			rand() % 30 - 15,
			-2,
			/*rand() % 5,*/
			rand() % 30 - 15
		));
		balls[i]->doScale(glm::vec3((float)(rand() % 2)));
		this->addObject(balls[i]);
	}

	/*
	

	

	auto suziBeautiful = new ModelSuzi(blinn, false, glm::vec3(0, 0.7, 0.8f));
	suziBeautiful->doTranslate(glm::vec3(1, 3, -1.0f));
	suziBeautiful->addRotate(glm::vec3(0, 1, 0.0f), 0.01f);
	suziBeautiful->doScale(glm::vec3(0.6f));

	auto suzi = new ModelSuzi(lambert, false, glm::vec3(0,0.7,0.8f));
	suzi->doTranslate(glm::vec3(-1, 2, -1.0f));
	suzi->addRotate(glm::vec3(0, 1, 0.0f), 0.01f);
	suzi->doScale(glm::vec3(0.6f));

	//this->addObject(suziBeautiful);
	//this->addObject(suzi);


	auto gift = new ModelGift(lambert, glm::vec3(1, 0, 1));
	gift->doScale(glm::vec3(2.0f));
	gift->doTranslate(glm::vec3(0, -2, -1));
	this->addObject(gift);

	*/
	for (int i = 0; i < 40; i++)
	{
		auto tree = new ModelTree(lights_phong, glm::vec3(
			(float)(rand() % 10 / (float)10),
			(float)(rand() % 10 / (float)10),
			(float)(rand() % 10 / (float)10)
		));

		tree->doTranslate(glm::vec3(
			rand() % 50 - 25,
			-2,
			rand() % 50 - 25
		));
		tree->doRotate(glm::vec3(
			0,
			1,
			0.0f
		),
			(float)(rand() % 100) / (float) 100 * 3.14f
			);
		tree->doScale(glm::vec3(
			(float)(rand() % 100) / (float)100 * 1.5 + 0.01f
		));
		this->addObject(tree);
	}
	/*

	auto tree = new ModelTree(constant, glm::vec3(0.5, 0.5, 0));
	tree->doTranslate(glm::vec3(0, -2, -6));
	this->addObject(tree);

	
	for (int i = 0; i < 40; i++)
	{
		auto bush = new ModelBushes(blinn, glm::vec3(
			1.0,
			0.5,
			(float)(rand() % 10 / (float)10)
		));

		bush->doTranslate(glm::vec3(
			rand() % 40 - 20,
			-2,
			rand() % 40 - 20
		));
		bush->doRotate(glm::vec3(
			0,
			1,
			0.0f
		),
			(float)(rand() % 100) / (float) 100 * 3.14
			);
		bush->doScale(glm::vec3(
			(float)(rand() % 100) / (float) 100 * 1.5 
		));
		//this->addObject(bush);
	}

	*/
	auto bush = new ModelBushes(blinn, glm::vec3(0, 0.4, 0.8));
	bush->doTranslate(glm::vec3(3, -2, 0));
	bush->doScale(glm::vec3(1.4f));
	bush->addRotate(glm::vec3(0, 1.0f, 0), 0.004f);
	this->addObject(bush);

	glm::vec3 suzicolor = glm::vec3(1.0, 0.7, 0.7f);
	auto suzi_constant = new ModelSuzi(constant, false, suzicolor);
	suzi_constant->doTranslate(glm::vec3(-2, 0, -2.0f));
	suzi_constant->doScale(glm::vec3(0.5f));

	auto suzi_lambert = new ModelSuzi(lambert, false, suzicolor);
	suzi_lambert->doTranslate(glm::vec3(-1, 0, -2.0f));
	suzi_lambert->doScale(glm::vec3(0.5f));

	auto suzi_phong = new ModelSuzi(phong, false, suzicolor);
	suzi_phong->doTranslate(glm::vec3(0, 0, -2.0f));
	suzi_phong->doScale(glm::vec3(0.5f));

	auto suzi_blinn = new ModelSuzi(blinn, false, suzicolor);
	suzi_blinn->doTranslate(glm::vec3(1, 0, -2.0f));
	suzi_blinn->doScale(glm::vec3(0.5f));

	auto plane = new ModelPlain(lights_phong, glm::vec3(0.1, 0.5f, 0));
	plane->doTranslate(glm::vec3(0.0, -2, 0.0f));
	plane->doScale(glm::vec3(30.0f, 1.0, 30.0));
	this->addObject(plane);

	ModelSphere* spheres[4];
	glm::vec3 colors[4] =
	{
		glm::vec3(1.0f, 0, 0),
		glm::vec3(0, 1.0f, 0),
		glm::vec3(0, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 0)
	};
	for (int i = 0; i < 4; i++)
	{
		spheres[i] = new ModelSphere(lights_phong, colors[i]);
		spheres[i]->doScale(glm::vec3(0.5f));
		spheres[i]->addRotate(glm::vec3(1, 0, 0.0f), 0.02f);
		this->addObject(spheres[i]);
	}

	spheres[0]->doTranslate(glm::vec3(-2, 0, 0));
	spheres[1]->doTranslate(glm::vec3(2, 0, 0));
	spheres[2]->doTranslate(glm::vec3(0, -2, 0));
	spheres[3]->doTranslate(glm::vec3(0, 2, 0));

	//mozes pouzivat vec4 a,     a.xyz / a.w

	suzi_phong->addRotate(glm::vec3(1, 0, 0), 0.001f);

	//this->addObject(suzi_constant);
	//this->addObject(suzi_lambert);
	//this->addObject(suzi_phong);
	//this->addObject(suzi_blinn);

	auto flatsusan = new ModelSuzi(lights_phong, true, glm::vec3(0.4f, 0.0f, 0.4f));
	flatsusan->doScale(glm::vec3(1.8f));
	flatsusan->doTranslate(glm::vec3(8.0f, 0, 6.0f));
	flatsusan->addRotate(glm::vec3(0, 1, 0.0f), 0.01f);

	auto roundsusan = new ModelSuzi(lights_phong, false, glm::vec3(0.4f, 0.0f, 0.4f));
	roundsusan->doScale(glm::vec3(1.8f));
	roundsusan->doTranslate(glm::vec3(5.0f, 0, 6.0f));
	roundsusan->addRotate(glm::vec3(0, 1, 0.0f), -0.01f);

	this->addObject(flatsusan);
	this->addObject(roundsusan);


	auto lightbulb = new ModelSphere(lights_phong, glm::vec3(1.0f, 1, 1));
	lightbulb->doTranslate(glm::vec3(-8, 13, -4.0f));
	lightbulb->doScale(glm::vec3(0.3f));
	this->addObject(lightbulb);
	
	PointLight* p1 = new PointLight(lights_phong, 10, 1, 0, 0, 1);
	PointLight* p2 = new PointLight(lights_phong, -8, 15, -4, 1, 2);
	PointLight* p3 = new PointLight(lights_phong, -3, 0, 13, 2, 4);
	PointLight* p4 = new PointLight(lights_phong, 5, 2, -9, 3, 4);

	p1->setADS({ 0.0, 0.3f, 1.0 });
	p1->setAttenuation(1, 0.3f, 0.05f);
	//p2->setADS({ 0.0, 1.0, 0.3 });

	addObject(p1);
	//this->addObject(p2);
	//this->addObject(p3);
	//this->addObject(p4);

	DirectionalLight* dl = new DirectionalLight(lights_phong, glm::vec3(1, -1.0f, 0.0f), 0, 2);
	dl->setADS({0.1, 0.5, 0.5});
	this->addObject(dl);

	SpotLight* sp = new SpotLight(lights_phong,
		{ 0.0f, 1.0f, 0.0f },
		{ 1.0f, 0.1f, 0.01f },
		{ 0.0f, 0.0f, 1.0f },
		15.0f,
		25.0f,
		0,
		1);
	sp->setADS({ 0.0f, 1.0f, 1.0f });
	this->_cam->attach(sp);
	addObject(sp);

	glEnable(GL_DEPTH_TEST);
}

void Scene::mainLoop()
{
	this->configScene();

	this->_cam->notifyAll(); //always update position to shaders(?)

	while(!glfwWindowShouldClose(this->_window))
	{
		/*
		float spot_direction[] = { -1.0 , -1.0 , 0.0 }; // smer
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
		const GLfloat angle = 30.0;
		glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &angle);
		*/


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->_cam->move();
		this->_cam->sendViewProjectionToShaders();


		for (auto& obj : this->_objectList)
		{
			obj->draw();
		}
		for (auto& object : this->_renderList)
		{

			object->applyTransformation();
			object->draw(this->_cam->getMatrix(), modes[this->index]);
		}



		glfwPollEvents();
		glfwSwapBuffers(this->_window);

	}

	delete this->_lm;
}

void Scene::addObject(Renderable* r)
{
	this->_renderList.push_back(r);
}

void Scene::addObject(GeneralObject* o)
{
	this->_objectList.push_back(o);
}

void Scene::addLight(Light* l)
{

}

void Scene::notify(IOdata type, void* data)
{
	int* ptr = (int*)data;
	double* ptr_f = (double*)data;
	int key = ptr[0];
	int action = ptr[2];

	switch (type)
	{
	case IOdata::KBD_PRESS:
		if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS)
		{
			this->index++;
			std::cout << "Now using draw mode #" << this->index << std::endl;
		}
		if (index > 11) index = 0;
		break;

	default:
		break;
	}
}

Scene::~Scene()
{
	for (auto& x : this->_renderList)
		delete x;
}
