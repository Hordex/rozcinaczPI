#pragma once
#include <list>
#include <glm/fwd.hpp>
class SceneObject;
class Graph;
class Plane;

/// <summary>
/// Class holding all objects to be rendered
/// </summary>
class Scene
{
public:
	bool FrameUpdate(float dt);
	SceneObject* CastRay(glm::vec3 origin, glm::vec3 direction);
	void CreateFaces(Graph& graph);
	void CreateEdges(Graph& graph);
	/// <summary>
	/// Defaults the scene.
	/// </summary>
	void defaultScene(Graph& graph);
	void defaultScene();
	/// <summary>
	/// The children
	/// </summary>
	std::list<SceneObject*> children;
	/// <summary>
	/// Adds a child.
	/// </summary>
	/// <param name="child">A child.</param>
	void addChild(SceneObject* child);
	/// <summary>
	/// Removes a child.
	/// </summary>
	/// <param name="child">A child.</param>
	void removeChild(SceneObject* child);
	void Clear();
	/// <summary>
	/// Finalizes an instance of the <see cref="Scene"/> class.
	/// </summary>
	~Scene();
};

