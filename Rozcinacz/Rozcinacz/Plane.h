#pragma once
#include "SceneObject.h"
class Plane :
	public SceneObject
{
	glm::vec3 vertices[4];
	GLuint indices[6];
	GLuint BOs[2], VAO;
public:
	void render(GLuint shaderProgram) override;
	Plane();
	~Plane();
};

