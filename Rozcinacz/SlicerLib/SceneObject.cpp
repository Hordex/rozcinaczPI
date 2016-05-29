#include "SceneObject.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>


void SceneObject::updateModelMatrix()
{
	modelMatrix = miscMatrix*CreateModelMatrix();
	worldMatrix = modelMatrix;
	UpdateParentSpace();
	modelMatrixNeedsUpdate = false;
}

void SceneObject::RemoveAllChildren()
{
	for (auto child : children)
		child->ParentUpdate(nullptr);
	children.clear();
}

glm::mat4 SceneObject::CreateModelMatrix() const
{
	return glm::translate(glm::mat4(1.0f), position)*glm::toMat4(rotation);
}

bool SceneObject::FrameUpdate(float dt)
{
	return false;
}

void SceneObject::ParentUpdate(SceneObject* parent)
{
	InvalidateParent();
	this->parent = parent;
}

void SceneObject::UpdateParentSpace()
{
	if (parent)
		worldMatrix = parent->getWorldMatrix() * modelMatrix;
	parentChanged = false;
}

const glm::mat4& SceneObject::getWorldMatrix()
{
	if (modelMatrixNeedsUpdate) 
	{
		updateModelMatrix();
	}
	if(parentChanged)
	{
		UpdateParentSpace();
	}
	return worldMatrix;
}

const glm::mat4& SceneObject::getModelMatrix()
{
	if (modelMatrixNeedsUpdate)
	{
		updateModelMatrix();
	}
	return modelMatrix;
}

const glm::vec3& SceneObject::getPosition() const
{
	return position;
}

bool SceneObject::TestRayOBBIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, float& intersection_distance)
{
	glm::mat4 RayWorldMatrix = getWorldMatrix();
	glm::vec3 aabb_min = getAABBMin();
	glm::vec3 aabb_max = getAABBMax();

	// Intersection method from Real-Time Rendering and Essential Mathematics for Games

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(RayWorldMatrix[3].x, RayWorldMatrix[3].y, RayWorldMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - rayOrigin;

	for (int i = 0; i<3; ++i)
	{
		glm::vec3 axis(RayWorldMatrix[i].x, RayWorldMatrix[i].y, RayWorldMatrix[i].z);
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

void SceneObject::InvalidateParent()
{
	parentChanged = true;
	for (SceneObject* child : children)
	{
		child->InvalidateParent();
	}
}

void SceneObject::InvalidateModelMatrix()
{
	modelMatrixNeedsUpdate = true;
	for(SceneObject* child : children)
	{
		child->InvalidateParent();
	}
}

void SceneObject::moveTo(glm::vec3& vector)
{
	InvalidateModelMatrix();
	position = vector;
}

void SceneObject::moveBy(const glm::vec3 & vector)
{
	InvalidateModelMatrix();
	position += vector;
}

void SceneObject::setRotation(const glm::vec3 & vector)
{
	setRotation(glm::quat(vector));
}

void SceneObject::setRotation(const glm::quat& rotaion)
{
	InvalidateModelMatrix();
	this->rotation = rotaion;
}

void SceneObject::ApplySpace(const glm::mat4& matrix)
{
	InvalidateModelMatrix();
	miscMatrix = matrix;
	return;
	glm::vec4 dest = (matrix * glm::vec4(position, 1.0));
	position.x = round(dest.x);
	position.y = round(dest.y);
	position.z = round(dest.z);
	rotation = glm::toQuat(matrix) *rotation;
}

void SceneObject::rotateBy(const glm::vec3& rotaion)
{
	InvalidateModelMatrix();
	this->rotation = glm::quat(rotaion)*this->rotation;
}

SceneObject::SceneObject():parent(nullptr),miscMatrix(glm::one<glm::mat4>())
{
	parentChanged = false;
	InvalidateModelMatrix();
	position = glm::vec3(.0f,.0f,.0f);
	rotation = glm::quat(1.0f,.0f,.0f,.0f);
}


SceneObject::~SceneObject()
{
	
}

void SceneObject::addChild(SceneObject* child)
{
	if (child)
		child->ParentUpdate(this);
	children.push_front(child);
}

void SceneObject::removeChild(SceneObject* child)
{
	if (child)
		child->ParentUpdate(nullptr);
	children.remove_if([child](SceneObject* obj) {return child == obj; });
}

void SceneObject::Mimic(glm::vec3 v1, glm::vec3 v2)
{
	InvalidateModelMatrix();
	rotation = glm::rotation(v1, v2)*rotation;
}
