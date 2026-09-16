#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Interactable.hpp"

class Terminal : public Interactable
{
public:
    explicit Terminal(sf::Vector2f position);

    void interact() override;
    float distanceTo(sf::Vector2f point) const override;
    std::string getHint() const override;
    void draw(sf::RenderWindow& window) const override;

    void setObjectiveComplete(bool complete);
    bool isCompleted() const;

private:
    sf::Vector2f position;
    bool active = false;
    bool objectiveComplete = false;
    sf::RectangleShape body;
    sf::RectangleShape screen;
};
