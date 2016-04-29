#include <easylogging++.h>
#include <algorithm>
#include "Graph.h"
#include "EdgeState.h"

void Graph::Analyze(int i)
{
	LOG(TRACE) << "Checking node " << i << " for possible lock";
	auto freeEdges = std::count_if(adjacencyVector[i].begin(), adjacencyVector[i].end(), [](EdgeRef& e) {return !e.second; });
	if(freeEdges == 1)
	{
		auto edge = std::find_if(adjacencyVector[i].begin(), adjacencyVector[i].end(), [](EdgeRef& e) {return !e.second; });
		LockEdge(i, edge->first);
		Analyze(edge->first);
	}
}

void Graph::LockEdge(int from, int to)
{
	LOG(TRACE) << "Locking edge " << from << "-" << to;
	auto edge1 = std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [](EdgeRef& e) {return !e.second; });
	auto edge2 = std::find_if(adjacencyVector[to].begin(), adjacencyVector[to].end(), [from](EdgeRef& e) {return from == e.first; });
	edge1->second = edge2->second = Locked;
}

bool Graph::SetVertex(int index, Plane* plane)
{
	LOG(TRACE) << "Setting plane in for vertex " << index;
	if (index >= nodes.size() || index < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		return false;
	}
	nodes[index].SetPlane(plane);
	return true;
}

int Graph::Size() const
{
	return size;
}

bool Graph::AreConnected(int from, int to) const
{
	LOG(TRACE) << "Looking for connection: " << from << " with " << to;
	if (from >= adjacencyVector.size() || to >= adjacencyVector.size() || from < 0 || to < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		return false;
	}
	if (from == to)
	{
		return false;
	}
	return std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [to](const EdgeRef& e) {return e.first == to; }) != adjacencyVector[from].end();
}

bool Graph::ConnectVertices(int from, int to)
{
	LOG(TRACE) << "Connecting " << from << " with " << to;
	if(AreConnected(from,to))
	{
		LOG(WARNING) << "Already connected";
		return true;
	}
	if(from >= adjacencyVector.size() || to >= adjacencyVector.size() || from < 0 || to < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		return false;
	}
	if(from == to)
	{
		LOG(ERROR) << "Cannot connect vertex to itself";
		return false;
	}
	adjacencyVector[from].push_back(EdgeRef(to, Free));
	adjacencyVector[to].push_back(EdgeRef(from, Free));
	return true;
}

GraphNode& Graph::GetNode(int index)
{
	if (index >= nodes.size() || index < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		throw "Index out of bounds";
	}
	return nodes[index];
}

bool Graph::CutEdge(int from, int to)
{
	LOG(TRACE) << "Cutting GraphEdge " << from << "-" << to;
	if(!AreConnected(from,to))
	{
		LOG(WARNING) << "No such edge";
		return false;
	}
	auto a = std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [to](const EdgeRef& e) {return e.first == to; });
	if(a->second)
	{
		LOG(WARNING) << "Edge cannot be cut, state is " << a->second;
		return false;
	}
	a->second = Deleted;
	auto b = std::find_if(adjacencyVector[to].begin(), adjacencyVector[to].end(), [from](const EdgeRef& e) {return e.first == from; });
	b->second = Deleted;
	return true;
}

void Graph::ClearAll()
{
	LOG(TRACE) << "Clearing adjacency vector";
	for (auto& adj : adjacencyVector)
	{
		adj.clear();
	}
	LOG(TRACE) << "Clearing nodes";
	for (auto& node : nodes)
	{
		node.ClearPlane();
	}
}

Graph::Graph(int vertices) : adjacencyVector(vertices), nodes(vertices)
{
	LOG(TRACE) << "Creating Graph with " << vertices << " vertices";
	size = vertices;
}

Graph::~Graph()
{

}
