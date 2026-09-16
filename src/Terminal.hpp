#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.hpp"


class Terminal : public Interactable
{
public:
    explicit Terminal(sf::Vector2f position);

    void interact();
    float distanceTo(sf::Vector2f point) const;

    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f position;
    bool active = false;
    sf::RectangleShape body;
    sf::RectangleShape screen;
    
    std::string getHint() const override
    {
        return "[E] Access terminal";
    }
};
