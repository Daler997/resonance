#include <SFML/Graphics.hpp>

#include "Door.hpp"
#include "Generator.hpp"
#include "Player.hpp"
#include "Terminal.hpp"
#include "World.hpp"
#include "Inventory.hpp"
#include "Keycard.hpp"
#include "HUD.hpp"
#include "InteractionManager.hpp"

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

    std::vector<Interactable*> objects;

    World world;
    Player player({640.f, 360.f});
    Generator generator({920.f, 250.f});
    Door door({765.f, 250.f});
    Terminal terminal({850.f, 340.f});
    Inventory inventory;
    HUD hud;

    Keycard keycard(
        {600.f,200.f}
    );

    objects.push_back(&generator);
    objects.push_back(&terminal);
    objects.push_back(&keycard);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* key =
                    event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();

                if (key->scancode == sf::Keyboard::Scancode::E)
                {
                    constexpr float interactionDistance = 85.f;
                    const sf::Vector2f playerPosition = player.getPosition();

                    auto object =
                        InteractionManager::find(
                            objects,
                            player.getPosition());

                    if (object)
                    {
                        object->interact();
                    }
                }
            }
        }

        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.05f);

        // Питание двери зависит от генератора.
        door.setPowered(generator.isPowered());
        door.update(dt, player.getPosition());

        player.update(
            dt,
            world.getWalls(),
            door
        );
        hud.update(
            inventory.hasKeycard()
        );

        camera.setCenter(player.getPosition());
        window.setView(camera);

        window.clear(sf::Color(8, 11, 15));

        world.drawFloor(window, player.getPosition());
        world.drawGrid(window);

        door.draw(window);
        generator.draw(window);
        terminal.draw(window);
        keycard.draw(window);

        drawLight(window, player.getPosition());
        player.draw(window);

        hud.draw(window);
        
        window.display();
    }

    return 0;
}
