#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include "math.h"
#include "Camera.h"

/// <summary>
/// 
/// </summary>
class Slicer
{
	/// <summary>
	/// Events the handler.
	/// </summary>
	/// <returns></returns>
	bool eventHandler();
	/// <summary>
	/// The window
	/// </summary>
	sf::Window* window;
	/// <summary>
	/// The mouse down
	/// </summary>
	bool mouseDown = false;
	/// <summary>
	/// The new cam
	/// </summary>
	bool newCam = false;
	/// <summary>
	/// The new aspect ratio
	/// </summary>
	bool newAspectRatio = false;
	/// <summary>
	/// The last position
	/// </summary>
	int lastPos[2];
	/// <summary>
	/// The radius
	/// </summary>
	float r = 2.0f;
	/// <summary>
	/// The width
	/// </summary>
	int width = 800;
	/// <summary>
	/// The height
	/// </summary>
	int height = 600;
	/// <summary>
	/// The pa
	/// </summary>
	float pa = M_PI / 2.0f;
	/// <summary>
	/// The aa
	/// </summary>
	float aa = 0;
	/// <summary>
	/// Calculates the camera position.
	/// </summary>
	/// <returns></returns>
	glm::vec3 calculateCameraPosition();
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Slicer"/> class.
	/// </summary>
	Slicer();
	/// <summary>
	/// Finalizes an instance of the <see cref="Slicer"/> class.
	/// </summary>
	~Slicer();
};

