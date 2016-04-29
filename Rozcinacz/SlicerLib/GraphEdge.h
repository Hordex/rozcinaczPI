#pragma once
#include "EdgeState.h"

/// <summary>
/// An edge of a graph.
/// </summary>
class GraphEdge
{
	/// <summary>
	/// The state of  <see cref="GraphEdge" />
	/// </summary>
	EdgeState state;
	/// <summary>
	/// The ends of  <see cref="GraphEdge" />
	/// </summary>
	int ends[2];
public:
	int From() const;
	int To() const;
	EdgeState State() const;
	/// <summary>
	/// Initializes a new instance of the <see cref="GraphEdge" /> class.
	/// </summary>
	/// <param name="from">From vertex.</param>
	/// <param name="to">To vertex.</param>
	/// <param name="state">State of the edge.</param>
	GraphEdge(int from, int to, EdgeState state);
	/// <summary>
	/// Finalizes an instance of the <see cref="GraphEdge"/> class.
	/// </summary>
	~GraphEdge();
};

