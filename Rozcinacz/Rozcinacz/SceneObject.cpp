#include "stdafx.h"
#include "SceneObject.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>


void SceneObject::updateWorldMatrix()
{
	worldMatrix = glm::translate(glm::mat4(1.0f), position)*glm::toMat4(rotation);
}

glm::mat4& SceneObject::getWorldMatrix()
{
	if (worldMatrixNeedsUpdate) 
	{
		worldMatrixNeedsUpdate = false;
		updateWorldMatrix();
	}
	return worldMatrix;
}

void SceneObject::moveBy(const glm::vec3 & vector)
{
	worldMatrixNeedsUpdate = true;
	position += vector;
}

void SceneObject::setRotation(const glm::vec3 & vector)
{
	worldMatrixNeedsUpdate = true;
	rotation = glm::quat(vector);
}

SceneObject::SceneObject()
{
	worldMatrixNeedsUpdate = true;
	position = glm::vec3(.0f,.0f,.0f);
	rotation = glm::quat(1.0f,.0f,.0f,.0f);
}


SceneObject::~SceneObject()
{
	
}
