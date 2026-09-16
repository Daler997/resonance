#pragma once

class Inventory
{
private:

    bool keycard = false;


public:

    void addKeycard()
    {
        keycard = true;
    }


    bool hasKeycard() const
    {
        return keycard;
    }
};