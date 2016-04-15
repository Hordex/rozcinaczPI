#pragma once
#include "SceneObject.h"
#include <list>
#include "Plane.h"

/// <summary>
/// Scene
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
	/// Adds the child.
	/// </summary>
	/// <param name="child">The child.</param>
	void addChild(Plane* child);
	/// <summary>
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	Scene();
	/// <summary>
	/// Finalizes an instance of the <see cref="Scene"/> class.
	/// </summary>
	~Scene();
};

