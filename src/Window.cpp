#include "Window.h"

Window::Window(const std::string& windowName) : window(sf::VideoMode(800, 600), windowName, sf::Style::Titlebar) 
{
	// Allows a player to sync the frame rate of the game to the refresh rate of the monitor.
	window.setVerticalSyncEnabled(true);
}

void Window::Update()
{
	sf::Event event;

	// Returns true if an event has occurred and fills the event with the relevant data
	if (window.pollEvent(event))
	{
		// Allows the player to quit the game with cmd-q on Mac and alt-f4 on Windows and Linux.
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Window::BeginDraw()
{
	// Clears the screen to a uniform colour(to remove previous frames).
	window.clear(sf::Color::White);
}

void Window::Draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Window::EndDraw()
{
	window.display();
}

bool Window::IsOpen() const
{
	return window.isOpen();
}


Window::~Window() 
{

};

