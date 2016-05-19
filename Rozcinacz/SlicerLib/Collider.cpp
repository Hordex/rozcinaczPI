#include "Collider.h"
#include <GL/glew.h>
#include "MaterialInstances.h"

glm::vec3 Collider::collisoiinExtent(0.95f, 0.05f, 0.05f);

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

void Collider::MouseClick()
{
	isCut = true;
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
	isLocked = false;
	material = &materials::edges::normal;
}

void Collider::SetConnection(int nodes[])
{
	connection[0] = nodes[0];
	connection[1] = nodes[1];
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

Collider::Collider()
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
