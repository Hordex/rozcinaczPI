#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <gl/glew.h>

class SceneObject
{
	std::vector<SceneObject> children;
	glm::mat4 worldMatrix;
	bool worldMatrixNeedsUpdate;
	void updateWorldMatrix();
protected:
	glm::vec3 position;
	glm::quat rotation;
	glm::mat4& getWorldMatrix();
public:
	virtual void moveBy(glm::vec3 & vector);
	void setRotation(glm::vec3 & rotaion);
	virtual void render(GLuint shaderProgram) = 0;
	SceneObject();
	virtual ~SceneObject();
};

