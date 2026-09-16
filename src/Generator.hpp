#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.hpp"


class Generator : public Interactable
{
public:
    explicit Generator(sf::Vector2f position);

    void interact();
    float distanceTo(sf::Vector2f point) const;
    bool isPowered() const;

    void draw(sf::RenderWindow& window) const;

private:
    void updateAppearance();

    sf::Vector2f position;
    bool powered = false;
    sf::RectangleShape body;
    sf::CircleShape lamp;

    std::string getHint() const override
    {
        if (powered)
            return "Generator: ONLINE";

        return "[E] Turn on generator";
    }
};
