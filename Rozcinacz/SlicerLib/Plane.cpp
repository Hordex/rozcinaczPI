#include "Plane.h"
#include <GL/glew.h>

void Plane::render(unsigned shaderProgram)
{
	GLint worldmatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	GLint normalLocation = glGetUniformLocation(shaderProgram, "normal");
	glUniformMatrix4fv(worldmatrixLocation, 1, GL_FALSE, &(getWorldMatrix()[0][0]));
	glUniform3fv(normalLocation,1,&normal[0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Plane::Plane()
{
	vertices[0] = glm::vec3(1.0f, 0.0f, 1.0f);  // Top Right
	vertices[1] = glm::vec3(1.0f, 0.0f, -1.0f);  // Bottom Right
	vertices[2] = glm::vec3(-1.0f, 0.0f, -1.0f);  // Bottom Left
	vertices[3] = glm::vec3(-1.0f, 0.0f, 1.0f);
	normal = glm::vec3(0, 1, 0);
	//vertices[0] = glm::vec3(1.0f,   1.0f,0.0f);  // Top Right
	//vertices[1] = glm::vec3(1.0f,  -1.0f,0.0f);  // Bottom Right
	//vertices[2] = glm::vec3(-1.0f, -1.0f,0.0f);  // Bottom Left
	//vertices[3] = glm::vec3(-1.0f,  1.0f,0.0f);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, BOs);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, BOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}


Plane::~Plane()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, BOs);
}
