#include <glm/glm.hpp>
#include "Renderer.h"
#include "GLShader.h"
#include "Scene.h"
#include "Camera.h"
#include "Plane.h"


void Renderer::render(Scene& scene, Camera& camera) const
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
		child->render(program);
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
	glPolygonOffset(0.f,0.5f);
}


Renderer::~Renderer()
{
}
