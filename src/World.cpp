#include "World.hpp"

World::World()
{
    // Внешние границы
    createWall(0.f, 0.f, 1280.f, 30.f);
    createWall(0.f, 690.f, 1280.f, 30.f);
    createWall(0.f, 0.f, 30.f, 720.f);
    createWall(1250.f, 0.f, 30.f, 720.f);

    // Верхняя комната. В правой стене оставлен проём двери y=200..300.
    createWall(250.f, 120.f, 500.f, 30.f);
    createWall(250.f, 120.f, 30.f, 220.f);
    createWall(750.f, 120.f, 30.f, 80.f);
    createWall(750.f, 300.f, 30.f, 40.f);

    // Нижняя часть
    createWall(450.f, 340.f, 30.f, 220.f);
    createWall(800.f, 400.f, 300.f, 30.f);

    // Комната за дверью
    createWall(1020.f, 120.f, 30.f, 220.f);
    createWall(780.f, 120.f, 240.f, 30.f);
}

const std::vector<Wall>& World::getWalls() const
{
    return walls;
}

void World::createWall(
    float x,
    float y,
    float width,
    float height)
{
    Wall wall;
    wall.shape.setSize({width, height});
    wall.shape.setPosition({x, y});
    wall.shape.setFillColor(sf::Color(45, 50, 58));
    wall.shape.setOutlineThickness(2.f);
    wall.shape.setOutlineColor(sf::Color(75, 85, 95));
    walls.push_back(wall);
}

void World::drawFloor(
    sf::RenderWindow& window,
    sf::Vector2f playerPosition) const
{
    sf::RectangleShape floor;
    floor.setSize({2000.f, 2000.f});
    floor.setOrigin({1000.f, 1000.f});
    floor.setPosition(playerPosition);
    floor.setFillColor(sf::Color(18, 22, 27));
    window.draw(floor);
}

void World::drawGrid(sf::RenderWindow& window) const
{
    constexpr float gridSize = 40.f;
    constexpr float worldSize = 1280.f;

    sf::VertexArray lines(sf::PrimitiveType::Lines);

    for (float x = 0.f; x <= worldSize; x += gridSize)
    {
        sf::Vertex v1;
        v1.position = {x, 0.f};
        v1.color = sf::Color(30, 35, 40);

        sf::Vertex v2;
        v2.position = {x, worldSize};
        v2.color = sf::Color(30, 35, 40);

        lines.append(v1);
        lines.append(v2);
    }

    for (float y = 0.f; y <= worldSize; y += gridSize)
    {
        sf::Vertex v1;
        v1.position = {0.f, y};
        v1.color = sf::Color(30, 35, 40);

        sf::Vertex v2;
        v2.position = {worldSize, y};
        v2.color = sf::Color(30, 35, 40);

        lines.append(v1);
        lines.append(v2);
    }

    window.draw(lines);

    for (const Wall& wall : walls)
        window.draw(wall.shape);
}

void drawLight(
    sf::RenderWindow& window,
    sf::Vector2f position)
{
    sf::CircleShape outer(260.f);
    outer.setOrigin({260.f, 260.f});
    outer.setPosition(position);
    outer.setFillColor(sf::Color(50, 180, 255, 12));
    window.draw(outer);

    sf::CircleShape middle(180.f);
    middle.setOrigin({180.f, 180.f});
    middle.setPosition(position);
    middle.setFillColor(sf::Color(50, 180, 255, 18));
    window.draw(middle);

    sf::CircleShape inner(100.f);
    inner.setOrigin({100.f, 100.f});
    inner.setPosition(position);
    inner.setFillColor(sf::Color(80, 200, 255, 22));
    window.draw(inner);
}
