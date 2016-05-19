#ifndef __CUBE__
#define __CUBE__
#include <glm/glm.hpp>

namespace cube
{
	enum Side { Top, Bottom, Left, Right, Front, Back, End };

	glm::vec3 GetFacePosition(Side side);
	glm::vec3 GetFaceRotation(Side side);
	glm::vec3 GetEdgePosition(Side side1, Side side2);
	glm::vec3 GetEdgeRotation(Side side1, Side side2);
}
#endif
