#pragma once
#include "SceneObject.h"

/// <summary>
/// Plane
/// </summary>
/// <seealso cref="SceneObject" />
class Plane :
	public SceneObject
{
	/// <summary>
	/// The vertices
	/// </summary>
	glm::vec3 vertices[4];
	/// <summary>
	/// The normals
	/// </summary>
	glm::vec3 normal;
	/// <summary>
	/// The indices
	/// </summary>
	GLuint indices[6];
	/// <summary>
	/// The Buffer Objects
	/// </summary>
	GLuint BOs[2];
	/// <summary>
	/// The Vertex Array Object
	/// </summary>
	GLuint VAO;
public:
	/// <summary>
	/// Renders the specified shader program.
	/// </summary>
	/// <param name="shaderProgram">The shader program.</param>
	void render(GLuint shaderProgram) override;
	/// <summary>
	/// Initializes a new instance of the <see cref="Plane"/> class.
	/// </summary>
	Plane();
	/// <summary>
	/// Finalizes an instance of the <see cref="Plane"/> class.
	/// </summary>
	~Plane();
};

