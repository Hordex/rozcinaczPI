#include "SceneObject.h"
#include <glm/glm.hpp>
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

bool SceneObject::TestRayOBBIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, float& intersection_distance)
{
	glm::mat4 ModelMatrix = getWorldMatrix();
	glm::vec3 aabb_min = getAABBMin();
	glm::vec3 aabb_max = getAABBMax();

	// Intersection method from Real-Time Rendering and Essential Mathematics for Games

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - rayOrigin;

	for (int i = 0; i<3; ++i)
	{
		glm::vec3 axis(ModelMatrix[i].x, ModelMatrix[i].y, ModelMatrix[i].z);
		float e = glm::dot(axis, delta);
		float f = glm::dot(rayDirection, axis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min[i]) / f;
			float t2 = (e + aabb_max[i]) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMax < tMin)
				return false;

		}
		else {
			if (-e + aabb_min[i] > 0.0f || -e + aabb_max[i] < 0.0f)
				return false;
		}
	}

	intersection_distance = tMin;
	return true;
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