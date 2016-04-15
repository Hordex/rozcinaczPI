#pragma once
#include <GL/glew.h>
#include "Scene.h"
#include "Camera.h"

/// <summary>
/// Renderer
/// </summary>
class Renderer
{
	/// <summary>
	/// The program
	/// </summary>
	GLuint program;
	/// <summary>
	/// Renders the specified current matrix.
	/// </summary>
	/// <param name="currentMatrix">The current matrix.</param>
	/// <param name="object">The object.</param>
	void render(glm::mat4 currentMatrix, SceneObject& object);
public:
	/// <summary>
	/// Renders the specified scene.
	/// </summary>
	/// <param name="scene">The scene.</param>
	/// <param name="camera">The camera.</param>
	void render(Scene& scene, Camera& camera);
	/// <summary>
	/// Initializes a new instance of the <see cref="Renderer"/> class.
	/// </summary>
	Renderer();
	/// <summary>
	/// Finalizes an instance of the <see cref="Renderer"/> class.
	/// </summary>
	~Renderer();
};

