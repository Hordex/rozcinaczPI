#pragma once
#include <glm/glm.hpp>
/// <summary>
/// The material
/// </summary>
class Material
{
	glm::vec3 color;
	float ambient;
	float diffuse;
public:
	void SetColor(glm::vec3 color);
	void UseMaterial(unsigned shaderProgram);
	Material(glm::vec3,float,float);
	virtual ~Material();
};

