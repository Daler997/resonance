#pragma once

#include "Interactable.hpp"
#include <vector>

class InteractionManager
{
public:
    static Interactable* find(
        const std::vector<Interactable*>& objects,
        sf::Vector2f playerPosition,
        float maxDistance = 90.f)
    {
        Interactable* result = nullptr;
        float bestDistance = maxDistance;

        for (Interactable* object : objects)
        {
            if (!object || !object->isInteractable())
                continue;

            const float distance = object->distanceTo(playerPosition);

            if (distance < bestDistance)
            {
                bestDistance = distance;
                result = object;
            }
        }

        return result;
    }
};
