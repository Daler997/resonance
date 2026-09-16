#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Interactable.hpp"
#include "Inventory.hpp"


class Keycard : public Interactable
{

private:

    sf::Vector2f position;

    bool collected = false;

    sf::RectangleShape shape;

    Inventory* inventory;


public:


    Keycard(
        sf::Vector2f pos,
        Inventory& inv
    )
        :
        position(pos),
        inventory(&inv)
    {

        shape.setSize(
            {30.f,18.f}
        );

        shape.setOrigin(
            {15.f,9.f}
        );

        shape.setPosition(
            position
        );

        shape.setFillColor(
            sf::Color::Yellow
        );

        shape.setOutlineThickness(
            2.f
        );

        shape.setOutlineColor(
            sf::Color::White
        );
    }



    float distanceTo(
        sf::Vector2f player
    ) const override
    {

        float dx =
            player.x-position.x;

        float dy =
            player.y-position.y;


        return std::sqrt(
            dx*dx+dy*dy
        );
    }



    void interact() override
    {

        if(!collected)
        {
            collected = true;

            inventory->addKeycard();
        }

    }



    bool isCollected() const
    {
        return collected;
    }



    void draw(
        sf::RenderWindow& window
    ) const override
    {

        if(!collected)
            window.draw(shape);

    }



    std::string getHint() const override
    {
        if(collected)
            return "";

        return "[E] Pick up keycard";
    }

};