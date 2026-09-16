#pragma once

#include "Interactable.hpp"
#include <vector>


class InteractionManager
{

public:


    static Interactable* find(
        std::vector<Interactable*>& objects,
        sf::Vector2f playerPosition
    )
    {

        Interactable* result =
            nullptr;


        float minDistance =
            90.f;


        for(auto* object : objects)
        {

            float d =
                object->distanceTo(
                    playerPosition
                );


            if(d < minDistance)
            {
                minDistance=d;
                result=object;
            }

        }


        return result;
    }

};