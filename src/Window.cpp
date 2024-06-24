#include "Window.h"

Window::Window(const std::string& windowName) : window({ 1920, 1080 }, windowName, sf::Style::Titlebar)
{
	// Allows a player to sync the frame rate of the game to the refresh rate of the monitor.
	window.setVerticalSyncEnabled(true);
}

void Window::Update()
{

	/*******************************************************************************************************************
	*   sf::Event class is a union so only one of its members is valid at one time. As all members share the same      *
	*     memory space, we need to test the event type to make sure we do not attempt to access invalid memory.        *
	*******************************************************************************************************************/
	sf::Event event{};

	// Returns true if an event has occurred and fills the event with the relevant data
	if (window.pollEvent(event))
	{
		// Allows the player to quit the game with cmd-q on Mac and alt-f4 on Windows and Linux.
		if (event.type == sf::Event::Closed) { window.close(); }
	}
}

// Clears the screen to a uniform colour(to remove previous frames).
void Window::BeginDraw() { window.clear(sf::Color::White); }
void Window::Draw(const sf::Drawable& drawable) { window.draw(drawable); }
void Window::EndDraw() { window.display(); }
bool Window::IsOpen() const { return window.isOpen(); }
void Window::Draw(const sf::Vertex *vertices, std::size_t vertexCount, sf::PrimitiveType type) { window.draw(vertices, vertexCount, type); }
void Window::SetView(const sf::View &view) { window.setView(view); }
const sf::View &Window::GetView() const { return window.getView(); }

sf::Vector2u Window::GetCenter() const
{
    sf::Vector2u size = window.getSize();
    return { (size.x / 2), (size.y / 2) };
}

sf::FloatRect Window::GetViewSpace() const {
    const sf::View& view = GetView();
    const sf::Vector2f& viewCenter = view.getCenter();
    const sf::Vector2f& viewSize = view.getSize();
    sf::Vector2f viewSizeHalf(viewSize.x * 0.5f, viewSize.y * 0.5f);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    return viewSpace;
}



