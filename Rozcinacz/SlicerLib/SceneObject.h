#pragma once
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/// <summary>
/// Base class for objects displayed on scene
/// </summary>
class SceneObject
{
	glm::mat4 miscMatrix;
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
	bool parentChanged;
	bool modelMatrixNeedsUpdate;
	/// <summary>
	/// Updates the world matrix
	/// </summary>
	void updateModelMatrix();
protected:
	SceneObject* parent;
	/// <summary>
	/// Collection of objects placed in model space of this object
	/// </summary>
	std::list<SceneObject*> children;
	void RemoveAllChildren();
	virtual glm::mat4 CreateModelMatrix() const;
	/// <summary>
	/// The position of object
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// The rotation of object
	/// </summary>
	glm::quat rotation;
public:
	virtual bool FrameUpdate(float dt);
	void ParentUpdate(SceneObject* parent);
	void UpdateParentSpace();
	/// <summary>
	/// Gets the world matrix
	/// </summary>
	/// <returns>  </returns>
	const glm::mat4& getWorldMatrix();
	const glm::mat4& getModelMatrix();
	const glm::vec3& getPosition() const;

	const glm::quat& getRotation() const
	{
		return rotation;
	}

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
	void InvalidateModelMatrix();
	/// <summary>
	/// Moves this object to location.
	/// </summary>
	/// <param name="vector">The vector.</param>
	virtual void moveTo(glm::vec3 & vector);
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
	void setRotation(const glm::quat & rotaion);
	void ApplySpace(const glm::mat4& matrix);
	/// <summary>
	/// Sets the rotation of object
	/// </summary>
	/// <param name="rotaion">The rotaion.</param>
	void rotateBy(const glm::vec3 & rotaion);
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
	void Mimic(glm::vec3 v1, glm::vec3 v2);
};

