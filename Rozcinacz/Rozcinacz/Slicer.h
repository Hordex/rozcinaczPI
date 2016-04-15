#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include "math.h"
#include "Camera.h"

class Slicer
{
	bool eventHandler(); 
	sf::Window* window;
	bool mouseDown = false, newCam = false, newAspectRatio = false;
	int lastPos[2];
	float r = 2.0f;
	int width = 800;
	int height = 600;
	float pa = M_PI/2.0f, aa = 0;
	glm::vec3 calculateCameraPosition();
public:
	Slicer();
	~Slicer();
};

