#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>


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


        text.setCharacterSize(
            24
        );


        text.setFillColor(
            sf::Color::White
        );


        text.setPosition(
            {20.f,20.f}
        );


        text.setString(
            "ACCESS CARD: NONE"
        );

    }



    void update(
        bool hasKeycard
    )
    {

        if(hasKeycard)
        {
            text.setString(
                "ACCESS CARD: OK"
            );
        }

        else
        {
            text.setString(
                "ACCESS CARD: NONE"
            );
        }

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