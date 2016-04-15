#pragma once
#include <GL/glew.h>
#include "Scene.h"
#include "Camera.h"

class Renderer
{
	GLuint program;
	void render(glm::mat4 currentMatrix, SceneObject& object);
public:
	void render(Scene& scene, Camera& camera);
	Renderer();
	~Renderer();
};

