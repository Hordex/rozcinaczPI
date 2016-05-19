#include "GraphEdge.h"
#include "Collider.h"
#include <easylogging++.h>

int GraphEdge::From() const
{
	return ends[0];
}

int GraphEdge::To() const
{
	return ends[0];
}

EdgeState GraphEdge::State() const
{
	return state;
}

Collider* GraphEdge::CubeEdge() const
{
	return collider;
}

GraphEdge::GraphEdge(int from, int to, EdgeState state, Collider* collider)
{
	this->collider = collider;
	LOG(TRACE) << "Creating GraphEdge from: " << from <<" to: " << to << ", state: " << state;
	this->state = state;
	ends[0] = from;
	ends[1] = to;
}

GraphEdge::~GraphEdge()
{

}
