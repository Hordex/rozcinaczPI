#include "stdafx.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4& Camera::getViewProjectionMatrix()
{
	if (projectionNeedsUpdate || viewNeedsUpdate)
	{
		projectionNeedsUpdate = viewNeedsUpdate = false;
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
	return viewProjectionMatrix;
}

void Camera::moveBy(glm::vec3 & vector)
{
	SceneObject::moveBy(vector);
	viewNeedsUpdate = true;
}

void Camera::lookAt(glm::vec3 & center)
{
	viewNeedsUpdate = true;
	viewMatrix = glm::lookAt(position, center, glm::vec3(0, 1, 0));
}

void Camera::render(GLuint shaderProgram)
{
}

Camera::Camera(float fov, float width, float height, float nearPlane, float farPlane)
{
	projectionNeedsUpdate = viewNeedsUpdate = true;
	projectionMatrix = glm::perspectiveFov(glm::radians(fov), width, height, nearPlane, farPlane);
}


Camera::~Camera()
{
}
