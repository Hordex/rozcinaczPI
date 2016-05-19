#include "Cube.h"

namespace cube {
	namespace detail
	{
		glm::vec3 positions[] =
		{
			glm::vec3(0.0f,1.0f,0.0f),
			glm::vec3(0.0f,-1.0f,0.0f),
			glm::vec3(-1.0f,0.0f,0.0f),
			glm::vec3(1.0f,0.0f,0.0f),
			glm::vec3(0.0f,0.0f,1.0f),
			glm::vec3(0.0f,0.0f,-1.0f)
		};
		glm::vec3 faceRotations[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, glm::radians(90.0f)),
			glm::vec3(0.0f, 0.0f, glm::radians(90.0f)),
			glm::vec3(glm::radians(90.0f), 0.0f, 0.0f),
			glm::vec3(glm::radians(90.0f), 0.0f, 0.0f)
		};
	}
	glm::vec3 GetFacePosition(Side side)
	{
		return detail::positions[side];
	}
	glm::vec3 GetFaceRotation(Side side)
	{
		return detail::faceRotations[side];
	}

	glm::vec3 GetEdgePosition(Side side1, Side side2)
	{
		return detail::positions[side1] + detail::positions[side2];
	}

	glm::vec3 GetEdgeRotation(Side side1, Side side2)
	{
		if(side1 == Top || side1 == Bottom)
		{
			if (side2 == Left || side2 == Right)
				return glm::vec3(0, glm::radians(90.0f), 0);
		}
		else
			return glm::vec3(0, 0, glm::radians(90.0f));
		return glm::vec3(0, 0, 0);
	}
}
