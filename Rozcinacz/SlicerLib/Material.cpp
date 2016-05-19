#include "Material.h"
#include <GL/glew.h>

void Material::SetColor(glm::vec3 color)
{
	this->color = color;
}

void Material::UseMaterial(unsigned shaderProgram)
{
	GLint colorLocation = glGetAttribLocation(shaderProgram, "color");
	GLint ambientLocation = glGetAttribLocation(shaderProgram, "ambient");
	GLint diffuseLocation = glGetAttribLocation(shaderProgram, "diffuse");
	glVertexAttrib3fv(colorLocation, &color[0]);
	glVertexAttrib1f(ambientLocation, ambient);
	glVertexAttrib1f(diffuseLocation, diffuse);
}

Material::Material(glm::vec3 color, float ambient, float diffuse):color(color)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
}

Material::~Material()
{
}
