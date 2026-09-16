#pragma once

class Inventory
{
public:
    void addKeycard()
    {
        keycard = true;
    }

    bool hasKeycard() const
    {
        return keycard;
    }

    void addEchoShard()
    {
        ++echoShards;
    }

    int getEchoShards() const
    {
        return echoShards;
    }

private:
    bool keycard = false;
    int echoShards = 0;
};
