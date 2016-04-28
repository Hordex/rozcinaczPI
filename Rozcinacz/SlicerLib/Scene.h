#pragma once
#include "SceneObject.h"
#include <list>
#include "Plane.h"

/// <summary>
/// Class holding all objects to be rendered
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Defaults the scene.
	/// </summary>
	void defaultScene();
	/// <summary>
	/// The children
	/// </summary>
	std::list<Plane*> children;
	/// <summary>
	/// Adds a child.
	/// </summary>
	/// <param name="child">A child.</param>
	void addChild(Plane* child);
	/// <summary>s
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	Scene();
	/// <summary>
	/// Finalizes an instance of the <see cref="Scene"/> class.
	/// </summary>
	~Scene();
};

