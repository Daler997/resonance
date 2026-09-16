#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>


class HUD
{

private:

    sf::Font font;

    sf::Text text;


public:


    HUD()
        :
        text(font)
    {

        if(!font.openFromFile(
            "assets/font.ttf"
        ))
        {
            throw std::runtime_error(
                "Cannot load font"
            );
        }


        text.setCharacterSize(24);

        text.setFillColor(
            sf::Color::White
        );

        text.setPosition(
            {20.f,20.f}
        );

    }



    void update(
        bool hasKeycard,
        const std::string& hint
    )
    {

        std::string result;


        if(hasKeycard)
            result += "ACCESS CARD: OK\n";
        else
            result += "ACCESS CARD: NONE\n";


        result += hint;


        text.setString(result);

    }



    void draw(
        sf::RenderWindow& window
    )
    {

        window.setView(
            window.getDefaultView()
        );

        window.draw(text);

    }

};