#pragma once
#include "SceneObject.h"
#include "Material.h"

/// <summary>
/// Geometric Plane object
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
	Material* material;
	/// <summary>
	/// The indices
	/// </summary>
	unsigned indices[6];
	/// <summary>
	/// The Buffer Objects
	/// </summary>
	unsigned BOs[2];
	/// <summary>
	/// The Vertex Array Object
	/// </summary>
	unsigned VAO;
	int index;
public:

	glm::vec3 getAABBMin() override;
	glm::vec3 getAABBMax() override;
	int Index() const;
	/// <summary>
	/// Renders with the specified shader program.
	/// </summary>
	/// <param name="shaderProgram">The shader program.</param>
	void render(unsigned shaderProgram) override;
	/// <summary>
	/// Initializes a new instance of the <see cref="Plane"/> class.
	/// </summary>
	Plane(int index);
	/// <summary>
	/// Finalizes an instance of the <see cref="Plane"/> class.
	/// </summary>
	~Plane();
};

