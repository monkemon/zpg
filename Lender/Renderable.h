#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <vector>
#include <iostream>

#include "TransformationComposite.h"
#include "Camera.h"
#include "LightModel.h"

class Renderable
{
protected:
	GLuint _vbo = 0;
	GLuint _vao = 0;

	float _xPos = 0;
	float _yPos = 0;
	const float* _modelVertices = nullptr;

	int _vertexCount = 0;
	int _vertexSize = 0;
	int _attribs = 0;

	TransformationComposite* _transformation = nullptr;

	glm::vec3 _modelColor;
	glm::mat4 _tMatrix;

	LightModel* _lightModel;
public:
	Renderable(LightModel* loader, glm::vec3 color = glm::vec3(0.5,0.5,0.5f)) :
		_lightModel(loader),
		_modelColor(color)
	{
		this->_transformation = new TransformationComposite();
		this->_tMatrix = this->_transformation->getTMatrix();
	}

	~Renderable()
	{
		delete this->_transformation;
	}

	void draw(glm::mat4 cam,int render_mode)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

		this->_lightModel->useMe();

		auto modelMatrix = this->_lightModel->registerVariable("modelMatrix");
		auto normalMatrix = this->_lightModel->registerVariable("normalMatrix");
		auto modelColorID = this->_lightModel->registerVariable("modelColor");

		glm::mat4 normal = glm::inverse(this->_tMatrix);

		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &this->_tMatrix[0][0]);
		glUniformMatrix4fv(normalMatrix, 1, GL_TRUE, &normal[0][0]);
		glUniform3fv(modelColorID, 1, &this->_modelColor[0]);


		glBindVertexArray(this->_vao);

		for (int i = 0; i < this->_attribs; i++)
		{
			int rowsize = this->_vertexSize * this->_attribs;
			auto offset = static_cast<unsigned long long>(i) * this->_vertexSize * sizeof(float);
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, this->_vertexSize, GL_FLOAT, GL_FALSE, rowsize * sizeof(float), (GLvoid*)(offset));
		}

		int rendervertices = (int)this->_vertexCount / (this->_vertexSize * this->_attribs);

		glDrawArrays(render_mode, 0, rendervertices);
	}

	void applyTransformation()
	{
		this->_tMatrix *= this->_transformation->getTMatrix();
	}

	/*
	* Loads the model and allocates all necessary stuff on GPU
	*/
	virtual void loadModel(const float* vertices, int count, int vertex_size, int attribs)
	{
		this->_vertexCount = count;
		this->_vertexSize = vertex_size;
		this->_attribs = attribs;
		this->_modelVertices = vertices;


		auto buffsize = count * sizeof(float);
	
		glGenBuffers(1, &this->_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
		glBufferData(GL_ARRAY_BUFFER, buffsize, vertices, GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, buffsize, this->_modelVertices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &this->_vao);
		glBindVertexArray(this->_vao);
	}

	void addScale(glm::vec3 scalefactor)
	{
		auto M = glm::mat4(1.0f);
		M = glm::scale(M, scalefactor);
		this->_transformation->addItem(new Transformation(M));
	}
	void addRotate(glm::vec3 axis, float angle)
	{
		auto M = glm::mat4(1.0f);
		M = glm::rotate(M, angle, axis);
		this->_transformation->addItem(new Transformation(M));
	}
	void addTranslate(glm::vec3 myView)
	{
		auto M = glm::mat4(1.0f);
		M = glm::translate(M, myView);
		this->_transformation->addItem(new Transformation(M));
	}
	void doScale(glm::vec3 scalefactor)
	{
		 this->_tMatrix = glm::scale(this->_tMatrix, scalefactor);
	}
	void doRotate(glm::vec3 axis, float angle)
	{
		this->_tMatrix = glm::rotate(this->_tMatrix, angle, axis);
	}
	void doTranslate(glm::vec3 myView)
	{
		this->_tMatrix = glm::translate(this->_tMatrix, myView);
	}
};

