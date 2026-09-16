#include "Terminal.hpp"

#include <cmath>

Terminal::Terminal(sf::Vector2f position)
    : position(position)
{
    body.setSize({45.f, 55.f});
    body.setOrigin({22.5f, 27.5f});
    body.setPosition(position);
    body.setFillColor(sf::Color(45, 50, 58));
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color(100, 110, 120));

    screen.setSize({28.f, 18.f});
    screen.setOrigin({14.f, 9.f});
    screen.setPosition({position.x, position.y - 8.f});
    screen.setFillColor(sf::Color(50, 150, 210));
}

void Terminal::interact()
{
    active = !active;
    screen.setFillColor(
        active ? sf::Color(80, 255, 120)
               : sf::Color(50, 150, 210));
}

float Terminal::distanceTo(sf::Vector2f point) const
{
    const float dx = point.x - position.x;
    const float dy = point.y - position.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Terminal::draw(sf::RenderWindow& window) const
{
    window.draw(body);
    window.draw(screen);
}
