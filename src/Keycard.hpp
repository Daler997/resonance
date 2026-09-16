#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Interactable.hpp"
#include "Inventory.hpp"

class Keycard : public Interactable
{
public:
    Keycard(sf::Vector2f position, Inventory& inventory)
        : position(position), inventory(inventory)
    {
        shape.setSize({30.f, 18.f});
        shape.setOrigin({15.f, 9.f});
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Yellow);
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color::White);
    }

    float distanceTo(sf::Vector2f player) const override
    {
        const float dx = player.x - position.x;
        const float dy = player.y - position.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void interact() override
    {
        if (collected)
            return;

        collected = true;
        inventory.addKeycard();
    }

    std::string getHint() const override
    {
        return collected ? "" : "[E] Pick up access card";
    }

    void draw(sf::RenderWindow& window) const override
    {
        if (!collected)
            window.draw(shape);
    }

    bool isInteractable() const override
    {
        return !collected;
    }

private:
    sf::Vector2f position;
    Inventory& inventory;
    bool collected = false;
    sf::RectangleShape shape;
};
