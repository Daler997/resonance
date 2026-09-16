#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Interactable.hpp"
#include "Inventory.hpp"

class EchoNode : public Interactable
{
public:
    EchoNode(sf::Vector2f position, Inventory& inventory)
        : position(position), inventory(inventory)
    {
        shape.setRadius(13.f);
        shape.setOrigin({13.f, 13.f});
        shape.setPosition(position);
        shape.setFillColor(sf::Color(70, 220, 255, 180));
        shape.setOutlineThickness(3.f);
        shape.setOutlineColor(sf::Color(180, 250, 255));
    }

    void update(float dt)
    {
        if (revealedTime > 0.f)
        {
            revealedTime -= dt;
            if (revealedTime < 0.f)
                revealedTime = 0.f;
        }
    }

    void reveal(float seconds = 3.5f)
    {
        if (!collected)
            revealedTime = seconds;
    }

    float distanceTo(sf::Vector2f player) const override
    {
        const float dx = player.x - position.x;
        const float dy = player.y - position.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void interact() override
    {
        if (!isInteractable())
            return;

        collected = true;
        inventory.addEchoShard();
    }

    std::string getHint() const override
    {
        return isInteractable() ? "[E] Stabilize echo shard" : "";
    }

    void draw(sf::RenderWindow& window) const override
    {
        if (collected || revealedTime <= 0.f)
            return;

        window.draw(shape);
    }

    bool isInteractable() const override
    {
        return !collected && revealedTime > 0.f;
    }

    bool isCollected() const
    {
        return collected;
    }

    sf::Vector2f getPosition() const
    {
        return position;
    }

private:
    sf::Vector2f position;
    Inventory& inventory;
    bool collected = false;
    float revealedTime = 0.f;
    sf::CircleShape shape;
};
