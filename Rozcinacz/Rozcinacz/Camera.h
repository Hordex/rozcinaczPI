#pragma once
#include "SceneObject.h"
#include "../packages/glm.0.9.7.1/build/native/include/glm/detail/type_mat.hpp"

class Camera :
	public SceneObject
{
	glm::mat4 projectionMatrix,viewMatrix,viewProjectionMatrix;
	bool projectionNeedsUpdate, viewNeedsUpdate, lookAtLocked, lookAtNeedsUpdate;
	glm::vec3 lookAtTarget;
	void refreshLookAt();
public:
	glm::mat4& getViewProjectionMatrix();
	void moveBy(glm::vec3 & vector) override;
	void moveTo(glm::vec3 & vector);
	void setLookAtLock(bool state);
	void lookAt(glm::vec3 & center);
	void render(GLuint shaderProgram) override;
	Camera();
	Camera(float FoV, float width, float height, float nearPlane, float farPlane);
	void perspective(float FoV, float width, float height, float nearPlane, float farPlane);
	~Camera();
};

