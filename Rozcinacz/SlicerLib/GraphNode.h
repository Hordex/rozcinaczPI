#pragma once
#include <iosfwd>
class Plane;

/// <summary>
/// A node in the graph
/// </summary>
class GraphNode
{
	/// <summary>
	/// <see cref="Plane"/> represented by this <see cref="GraphNode"/>
	/// </summary>
	Plane* planeRef;
	/// <summary>
	/// The index of <see cref="GraphNode"/>
	/// </summary>
	int index;
public:
	Plane* GetPlane();
	/// <summary>
	/// Bind <see cref="Plane"/> to <see cref="GraphNode"/>.
	/// </summary>
	/// <param name="plane">The plane.</param>
	void SetPlane(Plane* plane);
	/// <summary>
	/// Sets the index of <see cref="GraphNode"/>.
	/// </summary>
	/// <param name="index">The index.</param>
	void SetIndex(int index);
	/// <summary>
	/// Clears the plane.
	/// </summary>
	void ClearPlane();
	/// <summary>
	/// Returns index of the <see cref="GraphNode"/>.
	/// </summary>
	/// <returns>Index</returns>
	int Index() const;
	friend std::ostream& operator<<(std::ostream& os, const GraphNode& obj);
	/// <summary>
	/// Initializes a new instance of the <see cref="GraphNode"/> class.
	/// </summary>
	GraphNode(Plane* plane = nullptr);
	/// <summary>
	/// Finalizes an instance of the <see cref="GraphNode"/> class.
	/// </summary>
	~GraphNode();
};

