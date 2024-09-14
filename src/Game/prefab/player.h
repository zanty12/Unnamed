#pragma once

#include "entity.h"

class Player
{
private:
    Entity* entity_ = nullptr;

public:
    Player() = default;
    ~Player()= default;
    void Start();
};
