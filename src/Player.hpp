#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Wall;
class Door;

class Player
{
public:
    explicit Player(sf::Vector2f startPosition);

    void update(
        float dt,
        const std::vector<Wall>& walls,
        const Door& door
    );

    sf::Vector2f getPosition() const;
    void draw(sf::RenderWindow& window) const;

private:
    bool collides(
        sf::Vector2f position,
        const std::vector<Wall>& walls,
        const Door& door
    ) const;

    static bool circleIntersectsRect(
        sf::Vector2f circlePosition,
        float radius,
        sf::FloatRect rect
    );

    sf::Vector2f position;
    float speed = 280.f;
    sf::CircleShape shape;
};
