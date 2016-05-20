#pragma once
#include <vector>
#include <list>
#include "EdgeState.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include <stack>

class Plane;
class Collider;

/// <summary>
///A graph
///</summary>
class Graph
{
	typedef std::tuple<int, EdgeState,Collider*> EdgeRef;
	
	std::stack<std::list<GraphEdge*>> history;
	/// <summary>
	/// The adjacency vector
	/// </summary>
	std::vector<std::list<EdgeRef>> adjacencyVector;
	/// <summary>
	/// The nodes
	/// </summary>
	std::vector<GraphNode> nodes;
	/// <summary>
	/// The size of graph
	/// </summary>
	int size;
	std::list<GraphEdge*> Analyze(int i);
public:
	bool Undo();
	void Attach(int from, EdgeRef to);
	void LockEdge(int from, int to);
	void Detach(int from, EdgeRef edge);
	void RestoreEdge(int from, int to);
	/// <summary>
	/// Associates index with plane
	/// </summary>
	/// <param name="index">The index.</param>
	/// <param name="plane">The plane.</param>
	/// <returns>True if vertex exists. False otherwise</returns>
	bool SetVertex(int index, Plane* plane);
	/// <summary>
	/// Sizes this instance.
	/// </summary>
	/// <returns>Size of the graph</returns>
	int Size() const;
	/// <summary>
	/// Checks if to vertices are connected.
	/// </summary>
	/// <param name="from">From vertex.</param>
	/// <param name="to">To vertex.</param>
	/// <returns>True if vertexes are connected. False otherwise.</returns>
	bool AreConnected(int from, int to) const;
	/// <summary>
	/// Connects the vertices.
	/// </summary>
	/// <param name="from">From vertex.</param>
	/// <param name="to">To vertex.</param>
	/// <returns>True if vertices are connected. False otherwise. Vertex cannot be connected to itself</returns>
	bool ConnectVertices(int from, int to, Collider* collider);
	/// <summary>
	/// Gets the node.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <returns>Node at specifed index</returns>
	GraphNode& GetNode(int index);
	/// <summary>
	/// Cuts the edge.
	/// </summary>
	/// <param name="from">From vertex.</param>
	/// <param name="to">To vertex.</param>
	/// <returns>True if vertices were connected and cut. False otherwise</returns>
	bool CutEdge(int from, int to);
	/// <summary>
	/// Clears graph.
	/// </summary>
	void ClearAll();
	/// <summary>
	/// Initializes a new instance of the <see cref="Graph"/> class.
	/// </summary>
	/// <param name="edges">Number of edges</param>
	Graph(int edges);
	/// <summary>
	/// Finalizes an instance of the <see cref="Graph"/> class.
	/// </summary>
	~Graph();
};