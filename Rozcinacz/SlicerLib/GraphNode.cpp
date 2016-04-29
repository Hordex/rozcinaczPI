#include <iostream>
#include <easylogging++.h>
#include "GraphNode.h"

void GraphNode::SetPlane(Plane* plane)
{
	if(!plane)LOG(WARNING) << "Plane is null. Was it intended?";
	planeRef = plane;
}

void GraphNode::SetIndex(int index)
{
	this->index = index;
}

void GraphNode::ClearPlane()
{
	planeRef = nullptr;
}

int GraphNode::Index() const
{
	return index;
}

GraphNode::GraphNode(Plane* plane): index(0) {
	LOG(TRACE) << "Creating GraphNode " << (plane ? " with plane" : " without plane");
	planeRef = plane;
}

GraphNode::~GraphNode()
{
}

std::ostream& operator<<(std::ostream& os, const GraphNode& obj)
{
	return os << "A node";
}
