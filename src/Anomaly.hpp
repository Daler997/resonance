#pragma once

#include <SFML/Graphics.hpp>

class Anomaly
{
public:
    explicit Anomaly(sf::Vector2f startPosition);

    void update(float dt, sf::Vector2f playerPosition, bool pulseActive, sf::Vector2f pulseOrigin);
    void reveal(float seconds = 1.8f);
    void draw(sf::RenderWindow& window) const;

    float distanceTo(sf::Vector2f point) const;
    float getThreatLevel(sf::Vector2f point) const;
    bool isRevealed() const;
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f position;
    sf::Vector2f homePosition;
    sf::Vector2f pulseTarget;
    sf::CircleShape core;
    sf::CircleShape halo;

    float revealedTime = 0.f;
    float pulseAttraction = 0.f;
    float driftTime = 0.f;
};
