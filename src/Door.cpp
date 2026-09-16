#include "Door.hpp"
#include <algorithm>

#include <cmath>

Door::Door(sf::Vector2f position)
    : position(position)
{
    shape.setSize({30.f, 100.f});
    shape.setOrigin({15.f, 50.f});
    shape.setPosition(position);
    shape.setOutlineThickness(2.f);
    updateAppearance();
}

void Door::setPowered(bool value)
{
    powered = value;
}

void Door::update(float dt, sf::Vector2f playerPosition)
{
    // Открывается сразу после подачи питания.
    if (powered)
    {
        openAmount += dt * 2.5f;
    }
    else
    {
        // Ключевой фикс: дверь НЕ закрывается через игрока.
        // Пока игрок находится в проходе, она ждёт.
        if (!playerIsTooCloseToClose(playerPosition))
            openAmount -= dt * 2.5f;
    }

    openAmount = std::clamp(openAmount, 0.f, 1.f);

    shape.setPosition({
        position.x,
        position.y - 100.f * openAmount
    });

    updateAppearance();
}

bool Door::isFullyOpen() const
{
    return openAmount >= 0.99f;
}

bool Door::isBlocking() const
{
    return openAmount < 0.99f;
}

sf::FloatRect Door::getCollisionBounds() const
{
    return shape.getGlobalBounds();
}

float Door::distanceTo(sf::Vector2f point) const
{
    const float dx = point.x - position.x;
    const float dy = point.y - position.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Door::draw(sf::RenderWindow& window) const
{
    if (openAmount < 0.999f)
        window.draw(shape);
}

bool Door::playerIsTooCloseToClose(sf::Vector2f playerPosition) const
{
    // Оставляем проход открытым, пока игрок находится возле него.
    constexpr float safeDistance = 85.f;
    return distanceTo(playerPosition) < safeDistance;
}

void Door::updateAppearance()
{
    if (powered)
    {
        shape.setFillColor(sf::Color(40, 110, 70));
        shape.setOutlineColor(sf::Color(80, 255, 120));
    }
    else
    {
        shape.setFillColor(sf::Color(130, 45, 45));
        shape.setOutlineColor(sf::Color(220, 80, 80));
    }
}
