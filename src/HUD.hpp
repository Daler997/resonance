#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Inventory.hpp"

class HUD
{
public:
    HUD()
        : text(font), objectiveText(font)
    {
        if (!font.openFromFile("assets/font.ttf"))
            throw std::runtime_error("Cannot load assets/font.ttf");

        text.setCharacterSize(22);
        text.setFillColor(sf::Color::White);
        text.setPosition({20.f, 18.f});

        objectiveText.setCharacterSize(26);
        objectiveText.setFillColor(sf::Color(180, 240, 255));
        objectiveText.setPosition({20.f, 625.f});
    }

    void update(
        const Inventory& inventory,
        const std::string& hint,
        float pulseCooldown,
        bool generatorPowered,
        float threat,
        bool terminalReady,
        bool completed)
    {
        std::ostringstream out;

        out << "ACCESS CARD: " << (inventory.hasKeycard() ? "OK" : "NONE") << "\n";
        out << "ECHO SHARDS: " << inventory.getEchoShards() << "/3\n";
        out << "POWER: " << (generatorPowered ? "ONLINE" : "OFFLINE") << "\n";

        if (pulseCooldown <= 0.f)
            out << "RESONANCE [SPACE]: READY";
        else
            out << std::fixed << std::setprecision(1)
                << "RESONANCE: " << pulseCooldown << "s";

        if (threat > 0.f)
        {
            out << "\nINTERFERENCE: "
                << static_cast<int>(threat * 100.f) << "%";
        }

        if (!hint.empty())
            out << "\n\n" << hint;

        text.setString(out.str());

        if (completed)
            objectiveText.setString("EXTRACTION COMPLETE");
        else if (terminalReady)
            objectiveText.setString("OBJECTIVE: Return to the terminal");
        else if (inventory.getEchoShards() < 3)
            objectiveText.setString("OBJECTIVE: Stabilize 3 echo shards");
        else if (!generatorPowered)
            objectiveText.setString("OBJECTIVE: Restore power");
        else if (!inventory.hasKeycard())
            objectiveText.setString("OBJECTIVE: Find the access card");
        else
            objectiveText.setString("OBJECTIVE: Reach the terminal");
    }

    void draw(sf::RenderWindow& window)
    {
        window.setView(window.getDefaultView());
        window.draw(text);
        window.draw(objectiveText);
    }

private:
    sf::Font font;
    sf::Text text;
    sf::Text objectiveText;
};
