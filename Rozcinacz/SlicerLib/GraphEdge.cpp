#include "GraphEdge.h"
#include "Collider.h"
#include <easylogging++.h>

int GraphEdge::From() const
{
	return this->ends[0];
}

int GraphEdge::To() const
{
	return this->ends[1];
}

Collider* GraphEdge::CubeEdge() const
{
	return this->collider;
}

GraphEdge::GraphEdge(int from, int to, Collider* collider)
{
	this->collider = collider;
	LOG(TRACE) << "Creating GraphEdge from: " << from << " to: " << to;
	ends[0] = from;
	ends[1] = to;
}

GraphEdge::~GraphEdge()
{
	LOG(TRACE) << "Deleting GraphEdge from: " << ends[0] << " to: " << ends[1];
}
