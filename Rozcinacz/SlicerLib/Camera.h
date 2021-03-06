#pragma once
#include "SceneObject.h"

/// <summary>
/// Object throuh which scene will be displayed
/// </summary>
/// <seealso cref="SceneObject" />
class Camera :
	public SceneObject
{
	/// <summary>
	/// The perspective projection matrix
	/// </summary>
	glm::mat4 projectionMatrix;
	/// <summary>
	/// The view matrix
	/// </summary>
	glm::mat4 viewMatrix;
	/// <summary>
	/// The projection matrix multiplied by the view matrix
	/// </summary>
	glm::mat4 viewProjectionMatrix;
	/// <summary>
	/// The projection has changed
	/// </summary>
	bool projectionIsDirty;
	/// <summary>
	/// The view needs has changed
	/// </summary>
	bool viewIsDirty;
	/// <summary>
	/// Is the lookAt target locked
	/// </summary>
	bool lookAtLocked;
	/// <summary>
	/// Camera moved and lookAt needs to be rerun
	/// </summary>
	bool lookAtNeedsUpdate;
	/// <summary>
	/// The lookAt target
	/// </summary>
	glm::vec3 lookAtTarget;
	/// <summary>
	/// rerun lookAt.
	/// </summary>
	void refreshLookAt();
public:

	glm::vec3 getAABBMin() override { return glm::zero<glm::vec3>(); }
	glm::vec3 getAABBMax() override { return glm::zero<glm::vec3>(); }
	void ScreenPosToWorldRay(
	int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,  // Window size, in pixels
	glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
	);
	/// <summary>
	/// Gets the projection*view matrix.
	/// </summary>
	/// <returns></returns>
	glm::mat4& getViewProjectionMatrix();
	/// <summary>
	/// Moves this object by vector.
	/// </summary>
	/// <param name="vector">The vector.</param>
	void moveBy(const glm::vec3 & vector) override;
	/// <summary>
	/// Moves this object to location.
	/// </summary>
	/// <param name="vector">The vector.</param>
	void moveTo(glm::vec3 & vector) override;
	/// <summary>
	/// Sets the lookAt lock.
	/// </summary>
	/// <param name="locked">if set to <c>true</c> [locked].</param>
	void setLookAtLock(bool locked);
	/// <summary>
	/// Rotates camera towards.
	/// </summary>
	/// <param name="center">The center.</param>
	void lookAt(glm::vec3 & center);
	/// <summary>
	/// Renders with the specified shader program.
	/// </summary>
	/// <param name="shaderProgram">The shader program.</param>
	void render(unsigned shaderProgram) override;
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera"/> class.
	/// </summary>
	Camera();
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera"/> class.
	/// </summary>
	/// <param name="FoV">The field of view.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="nearPlane">The near plane.</param>
	/// <param name="farPlane">The far plane.</param>
	Camera(float FoV, float width, float height, float nearPlane, float farPlane);
	/// <summary>
	/// Creates new projection matrix.
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

