#pragma once

#include "entity.h"
#include "traits/debugmenu.h"

class Pinball
{
private:
    Entity* entity_ = nullptr;

public:
    Pinball() = default;
    ~Pinball()= default;
    void Start();
};
