#include "MaterialInstances.h"

namespace materials
{
	namespace edges
	{
		extern Material normal(glm::vec3(0.2f, 1.0f, 0.5f), 1.0f, 0.0f),
			hover(glm::vec3(0.5f, 0.2f, 1.0f), 1.0f, 0.0f),
			locked(glm::vec3(0.2f, 0.5f, 1.0f), 1.0f, 0.0f);
	}
	namespace faces
	{
		extern Material normal(glm::vec3(1.0f, 0.5f, 0.2f), 0.5f, 0.2f);
	}
}
