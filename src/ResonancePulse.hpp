#pragma once

#include <SFML/Graphics.hpp>

class ResonancePulse
{
public:
    void trigger(sf::Vector2f origin);
    void update(float dt);

    bool isActive() const;
    float getCooldownRemaining() const;
    bool crossedDistance(float distance) const;
    bool crossedPoint(sf::Vector2f point) const;
    sf::Vector2f getOrigin() const;

    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f origin{0.f, 0.f};
    bool active = false;
    float radius = 0.f;
    float previousRadius = 0.f;
    float cooldown = 0.f;

    static constexpr float maxRadius = 480.f;
    static constexpr float speed = 700.f;
    static constexpr float cooldownDuration = 1.8f;
};
