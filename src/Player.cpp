#include "Player.hpp"

#include "Door.hpp"
#include "World.hpp"

#include <algorithm>
#include <cmath>

Player::Player(sf::Vector2f startPosition)
    : position(startPosition)
{
    shape.setRadius(18.f);
    shape.setOrigin({18.f, 18.f});
    shape.setFillColor(sf::Color(80, 210, 255));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);
    shape.setPosition(position);
}

void Player::update(
    float dt,
    const std::vector<Wall>& walls,
    const Door& door
)
{
    sf::Vector2f direction{0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        direction.x += 1.f;

    const float length = std::sqrt(
        direction.x * direction.x +
        direction.y * direction.y
    );

    if (length > 0.f)
        direction /= length;

    const sf::Vector2f movement = direction * speed * dt;

    sf::Vector2f testPosition = position;
    testPosition.x += movement.x;

    if (!collides(testPosition, walls, door))
        position.x = testPosition.x;

    testPosition = position;
    testPosition.y += movement.y;

    if (!collides(testPosition, walls, door))
        position.y = testPosition.y;

    shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return position;
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

bool Player::collides(
    sf::Vector2f testPosition,
    const std::vector<Wall>& walls,
    const Door& door
) const
{
    constexpr float radius = 18.f;

    for (const Wall& wall : walls)
    {
        if (circleIntersectsRect(
                testPosition,
                radius,
                wall.shape.getGlobalBounds()))
        {
            return true;
        }
    }

    if (door.isBlocking())
    {
        if (circleIntersectsRect(
                testPosition,
                radius,
                door.getCollisionBounds()))
        {
            return true;
        }
    }

    return false;
}

bool Player::circleIntersectsRect(
    sf::Vector2f circlePosition,
    float radius,
    sf::FloatRect rect
)
{
    const float closestX = std::clamp(
        circlePosition.x,
        rect.position.x,
        rect.position.x + rect.size.x
    );

    const float closestY = std::clamp(
        circlePosition.y,
        rect.position.y,
        rect.position.y + rect.size.y
    );

    const float dx = circlePosition.x - closestX;
    const float dy = circlePosition.y - closestY;

    return dx * dx + dy * dy < radius * radius;
}
