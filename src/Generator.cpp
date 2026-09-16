#include "Generator.hpp"

#include <cmath>

Generator::Generator(sf::Vector2f position)
    : position(position)
{
    body.setSize({50.f, 70.f});
    body.setOrigin({25.f, 35.f});
    body.setPosition(position);
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color(120, 130, 140));

    lamp.setRadius(8.f);
    lamp.setOrigin({8.f, 8.f});
    lamp.setPosition({position.x, position.y - 20.f});

    updateAppearance();
}

void Generator::interact()
{
    powered = !powered;
    updateAppearance();
}

float Generator::distanceTo(sf::Vector2f point) const
{
    const float dx = point.x - position.x;
    const float dy = point.y - position.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Generator::isPowered() const
{
    return powered;
}

void Generator::draw(sf::RenderWindow& window) const
{
    window.draw(body);
    window.draw(lamp);
}

void Generator::updateAppearance()
{
    if (powered)
    {
        body.setFillColor(sf::Color(60, 95, 80));
        lamp.setFillColor(sf::Color(80, 255, 120));
    }
    else
    {
        body.setFillColor(sf::Color(70, 75, 82));
        lamp.setFillColor(sf::Color(255, 90, 50));
    }
}
