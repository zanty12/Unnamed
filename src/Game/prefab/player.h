#pragma once

#include "entity.h"
#include "traits/debugmenu.h"

class Player
{
private:
    Entity* entity_ = nullptr;

public:
    Player() = default;
    ~Player()= default;
    void Start();
};
