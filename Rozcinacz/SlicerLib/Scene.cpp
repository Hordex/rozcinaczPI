#include "Scene.h"

void Scene::defaultScene()
{
	glm::vec3 pos[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(-1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, -1.0f)
	};

	glm::vec3 rot[] = {
		glm::vec3(0.0f, 0.0f, glm::radians(90.0f)),
		glm::vec3(0.0f, 0.0f, glm::radians(90.0f)),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(glm::radians(90.0f), 0.0f, 0.0f),
		glm::vec3(glm::radians(90.0f), 0.0f, 0.0f)
	};
	Plane* p;

	for (int i = 0; i < 6; ++i)
	{
		p = new Plane();
		p->moveBy(pos[i]);
		p->setRotation(rot[i]);
		addChild(p);
	}
}

void Scene::addChild(Plane* child)
{
	children.push_front(child);
}

Scene::Scene()
{
	defaultScene();
}


Scene::~Scene()
{
	for (auto child : children)
		delete child;
	children.clear();
}
