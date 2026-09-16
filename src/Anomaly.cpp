#include "Anomaly.hpp"

#include <algorithm>
#include <cstdint>
#include <cmath>

namespace
{
    sf::Vector2f normalize(sf::Vector2f value)
    {
        const float length = std::sqrt(value.x * value.x + value.y * value.y);
        if (length < 0.001f)
            return {0.f, 0.f};
        return value / length;
    }
}

Anomaly::Anomaly(sf::Vector2f startPosition)
    : position(startPosition),
      homePosition(startPosition),
      pulseTarget(startPosition)
{
    core.setRadius(11.f);
    core.setOrigin({11.f, 11.f});
    core.setFillColor(sf::Color(245, 245, 255, 225));
    core.setOutlineThickness(2.f);
    core.setOutlineColor(sf::Color(100, 220, 255));

    halo.setRadius(28.f);
    halo.setOrigin({28.f, 28.f});
    halo.setFillColor(sf::Color(70, 210, 255, 24));
    halo.setOutlineThickness(2.f);
    halo.setOutlineColor(sf::Color(90, 220, 255, 70));
}

void Anomaly::update(
    float dt,
    sf::Vector2f playerPosition,
    bool pulseActive,
    sf::Vector2f pulseOrigin)
{
    revealedTime = std::max(0.f, revealedTime - dt);
    pulseAttraction = std::max(0.f, pulseAttraction - dt);
    driftTime += dt;

    if (pulseActive)
    {
        pulseTarget = pulseOrigin;
        pulseAttraction = 1.4f;
    }

    sf::Vector2f target = homePosition;
    float speed = 24.f;

    if (pulseAttraction > 0.f)
    {
        target = pulseTarget;
        speed = 150.f;
    }
    else
    {
        target = {
            homePosition.x + std::sin(driftTime * 0.7f) * 100.f,
            homePosition.y + std::cos(driftTime * 0.9f) * 70.f
        };
    }

    const sf::Vector2f direction = normalize(target - position);
    position += direction * speed * dt;

    // Чем ближе игрок к аномалии, тем сильнее она тянется к нему.
    // Она не наносит физического урона, а создаёт помехи.
    const float playerDistance = distanceTo(playerPosition);
    if (playerDistance < 180.f && pulseAttraction <= 0.f)
    {
        const sf::Vector2f playerDirection = normalize(playerPosition - position);
        const float chaseStrength = (180.f - playerDistance) / 180.f;
        position += playerDirection * (35.f * chaseStrength) * dt;
    }

    core.setPosition(position);
    halo.setPosition(position);
}

void Anomaly::reveal(float seconds)
{
    revealedTime = std::max(revealedTime, seconds);
}

void Anomaly::draw(sf::RenderWindow& window) const
{
    if (revealedTime <= 0.f)
        return;

    const float alphaFactor = std::clamp(revealedTime / 1.8f, 0.f, 1.f);
    const auto alpha = static_cast<std::uint8_t>(40.f + 130.f * alphaFactor);

    sf::CircleShape outer = halo;
    outer.setFillColor(sf::Color(70, 210, 255, static_cast<std::uint8_t>(20.f + 45.f * alphaFactor)));
    outer.setOutlineColor(sf::Color(90, 220, 255, alpha));
    window.draw(outer);

    sf::CircleShape inner = core;
    inner.setFillColor(sf::Color(245, 245, 255, alpha));
    inner.setOutlineColor(sf::Color(100, 220, 255, alpha));
    window.draw(inner);
}

float Anomaly::distanceTo(sf::Vector2f point) const
{
    const float dx = point.x - position.x;
    const float dy = point.y - position.y;
    return std::sqrt(dx * dx + dy * dy);
}

float Anomaly::getThreatLevel(sf::Vector2f point) const
{
    const float distance = distanceTo(point);
    if (distance >= 220.f)
        return 0.f;
    return std::clamp((220.f - distance) / 220.f, 0.f, 1.f);
}

bool Anomaly::isRevealed() const
{
    return revealedTime > 0.f;
}

sf::Vector2f Anomaly::getPosition() const
{
    return position;
}
