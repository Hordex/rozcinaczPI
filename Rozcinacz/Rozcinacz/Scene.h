#pragma once
#include "SceneObject.h"
#include <list>
#include "Plane.h"

class Scene
{
public:
	void defaultScene();
	std::list<Plane*> children;
	void addChild(Plane* child);
	Scene();
	~Scene();
};

