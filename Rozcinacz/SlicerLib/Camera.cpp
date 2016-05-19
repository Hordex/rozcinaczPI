#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>

void Camera::refreshLookAt()
{
	viewIsDirty = true;
	viewMatrix = glm::lookAt(position, lookAtTarget, glm::vec3(0, 1, 0));
	lookAtNeedsUpdate = false;
}

void Camera::ScreenPosToWorldRay(int mouseX, int mouseY, int screenWidth, int screenHeight, glm::vec3& out_origin, glm::vec3& out_direction)
{
	// The ray Start and End positions, in Normalized Device Coordinates
	glm::vec4 lRayStart_NDC(
		((float)mouseX / (float)screenWidth - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)mouseY / (float)screenHeight - 0.5f) * -2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
		);
	glm::vec4 lRayEnd_NDC(
		((float)mouseX / (float)screenWidth - 0.5f) * 2.0f,
		((float)mouseY / (float)screenHeight - 0.5f) * -2.0f,
		0.0,
		1.0f
		);

	glm::mat4 M = glm::inverse(getViewProjectionMatrix());
	glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;

	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);


	out_origin = glm::vec3(lRayStart_world);
	out_direction = glm::normalize(lRayDir_world);
}

glm::mat4& Camera::getViewProjectionMatrix()
{
	if(lookAtNeedsUpdate && lookAtLocked)
	{
		refreshLookAt();
		lookAtNeedsUpdate = false;
	}
	if (projectionIsDirty || viewIsDirty)
	{
		projectionIsDirty = viewIsDirty = false;
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
	return viewProjectionMatrix;
}

void Camera::moveBy(const glm::vec3 & vector)
{
	SceneObject::moveBy(vector);
	viewIsDirty = true;
	lookAtNeedsUpdate = lookAtLocked;
}

void Camera::moveTo(glm::vec3& vector)
{
	position = vector;
	lookAtNeedsUpdate = lookAtLocked;
}

void Camera::setLookAtLock(bool state)
{
	lookAtLocked = state;
}

void Camera::lookAt(glm::vec3 & center)
{
	viewIsDirty = true;
	lookAtTarget = center;
	viewMatrix = glm::lookAt(position, center, glm::vec3(0, 1, 0));
}

void Camera::render(unsigned shaderProgram)
{
}

Camera::Camera(float fov, float width, float height, float nearPlane, float farPlane)
{
	viewIsDirty = true;
	perspective(fov, width, height, nearPlane, farPlane);
}

void Camera::perspective(float fov, float width, float height, float nearPlane, float farPlane)
{
	projectionIsDirty = true;
	projectionMatrix = glm::perspectiveFov(glm::radians(fov), width, height, nearPlane, farPlane);
}

Camera::Camera(){}

Camera::~Camera(){}
