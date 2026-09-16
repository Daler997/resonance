#include "ResonancePulse.hpp"

#include <algorithm>
#include <cmath>

void ResonancePulse::trigger(sf::Vector2f newOrigin)
{
    if (cooldown > 0.f)
        return;

    origin = newOrigin;
    radius = 0.f;
    previousRadius = 0.f;
    active = true;
    cooldown = cooldownDuration;
}

void ResonancePulse::update(float dt)
{
    cooldown = std::max(0.f, cooldown - dt);

    if (!active)
        return;

    previousRadius = radius;
    radius += speed * dt;

    if (radius >= maxRadius)
    {
        radius = maxRadius;
        active = false;
    }
}

bool ResonancePulse::isActive() const
{
    return active;
}

float ResonancePulse::getCooldownRemaining() const
{
    return cooldown;
}

bool ResonancePulse::crossedDistance(float distance) const
{
    return active && distance >= previousRadius && distance <= radius;
}

bool ResonancePulse::crossedPoint(sf::Vector2f point) const
{
    const float dx = point.x - origin.x;
    const float dy = point.y - origin.y;
    const float distance = std::sqrt(dx * dx + dy * dy);
    return crossedDistance(distance);
}

sf::Vector2f ResonancePulse::getOrigin() const
{
    return origin;
}

void ResonancePulse::draw(sf::RenderWindow& window) const
{
    if (!active)
        return;

    sf::CircleShape ring(radius);
    ring.setOrigin({radius, radius});
    ring.setPosition(origin);
    ring.setFillColor(sf::Color::Transparent);
    ring.setOutlineThickness(4.f);
    ring.setOutlineColor(sf::Color(80, 220, 255, 190));
    window.draw(ring);

    if (radius > 18.f)
    {
        sf::CircleShape inner(radius - 18.f);
        inner.setOrigin({radius - 18.f, radius - 18.f});
        inner.setPosition(origin);
        inner.setFillColor(sf::Color::Transparent);
        inner.setOutlineThickness(2.f);
        inner.setOutlineColor(sf::Color(80, 220, 255, 70));
        window.draw(inner);
    }
}
