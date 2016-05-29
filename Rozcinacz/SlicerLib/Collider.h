#pragma once
#include "SceneObject.h"
#include "Material.h"
#include <gl/glew.h>

class Collider :
	public SceneObject
{
	glm::quat jointRotation;
	glm::quat targetJointRotation;
	float timeElapsed;
	glm::quat startJointRotation;
	bool shouldBreakChain;
	static glm::vec3 collisoiinExtent;
	/// <summary>
	/// The vertices
	/// </summary>
	glm::vec3 vertices[2];
	Material* material;
	GLuint VAO;
	GLuint VBO;
	int connection[2];
	bool isLocked = false;
	bool isCut = false;
	void BreakChain();
#ifdef _DEBUG
	GLuint debugVAO;
	GLuint debugBOs[2];
	glm::vec3 debugVertices[8];
	int debugIndices[16] = { 0,1,2,3,0, 4, 5, 6, 7, 4, 5, 1, 2, 6, 7, 3};
#endif
protected:
	glm::mat4 CreateModelMatrix() const override;
	void SetJointRotation(glm::quat& rot);
public:
	bool FrameUpdate(float dt) override;
	glm::vec3 getAABBMin() override;
	glm::vec3 getAABBMax() override;
	void MouseEnter() override;
	void MouseLeave() override;
	bool MouseClick(int& from, int& to) override;
	void Restore();
	bool TestRayOBBIntersection(glm::vec3 rayOrigin, glm::vec3 rayDirection, float& intersection_distance) override;
	void Lock();
	void UnLock();
	void SetConnection(int,int);
	int* GetConnection();
	void render(unsigned shaderProgram) override;
	void JointRotateBy(float angle, bool breakChain = false);
	void JointRotateTo(float angle, bool breakChain = false);
	Collider();
	~Collider();
};

