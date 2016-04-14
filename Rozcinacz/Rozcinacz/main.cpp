#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>


void handleEvents(sf::Window& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			glViewport(0, 0, event.size.width, event.size.height);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;
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
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	//Initialize Glew
	glewExperimental = GL_TRUE;
	glewInit();
	// load resources, initialize the OpenGL states, ...
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	sf::Shader shader;
	shader.loadFromFile("test.vert","test.frag");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		handleEvents(window);

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...

		sf::Shader::bind(&shader);

		sf::Shader::bind(nullptr);

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}