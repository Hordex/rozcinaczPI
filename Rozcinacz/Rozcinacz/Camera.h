#pragma once
#include "SceneObject.h"

/// <summary>
/// Camera
/// </summary>
/// <seealso cref="SceneObject" />
class Camera :
	public SceneObject
{
	/// <summary>
	/// The projection matrix
	/// </summary>
	glm::mat4 projectionMatrix;
	/// <summary>
	/// The view matrix
	/// </summary>
	glm::mat4 viewMatrix;
	/// <summary>
	/// The view projection matrix
	/// </summary>
	glm::mat4 viewProjectionMatrix;
	/// <summary>
	/// The projection needs update
	/// </summary>
	bool projectionNeedsUpdate;
	/// <summary>
	/// The view needs update
	/// </summary>
	bool viewNeedsUpdate;
	/// <summary>
	/// The look at locked
	/// </summary>
	bool lookAtLocked;
	/// <summary>
	/// The look at needs update
	/// </summary>
	bool lookAtNeedsUpdate;
	/// <summary>
	/// The look at target
	/// </summary>
	glm::vec3 lookAtTarget;
	/// <summary>
	/// Refreshes the look at.
	/// </summary>
	void refreshLookAt();
public:
	/// <summary>
	/// Gets the view projection matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4& getViewProjectionMatrix();
	/// <summary>
	/// Moves the by.
	/// </summary>
	/// <param name="vector">The vector.</param>
	void moveBy(const glm::vec3 & vector) override;
	/// <summary>
	/// Moves to.
	/// </summary>
	/// <param name="vector">The vector.</param>
	void moveTo(glm::vec3 & vector);
	/// <summary>
	/// Sets the look at lock.
	/// </summary>
	/// <param name="state">if set to <c>true</c> [state].</param>
	void setLookAtLock(bool state);
	/// <summary>
	/// Looks at.
	/// </summary>
	/// <param name="center">The center.</param>
	void lookAt(glm::vec3 & center);
	/// <summary>
	/// Renders the specified shader program.
	/// </summary>
	/// <param name="shaderProgram">The shader program.</param>
	void render(GLuint shaderProgram) override;
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera"/> class.
	/// </summary>
	Camera();
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera"/> class.
	/// </summary>
	/// <param name="FoV">The fo v.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="nearPlane">The near plane.</param>
	/// <param name="farPlane">The far plane.</param>
	Camera(float FoV, float width, float height, float nearPlane, float farPlane);
	/// <summary>
	/// Perspectives the specified fo v.
	/// </summary>
	/// <param name="FoV">The fo v.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="nearPlane">The near plane.</param>
	/// <param name="farPlane">The far plane.</param>
	void perspective(float FoV, float width, float height, float nearPlane, float farPlane);
	/// <summary>
	/// Finalizes an instance of the <see cref="Camera"/> class.
	/// </summary>
	~Camera();
};

