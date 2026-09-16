#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Wall
{
    sf::RectangleShape shape;
};

class World
{
public:
    World();

    const std::vector<Wall>& getWalls() const;

    void drawFloor(sf::RenderWindow& window, sf::Vector2f playerPosition) const;
    void drawGrid(sf::RenderWindow& window) const;

private:
    void createWall(float x, float y, float width, float height);

    std::vector<Wall> walls;
};

void drawLight(sf::RenderWindow& window, sf::Vector2f position);
