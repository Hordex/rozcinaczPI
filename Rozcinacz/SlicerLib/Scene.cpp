#include "Cube.h"
#include "Scene.h"
#include "Plane.h"
#include "Graph.h"
#include <easylogging++.h>
#include "Collider.h"

SceneObject* Scene::CastRay(glm::vec3 origin, glm::vec3 direction)
{
	SceneObject* ret = nullptr;
	float minDistance = 99999;
	float distance = minDistance;
	for (SceneObject* object : children)
	{
		if (object->TestRayOBBIntersection(origin, direction, distance))
		{
			if(distance < minDistance)
			{
				minDistance = distance;
				ret = object;
			}
		}
	}
	return ret;
}

void Scene::CreateFaces(Graph& graph)
{
	bool graphflag = graph.Size() == 6;
	Plane* p;
	for (int i = 0; i < cube::End; ++i)
	{
		LOG(TRACE) << "Creating face " << i;
		p = new Plane(i);
		p->moveBy(cube::GetFacePosition(static_cast<cube::Side>(i)));
		p->setRotation(cube::GetFaceRotation(static_cast<cube::Side>(i)));
		addChild(p);
		if (graphflag)
			graph.GetNode(i).SetPlane(p);
	}
}

void Scene::CreateEdges(Graph& graph)
{
	bool graphflag = graph.Size() == 6;
	Collider* c;
	int count = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = i - i%2 + 2; j < cube::End; ++j)
		{
			LOG(TRACE) << "Creating collider " << count++ << ", " << i << " - " << j;
			c = new Collider();
			c->SetConnection(i,j);
			c->moveBy(cube::GetEdgePosition(static_cast<cube::Side>(i), static_cast<cube::Side>(j)));
			c->setRotation(cube::GetEdgeRotation(static_cast<cube::Side>(i), static_cast<cube::Side>(j)));
			addChild(c);
			if (graphflag)
			{
				graph.ConnectVertices(i, j,c);
			}
		}
	}
}

void Scene::defaultScene(Graph& graph)
{
	Clear();
	CreateFaces(graph);
	CreateEdges(graph);
}

void Scene::addChild(SceneObject* child)
{
	children.push_front(child);
}

void Scene::removeChild(SceneObject* child)
{
	children.remove_if([child](SceneObject* obj) {return obj == child; });
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
