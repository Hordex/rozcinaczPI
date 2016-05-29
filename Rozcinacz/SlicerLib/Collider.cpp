#include "Collider.h"
#include <GL/glew.h>
#include "MaterialInstances.h"
#include <easylogging++.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Collider::collisoiinExtent(0.95f, 0.05f, 0.05f);

void Collider::SetJointRotation(glm::quat& rot)
{
	//InvalidateModelMatrix();
	timeElapsed = 0.0f;
	startJointRotation = jointRotation;
	targetJointRotation = rot;
}

bool Collider::FrameUpdate(float dt)
{
	if (timeElapsed >= 1.0f)
		return false;
	timeElapsed += dt;
	auto newRot = glm::mix(startJointRotation,targetJointRotation, min(timeElapsed,1.0f));
	InvalidateModelMatrix();
	if (timeElapsed >= 1.0f)
	{
		jointRotation = targetJointRotation;
		if(shouldBreakChain)
		{
			BreakChain();
		}
		startJointRotation = targetJointRotation;
	}
	else
		jointRotation = newRot;

	return true;
}

void Collider::BreakChain()
{
	for(auto child : children)
	{
		child->ApplySpace(glm::one<glm::mat4>());
	}
	RemoveAllChildren();
	this->ApplySpace(glm::one<glm::mat4>());
	//this->ApplySpace(parent->getWorldMatrix());
	parent->removeChild(this);
}

glm::mat4 Collider::CreateModelMatrix() const
{
	return glm::translate(glm::mat4(1.0f), position)*glm::toMat4(rotation * jointRotation);
}

glm::vec3 Collider::getAABBMin()
{
	return -collisoiinExtent;
}
glm::vec3 Collider::getAABBMax()
{
	return collisoiinExtent;
}

void Collider::MouseEnter()
{
	material = &materials::edges::hover;
}

void Collider::MouseLeave()
{
	material = &materials::edges::normal;
}

bool Collider::MouseClick(int& from, int& to)
{
	LOG(TRACE) << "Clicked collider from " << connection[0] << " to " << connection[1];
	isCut = true;
	from = connection[0];
	to = connection[1];
	return true;
}

void Collider::Restore()
{
	LOG(TRACE) << "Restoring collider from " << connection[0] << " to " << connection[1];
	isCut = false;
}

bool Collider::TestRayOBBIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, float& intersection_distance)
{
	if (isLocked || isCut)return false;
	return SceneObject::TestRayOBBIntersection(rayOrigin, rayDirection, intersection_distance);
}

void Collider::Lock()
{
	isLocked = true;
	material = &materials::edges::locked;
}

void Collider::UnLock()
{
	LOG(TRACE) << "Unlocking collider from " << connection[0] << " to " << connection[1];
	isLocked = false;
	material = &materials::edges::normal;
}

void Collider::SetConnection(int from,int to)
{
	connection[0] = from;
	connection[1] = to;
}

int* Collider::GetConnection()
{
	return connection;
}

void Collider::render(unsigned shaderProgram)
{
	if (isCut)
		return;
	GLint worldmatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldmatrixLocation, 1, GL_FALSE, &(getWorldMatrix()[0][0]));
	material->UseMaterial(shaderProgram);
	glBindVertexArray(VAO);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glLineWidth(3.0f);
	glDrawArrays(GL_LINES, 0, 2);
#ifdef _DEBUG
	glBindVertexArray(debugVAO);
	glDrawElements(GL_LINE_STRIP, 16, GL_UNSIGNED_INT, 0);
#endif
	glLineWidth(1.0f);
	glDisable(GL_POLYGON_OFFSET_FILL);

	glBindVertexArray(0);

}

void Collider::JointRotateBy(float angle, bool breakChain)
{
	glm::quat rot(glm::vec3(angle,0.f,0.f));
	this->SetJointRotation(this->targetJointRotation * rot);
	this->shouldBreakChain = breakChain;
}

void Collider::JointRotateTo(float angle, bool breakChain)
{
	glm::quat rot(glm::vec3(angle, 0.f, 0.f));
	this->SetJointRotation(rot);
	this->shouldBreakChain = breakChain;
}

Collider::Collider() :jointRotation(glm::vec3(0, 0, 0)),targetJointRotation(jointRotation),timeElapsed(999.9f)
{
	material = &materials::edges::normal;
	vertices[0] = glm::vec3(-1.0f, 0.0f, 0.0f);
	vertices[1] = glm::vec3(1.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
#ifdef _DEBUG
	float cX = collisoiinExtent.x, cY = collisoiinExtent.y, cZ = collisoiinExtent.z;
	glGenVertexArrays(1, &debugVAO);
	glGenBuffers(2, debugBOs);
	debugVertices[0] = glm::vec3( cX,  cY,  cZ);
	debugVertices[1] = glm::vec3( cX, -cY,  cZ);
	debugVertices[2] = glm::vec3(-cX, -cY,  cZ);
	debugVertices[3] = glm::vec3(-cX,  cY,  cZ);
	debugVertices[4] = glm::vec3( cX,  cY, -cZ);
	debugVertices[5] = glm::vec3( cX, -cY, -cZ);
	debugVertices[6] = glm::vec3(-cX, -cY, -cZ);
	debugVertices[7] = glm::vec3(-cX,  cY, -cZ);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(debugVAO);

	glBindBuffer(GL_ARRAY_BUFFER, debugBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(debugVertices), debugVertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, debugBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(debugIndices), debugIndices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
#endif
}


Collider::~Collider()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
#ifdef _DEBUG
	glDeleteVertexArrays(1, &debugVAO);
	glDeleteBuffers(2, debugBOs);
#endif
}
