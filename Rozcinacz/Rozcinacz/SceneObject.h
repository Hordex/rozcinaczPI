#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GL/glew.h>

class SceneObject
{
	std::vector<SceneObject*> children;
	glm::mat4 worldMatrix;
	bool worldMatrixNeedsUpdate;
	void updateWorldMatrix();
protected:
	glm::quat rotation;
	glm::mat4& getWorldMatrix();
public:
	glm::vec3 position;
	virtual void moveBy(glm::vec3 & vector);
	void setRotation(glm::vec3 & rotaion);
	virtual void render(GLuint shaderProgram) = 0;
	SceneObject();
	virtual ~SceneObject();
};

