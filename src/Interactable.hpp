#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class Interactable
{

public:

    virtual ~Interactable() = default;


    virtual float distanceTo(
        sf::Vector2f position
    ) const = 0;


    virtual void interact() = 0;


    virtual std::string getHint() const = 0;


    virtual void draw(
        sf::RenderWindow& window
    ) const = 0;

};