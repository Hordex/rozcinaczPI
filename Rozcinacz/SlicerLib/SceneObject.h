#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/// <summary>
/// Base class for objects displayed on scene
/// </summary>
class SceneObject
{
	/// <summary>
	/// Collection of objects placed in model space of this object
	/// </summary>
	std::vector<SceneObject*> children;
	/// <summary>
	/// The world matrix or model matrix
	/// </summary>
	glm::mat4 worldMatrix;
	/// <summary>
	/// The world matrix needs to be updated
	/// </summary>
	bool worldMatrixNeedsUpdate;
	/// <summary>
	/// Updates the world matrix
	/// </summary>
	void updateWorldMatrix();
protected:
	/// <summary>
	/// The rotation of object
	/// </summary>
	glm::quat rotation;
	/// <summary>
	/// Gets the world matrix
	/// </summary>
	/// <returns>  </returns>
	glm::mat4& getWorldMatrix();
public:
	/// <summary>
	/// The position of object
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// Moves the object by specified vector
	/// </summary>
	/// <param name="vector">The vector.</param>
	virtual void moveBy(const glm::vec3 & vector);
	/// <summary>
	/// Sets the rotation of object
	/// </summary>
	/// <param name="rotaion">The rotaion.</param>
	void setRotation(const glm::vec3 & rotaion);
	/// <summary>
	/// Renders object with the specified shader program.
	/// </summary>
	/// <param name="shaderProgram">The shader program.</param>
	virtual void render(unsigned shaderProgram) = 0;
	/// <summary>
	/// Initializes a new instance of the <see cref="SceneObject"/> class.
	/// </summary>
	SceneObject();
	/// <summary>
	/// Finalizes an instance of the <see cref="SceneObject"/> class.
	/// </summary>
	virtual ~SceneObject();
};

