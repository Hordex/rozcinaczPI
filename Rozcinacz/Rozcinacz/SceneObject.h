#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GL/glew.h>

/// <summary>
/// SceneObject
/// </summary>
class SceneObject
{
	/// <summary>
	/// The children
	/// </summary>
	std::vector<SceneObject*> children;
	/// <summary>
	/// The world matrix
	/// </summary>
	glm::mat4 worldMatrix;
	/// <summary>
	/// The world matrix needs update
	/// </summary>
	bool worldMatrixNeedsUpdate;
	/// <summary>
	/// Updates the world matrix.
	/// </summary>
	void updateWorldMatrix();
protected:
	/// <summary>
	/// The rotation
	/// </summary>
	glm::quat rotation;
	/// <summary>
	/// Gets the world matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4& getWorldMatrix();
public:
	/// <summary>
	/// The position
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// Moves the by.
	/// </summary>
	/// <param name="vector">The vector.</param>
	virtual void moveBy(const glm::vec3 & vector);
	/// <summary>
	/// Sets the rotation.
	/// </summary>
	/// <param name="rotaion">The rotaion.</param>
	void setRotation(const glm::vec3 & rotaion);
	/// <summary>
	/// Renders the specified shader program.
	/// </summary>
	/// <param name="shaderProgram">The shader program.</param>
	virtual void render(GLuint shaderProgram) = 0;
	/// <summary>
	/// Initializes a new instance of the <see cref="SceneObject"/> class.
	/// </summary>
	SceneObject();
	/// <summary>
	/// Finalizes an instance of the <see cref="SceneObject"/> class.
	/// </summary>
	virtual ~SceneObject();
};

