#include "Scene.h"
#include "Plane.h"
#include "Graph.h"
#include <easylogging++.h>

void Scene::defaultScene(Graph& graph)
{
	Clear();
	bool graphflag = graph.Size() == 6;

	int adjacencies[][4] = {
		{ 2,3,4,5 },
		{ 2,3,4,5 },
		{ 0,1,4,5 },
		{ 0,1,4,5 },
		{ 0,1,2,3 },
		{ 0,1,2,3 }
	};

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
		p = new Plane(i);
		p->moveBy(pos[i]);
		p->setRotation(rot[i]);
		addChild(p);
		if(graphflag)
		{
			graph.GetNode(i).SetPlane(p);
			for (int j = 0; j < 4;++j)
			{
				graph.ConnectVertices(i, adjacencies[i][j]);
			}
		}
	}
}

void Scene::defaultScene()
{
	Clear();
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
		p = new Plane(i);
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

Scene::Scene(Graph& graph)
{
	defaultScene(graph);
}

void Scene::Clear()
{
	LOG(TRACE) << "Clearing scene";
	for (auto child : children)
		delete child;
	children.clear();
}

Scene::~Scene()
{
	Clear();
}
