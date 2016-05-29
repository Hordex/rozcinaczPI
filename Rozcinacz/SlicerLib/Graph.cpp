#include <easylogging++.h>
#include <algorithm>
#include "Graph.h"
#include "EdgeState.h"
#include "Collider.h"
#include "Plane.h"
#include "Cube.h"
#include <glm/gtx/quaternion.inl>
#include <glm/gtx/norm.inl>

std::list<GraphEdge*> Graph::Analyze(int i)
{
	std::list<GraphEdge*> ret;
	LOG(TRACE) << "Checking node " << i << " for possible lock";
	auto freeEdges = std::count_if(adjacencyVector[i].begin(), adjacencyVector[i].end(), [](EdgeRef& e) {return !std::get<1>(e); });
	if(freeEdges == 1)
	{
		auto edge = std::find_if(adjacencyVector[i].begin(), adjacencyVector[i].end(), [](EdgeRef& e) {return !std::get<1>(e); });
		LockEdge(i, std::get<0>(*edge));
		LOG(TRACE) << "Adding to history edge from " << i << " to " << std::get<0>(*edge);
		ret.splice(ret.end(), Analyze(std::get<0>(*edge)));
		ret.push_back(new GraphEdge(i, std::get<0>(*edge), std::get<2>(*edge)));
	}
	return ret;
}

bool Graph::Undo()
{
	if (history.empty()) return false;
	LOG(TRACE) << "Undoing last action";
	auto step = history.top(); history.pop();
	for(GraphEdge* edge : step)
	{
		int from = edge->From();
		int to = edge->To();
		RestoreEdge(from, to);
	}
	step.remove_if([](GraphEdge* edge) {delete edge; return true; });
	return true;
}

void Graph::Attach(int from, EdgeRef to)
{
	Collider* col = std::get<2>(to);
	int toIndex = std::get<0>(to);
	Plane* face1 = nodes[from].GetPlane();
	Plane* face2 = nodes[toIndex].GetPlane();
	face2->addChild(col);
	col->ApplySpace(glm::inverse(face2->getWorldMatrix()));
	col->addChild(face1);
	face1->ApplySpace(glm::inverse(col->getWorldMatrix()));
	auto pos = col->getPosition();
	auto rot = col->getRotation();
	auto face1pos = face1->getPosition();
	float angle = 90.f;
	auto target = col->getWorldMatrix() * glm::vec4(face1pos.x, - face1pos.z,face1pos.y, 1.0f);
	if(fabs(target.x) < 1.9f && fabs(target.y) < 1.9f && fabs(target.z) < 1.9f)
	{
		angle *= -1;
	}
	col->JointRotateBy(glm::radians(angle));
}

void Graph::LockEdge(int from, int to)
{
	LOG(TRACE) << "Locking edge " << from << "-" << to;
	auto edge1 = std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [](EdgeRef& e) {return !std::get<1>(e); });
	auto edge2 = std::find_if(adjacencyVector[to].begin(), adjacencyVector[to].end(), [from](EdgeRef& e) {return from == std::get<0>(e); });
	std::get<1>(*edge1) = std::get<1>(*edge2) = Locked;
	Attach(from, *edge1);
	if (std::get<2>(*edge1))std::get<2>(*edge1)->Lock();
}

void Graph::Detach(int from, EdgeRef edge)
{
	Collider* col = std::get<2>(edge);
	int toIndex = std::get<0>(edge);
	Plane* face1 = nodes[from].GetPlane();
	Plane* face2 = nodes[toIndex].GetPlane();
	col->JointRotateTo(0.0f,true);
}

void Graph::RestoreEdge(int from, int to)
{
	LOG(TRACE) << "Restoring edge " << from << "-" << to;
	auto edge1 = std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [to](EdgeRef& e) {return std::get<0>(e) == to; });
	auto edge2 = std::find_if(adjacencyVector[to].begin(), adjacencyVector[to].end(), [from](EdgeRef& e) {return from == std::get<0>(e); });
	if(std::get<2>(*edge1))
	{
		switch(std::get<1>(*edge1))
		{
		case Locked:
			std::get<2>(*edge1)->UnLock();
			Detach(from, *edge1);
			break;
		case Deleted:
			std::get<2>(*edge1)->Restore();
			break;
		default:
			break;
		}
	}
	std::get<1>(*edge1) = std::get<1>(*edge2) = Free;
}

bool Graph::SetVertex(int index, Plane* plane)
{
	LOG(TRACE) << "Setting plane in for vertex " << index;
	if ((unsigned)index >= nodes.size() || index < 0)
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
	if ((unsigned)from >= adjacencyVector.size() || (unsigned)to >= adjacencyVector.size() || from < 0 || to < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		return false;
	}
	if (from == to)
	{
		return false;
	}
	return std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [to](const EdgeRef& e) {return std::get<0>(e) == to; }) != adjacencyVector[from].end();
}

bool Graph::ConnectVertices(int from, int to, Collider* collider)
{
	LOG(TRACE) << "Connecting " << from << " with " << to;
	if(AreConnected(from,to))
	{
		LOG(WARNING) << "Already connected";
		return true;
	}
	if((unsigned)from >= adjacencyVector.size() || (unsigned)to >= adjacencyVector.size() || from < 0 || to < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		return false;
	}
	if(from == to)
	{
		LOG(ERROR) << "Cannot connect vertex to itself";
		return false;
	}
	adjacencyVector[from].push_back(EdgeRef(to, Free,collider));
	adjacencyVector[to].push_back(EdgeRef(from, Free,collider));
	return true;
}

GraphNode& Graph::GetNode(int index)
{
	if ((unsigned)index >= nodes.size() || index < 0)
	{
		LOG(ERROR) << "Index out of bounds";
		throw "Index out of bounds";
	}
	return nodes[index];
}

bool Graph::CutEdge(int from, int to)
{
	LOG(TRACE) << "Cutting GraphEdge " << from << "-" << to;
	if (!AreConnected(from, to))
	{
		LOG(WARNING) << "No such edge";
		return false;
	}
	auto a = std::find_if(adjacencyVector[from].begin(), adjacencyVector[from].end(), [to](const EdgeRef& e) {return std::get<0>(e) == to; });
	if (std::get<1>(*a))
	{
		LOG(WARNING) << "Edge cannot be cut, state is " << std::get<1>(*a);
		return false;
	}
	std::get<1>(*a) = Deleted;
	auto b = std::find_if(adjacencyVector[to].begin(), adjacencyVector[to].end(), [from](const EdgeRef& e) {return std::get<0>(e) == from; });
	std::get<1>(*b) = Deleted;
	LOG(TRACE) << "Adding to history edge from " << from << " to " << to;
	std::list<GraphEdge*> step = Analyze(from);
	step.splice(step.end(), Analyze(to));
	step.push_front(new GraphEdge(from, to, std::get<2>(*a)));
	history.push(step);
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
	while (!history.empty())
	{
		std::list<GraphEdge*> step = history.top();
		history.pop();
		step.remove_if([](GraphEdge* edge) {delete edge; return true; });
	}
}

Graph::Graph(int vertices) : adjacencyVector(vertices), nodes(vertices)
{
	LOG(TRACE) << "Creating Graph with " << vertices << " vertices";
	size = vertices;
}

Graph::~Graph()
{
	ClearAll();
}
