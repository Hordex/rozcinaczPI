#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "GLShader.h"
#include <glm/glm.hpp>
#include "Plane.h"
#define M_PI 3.1415926535897932384626433832795
#include "Camera.h"

bool handleEvents(sf::Window& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
			return false;
		case sf::Event::Resized:
			glViewport(0, 0, event.size.width, event.size.height);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			return false;
			//case sf::Event::LostFocus: break;
			//case sf::Event::GainedFocus: break;
			//case sf::Event::TextEntered: break;
			//case sf::Event::KeyReleased: break;
			//case sf::Event::MouseWheelMoved: break;
			//case sf::Event::MouseWheelScrolled: break;
			//case sf::Event::MouseButtonPressed: break;
			//case sf::Event::MouseButtonReleased: break;
			//case sf::Event::MouseMoved: break;
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

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32,0,16));
	window.setVerticalSyncEnabled(true);

	//Initialize Glew
	glewExperimental = GL_TRUE;
	glewInit();

	// load resources, initialize the OpenGL states, ...
	GLuint program = LoadShader("test.vert", "test.frag");
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Plane fig1 = Plane();
	fig1.setRotation(glm::vec3(glm::radians(20.0), glm::radians(20.0), glm::radians(20.0)));
	Camera cam = Camera(75, 800, 600, 0.1f, 1000);
	cam.moveBy(glm::vec3(-1, -2, -3));
	cam.lookAt(glm::vec3(0, 0, 0));

	// run the main loop
	while (window.isOpen() && handleEvents(window))
	{
		// handle events

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// draw...

		glUseProgram(program);
		GLint worldmatrixLocation = glGetUniformLocation(program, "viewProjectionMatrix");
		glUniformMatrix4fv(worldmatrixLocation, 1, GL_FALSE, &(cam.getViewProjectionMatrix()[0][0]));

		fig1.render(program);

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}