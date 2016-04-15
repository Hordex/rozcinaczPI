#include "stdafx.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>

void Camera::refreshLookAt()
{
	viewNeedsUpdate = true;
	viewMatrix = glm::lookAt(position, lookAtTarget, glm::vec3(0, 1, 0));
	lookAtNeedsUpdate = false;
}

glm::mat4& Camera::getViewProjectionMatrix()
{
	if(lookAtNeedsUpdate && lookAtLocked)
	{
		refreshLookAt();
		lookAtNeedsUpdate = false;
	}
	if (projectionNeedsUpdate || viewNeedsUpdate)
	{
		projectionNeedsUpdate = viewNeedsUpdate = false;
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
	return viewProjectionMatrix;
}

void Camera::moveBy(const glm::vec3 & vector)
{
	SceneObject::moveBy(vector);
	viewNeedsUpdate = true;
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
	viewNeedsUpdate = true;
	lookAtTarget = center;
	viewMatrix = glm::lookAt(position, center, glm::vec3(0, 1, 0));
}

void Camera::render(GLuint shaderProgram)
{
}

Camera::Camera(float fov, float width, float height, float nearPlane, float farPlane)
{
	viewNeedsUpdate = true;
	perspective(fov, width, height, nearPlane, farPlane);
}

void Camera::perspective(float fov, float width, float height, float nearPlane, float farPlane)
{
	projectionNeedsUpdate = true;
	projectionMatrix = glm::perspectiveFov(glm::radians(fov), width, height, nearPlane, farPlane);
}

Camera::Camera()
{

}

Camera::~Camera()
{
}
