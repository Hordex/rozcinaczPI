#pragma once
#include <list>
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
	std::list<SceneObject*> children;
	/// <summary>
	/// The world matrix
	/// </summary>
	glm::mat4 worldMatrix;
	/// <summary>
	/// The model matrix
	/// </summary>
	glm::mat4 modelMatrix;
	/// <summary>
	/// The world matrix needs to be updated
	/// </summary>
	bool modelMatrixNeedsUpdate;
	SceneObject* parent;
	/// <summary>
	/// Updates the world matrix
	/// </summary>
	void updateModelMatrix();
	bool parentChanged;
protected:
	/// <summary>
	/// The rotation of object
	/// </summary>
	glm::quat rotation;
public:
	void ParentUpdate(SceneObject* parent);
	/// <summary>
	/// Gets the world matrix
	/// </summary>
	/// <returns>  </returns>
	glm::mat4& getWorldMatrix();
	glm::mat4& getModelMatrix();
	virtual glm::vec3 getAABBMin() = 0;
	virtual glm::vec3 getAABBMax() = 0;
	virtual void MouseEnter() {}
	virtual void MouseLeave() {}
	virtual bool MouseClick(int& from, int& to) { return false; }
	virtual bool TestRayOBBIntersection(
		glm::vec3 rayOrigin,
		glm::vec3 rayDirection,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
		float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
		);
	void InvalidateParent();
	void InvalidateWorldMatrix();
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
	void addChild(SceneObject* child);
	void removeChild(SceneObject* child);
};

