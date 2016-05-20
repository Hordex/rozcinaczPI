#pragma once
#include <GL/glew.h>
#include <glm/fwd.hpp>
class SceneObject;
class Camera;
class Scene;
/// <summary>
/// Class responsible for rendering scene
/// </summary>
class Renderer
{
	/// <summary>
	/// The shader program
	/// </summary>
	GLuint program;
public:
	/// <summary>
	/// Renders the specified scene.
	/// </summary>
	/// <param name="scene">The scene.</param>
	/// <param name="camera">The camera.</param>
	void render(Scene& scene, Camera& camera) const;
	/// <summary>
	/// Initializes a new instance of the <see cref="Renderer"/> class.
	/// </summary>
	Renderer();
	/// <summary>
	/// Finalizes an instance of the <see cref="Renderer"/> class.
	/// </summary>
	~Renderer();
};

