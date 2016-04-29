#include "stdafx.h"
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#define MAXRADIUS 5.0f
#define MINRADIUS 3.0f
#define MAGICNUMBERS ((MAXRADIUS + 1.0f) / ((float)width) / (MAXRADIUS + 1.0f - r))
#include "Slicer.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "Graph.h"

bool Slicer::eventHandler()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			return false;
		case sf::Event::Resized:
			width = event.size.width;
			height = event.size.height;
			glViewport(0, 0, width, height);
			newAspectRatio = true;
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window->close();
			return false;
			//case sf::Event::LostFocus: break;
			//case sf::Event::GainedFocus: break;
			//case sf::Event::TextEntered: break;
			//case sf::Event::KeyReleased: break;
		case sf::Event::MouseWheelMoved:
			r = std::max(MINRADIUS, std::min(MAXRADIUS, r + 0.1f * -event.mouseWheel.delta));
			newCam = true;
			break;
			//case sf::Event::MouseWheelScrolled: break;
		case sf::Event::MouseButtonPressed:
			mouseDown = true;
			lastPos[0] = event.mouseButton.x;
			lastPos[1] = event.mouseButton.y;
			break;
		case sf::Event::MouseButtonReleased:
			mouseDown = false;
			break;
		case sf::Event::MouseMoved:
			if (mouseDown)
			{
				int dx = (lastPos[0] - event.mouseMove.x),
					dy = (lastPos[1] - event.mouseMove.y);
				float magic = MAGICNUMBERS;
				aa += dx * magic;
				pa += dy * magic;
				pa = std::max(0.0001f, std::min(pa, (float)M_PI - 0.0001f));
				newCam = true;

				lastPos[0] = event.mouseMove.x;
				lastPos[1] = event.mouseMove.y;
			}
			break;
			//case sf::Event::MouseEntered: break;
			//case sf::Event::MouseLeft: break;
			//case sf::Event::JoystickButtonPressed: break;
			//case sf::Event::JoystickButtonReleased: break;
			//case sf::Event::JoystickMoved: break;
			//case sf::Event::JoystickConnected: break;
			//case sf::Event::JoystickDisconnected: break;
			//case sf::Event::TouchBegan: break;
			//case sf::Event::TouchMoved: break;
			//case sf::Event::TouchEnded: break;
			//case sf::Event::SensorChanged: break;
			//case sf::Event::Count: break;
		default:
			break;
		}
	}
	return true;
}

void Slicer::calculateCameraPosition(class Camera& camera) const
{
	glm::vec3 ret;

	ret.z = r * sin(pa) * cos(aa);
	ret.x = r * sin(pa) * sin(aa);
	ret.y = r * cos(pa);

	camera.moveTo(ret);
}

Slicer::Slicer()
{
	// create the window
	window = new sf::Window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(32, 0, 16));
	window->setVerticalSyncEnabled(true);
	r = MINRADIUS;
	Renderer renderer;

	Graph graph(6);
	Scene scene(graph);

	Camera cam(75.0f, (float)width, (float)height, 0.1f, 1000.0f);
	calculateCameraPosition(cam);
	cam.lookAt(glm::vec3(0, 0, 0));
	cam.setLookAtLock(true);

	// run the main loop
	while (window->isOpen() && eventHandler())
	{
		// handle events
		if (newCam)
		{
			calculateCameraPosition(cam);
			newCam = false;
		}
		if(newAspectRatio)
		{
			cam.perspective(75.0f, (float)width, (float)height, 0.1f, 1000.0f);
			newAspectRatio = false;
		}

		// clear the buffers
		
		renderer.render(scene, cam);

		// end the current frame (internally swaps the front and back buffers)
		window->display();
	}

	// release resources...

}


Slicer::~Slicer()
{
	delete window;
}
