#include <glm/glm.hpp>
#include "Renderer.h"
#include "GLShader.h"
#include "Scene.h"
#include "Camera.h"
#include "Plane.h"


void Renderer::render(glm::mat4 currentMatrix, SceneObject& object)
{
	object.render(program);
}

void Renderer::render(Scene& scene, Camera& camera)
{
	glm::mat4 eye(1.0f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	GLint worldmatrixLocation = glGetUniformLocation(program, "viewProjectionMatrix");
	GLint cameraLocation = glGetUniformLocation(program, "cameraLocation");
	glUniformMatrix4fv(worldmatrixLocation, 1, GL_FALSE, &(camera.getViewProjectionMatrix()[0][0]));
	glUniform3fv(cameraLocation, 1, &camera.position[0]);

	for(auto child : scene.children)
	{
		render(eye, *child);
	}
}

Renderer::Renderer()
{
	//Initialize Glew
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	// load resources, initialize the OpenGL states, ...
	program = LoadShader("test.vert", "test.frag");
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}


Renderer::~Renderer()
{
}
