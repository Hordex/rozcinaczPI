#pragma once
#include "EdgeState.h"

/// <summary>
/// An edge of a graph.
/// </summary>
class GraphEdge
{
	class Collider* collider;
	/// <summary>
	/// The ends of  <see cref="GraphEdge" />
	/// </summary>
	int ends[2];
public:
	int From() const;
	int To() const;
	class Collider* CubeEdge() const;
	/// <summary>
	/// Initializes a new instance of the <see cref="GraphEdge" /> class.
	/// </summary>
	/// <param name="from">From vertex.</param>
	/// <param name="to">To vertex.</param>
	/// <param name="state">State of the edge.</param>
	GraphEdge(int from, int to, class Collider* collider);
	/// <summary>
	/// Finalizes an instance of the <see cref="GraphEdge"/> class.
	/// </summary>
	~GraphEdge();
};

