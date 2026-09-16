#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstdint>
#include <array>
#include <optional>
#include <string>
#include <vector>

#include "Anomaly.hpp"
#include "Door.hpp"
#include "EchoNode.hpp"
#include "Generator.hpp"
#include "HUD.hpp"
#include "InteractionManager.hpp"
#include "Inventory.hpp"
#include "Keycard.hpp"
#include "Player.hpp"
#include "ResonancePulse.hpp"
#include "Terminal.hpp"
#include "World.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "RESONANCE"
    );

    window.setFramerateLimit(144);

    sf::View camera(
        sf::FloatRect({0.f, 0.f}, {1280.f, 720.f})
    );

    World world;
    Player player({640.f, 360.f});
    Inventory inventory;
    HUD hud;

    Generator generator({920.f, 250.f});
    Door door({765.f, 250.f});
    Terminal terminal({850.f, 340.f});
    Keycard keycard({600.f, 200.f}, inventory);

    std::array<EchoNode, 3> echoes{
        EchoNode({335.f, 235.f}, inventory),
        EchoNode({930.f, 190.f}, inventory),
        EchoNode({1110.f, 540.f}, inventory)
    };

    ResonancePulse pulse;
    Anomaly anomaly({1090.f, 240.f});

    std::vector<Interactable*> objects;
    objects.push_back(&generator);
    objects.push_back(&terminal);
    objects.push_back(&keycard);

    for (EchoNode& echo : echoes)
        objects.push_back(&echo);

    bool gameComplete = false;
    float completionTimer = 0.f;

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();

                if (key->scancode == sf::Keyboard::Scancode::E && !gameComplete)
                {
                    if (Interactable* object = InteractionManager::find(
                            objects,
                            player.getPosition()))
                    {
                        object->interact();
                    }
                }

                if (key->scancode == sf::Keyboard::Scancode::Space && !gameComplete)
                {
                    pulse.trigger(player.getPosition());
                }
            }
        }

        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.05f);

        if (!gameComplete)
        {
            pulse.update(dt);
            anomaly.update(
                dt,
                player.getPosition(),
                pulse.isActive(),
                pulse.getOrigin()
            );

            if (pulse.crossedPoint(anomaly.getPosition()))
                anomaly.reveal(2.5f);

            for (EchoNode& echo : echoes)
            {
                echo.update(dt);
                if (pulse.crossedPoint(echo.getPosition()))
                    echo.reveal();
            }

            door.setPowered(
                generator.isPowered() && inventory.hasKeycard()
            );

            door.update(dt, player.getPosition());

            player.update(
                dt,
                world.getWalls(),
                door
            );

            const bool objectiveReady =
                inventory.hasKeycard() &&
                generator.isPowered() &&
                inventory.getEchoShards() >= 3;

            terminal.setObjectiveComplete(objectiveReady);

            Interactable* nearby = InteractionManager::find(
                objects,
                player.getPosition()
            );

            std::string hint;

            if (nearby)
            {
                hint = nearby->getHint();
            }
            else if (!inventory.hasKeycard())
            {
                hint = "Find the yellow access card";
            }
            else if (!generator.isPowered())
            {
                hint = "Restore power at the generator";
            }
            else if (inventory.getEchoShards() < 3)
            {
                hint = "Use SPACE to reveal hidden echo shards";
            }
            else
            {
                hint = "All echoes stabilized. Return to the terminal.";
            }

            if (objectiveReady && terminal.isCompleted())
            {
                gameComplete = true;
                completionTimer = 0.f;
            }

            hud.update(
                inventory,
                hint,
                pulse.getCooldownRemaining(),
                generator.isPowered(),
                anomaly.getThreatLevel(player.getPosition()),
                objectiveReady,
                gameComplete
            );
        }
        else
        {
            completionTimer += dt;
            hud.update(
                inventory,
                completionTimer < 3.f ? "Extraction signal locked. Sector cleared." : "PRESS ESC TO EXIT",
                pulse.getCooldownRemaining(),
                generator.isPowered(),
                0.f,
                true,
                true
            );
        }

        camera.setCenter(player.getPosition());
        window.setView(camera);

        window.clear(sf::Color(8, 11, 15));

        world.drawFloor(window, player.getPosition());
        world.drawGrid(window);

        door.draw(window);
        generator.draw(window);
        terminal.draw(window);
        keycard.draw(window);

        for (const EchoNode& echo : echoes)
            echo.draw(window);

        drawLight(window, player.getPosition());
        pulse.draw(window);
        anomaly.draw(window);
        player.draw(window);

        // Лёгкая помеха, когда аномалия близко.
        const float threat = anomaly.getThreatLevel(player.getPosition());
        if (threat > 0.01f && !gameComplete)
        {
            sf::RectangleShape interference;
            interference.setSize({1280.f, 720.f});
            interference.setPosition({0.f, 0.f});
            interference.setFillColor(
                sf::Color(80, 180, 255,
                    static_cast<std::uint8_t>(threat * 55.f)));
            window.setView(window.getDefaultView());
            window.draw(interference);
        }

        hud.draw(window);
        window.display();
    }

    return 0;
}
