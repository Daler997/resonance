#pragma once

#include <SFML/Graphics.hpp>

class Door
{
public:
    explicit Door(sf::Vector2f position);

    void setPowered(bool powered);
    void update(float dt, sf::Vector2f playerPosition);

    bool isFullyOpen() const;
    bool isBlocking() const;

    sf::FloatRect getCollisionBounds() const;
    float distanceTo(sf::Vector2f point) const;

    void draw(sf::RenderWindow& window) const;

private:
    void updateAppearance();
    bool playerIsTooCloseToClose(sf::Vector2f playerPosition) const;

    sf::Vector2f position;
    sf::RectangleShape shape;
    bool powered = false;
    float openAmount = 0.f;
};
