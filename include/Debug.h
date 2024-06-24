#ifndef Debug_h
#define Debug_h

#include <array>
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Input.h"

 #define DEBUG_LINES
 #define DEBUG

class Debug {

public:

    static void Draw(Window& window)
    {
        for(auto& r : rects)
        {
            window.Draw(r);
        }
        rects.clear();

        for(auto& l : lines)
        {
            sf::Vertex line[2] = {l.at(0), l.at(1) };
            window.Draw(line , 2, sf::Lines);
        }
        lines.clear();
    };

    static void DrawRect(const sf::FloatRect& rect, sf::Color color = sf::Color::White){
        sf::Vector2f size(rect.width, rect.height);
        sf::Vector2f pos(rect.left, rect.top);
        sf::RectangleShape shape(size);
        shape.setPosition(pos);
        shape.setOutlineColor(color);
        shape.setOutlineThickness(3.f);
        shape.setFillColor(sf::Color::Transparent);
        rects.push_back(shape);
    };

    [[maybe_unused]] static void DrawLine(const sf::Vector2f& from, const sf::Vector2f& to, sf::Color color = sf::Color::White)
    {
        lines.push_back({sf::Vertex(from, color), sf::Vertex(to, color)});
    };

    [[maybe_unused]] static void Log(const std::string& msg){ std::cout << msg << std::endl; };
    [[maybe_unused]] static void LogWarning(const std::string& msg) { std::cout << "WARNING: " << msg << std::endl; };
    [[maybe_unused]] static void LogError(const std::string& msg){ std::cout << "DEBUG: " << msg << std::endl; };

    static void HandleCameraZoom(Window& window, Input& input){

        if(input.IsKeyUp(Input::Key::LBracket)){
            sf::View view = window.GetView();
            view.zoom(1.1f);
            window.SetView(view);
        }
        else if(input.IsKeyUp(Input::Key::RBracket)){
            sf::View view = window.GetView();
            view.zoom(0.9f);
            window.SetView(view);
        }
    }

private:

    static std::vector<std::array<sf::Vertex, 2>> lines;
    static std::vector<sf::RectangleShape> rects;

};

#endif // Debug_h
