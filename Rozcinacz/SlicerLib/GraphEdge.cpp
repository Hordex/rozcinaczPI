#include "GraphEdge.h"
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

GraphEdge::GraphEdge(int from, int to, EdgeState state)
{
	LOG(TRACE) << "Creating GraphEdge from: " << from <<" to: " << to << ", state: " << state;
	this->state = state;
	ends[0] = from;
	ends[1] = to;
}

GraphEdge::~GraphEdge()
{

}
