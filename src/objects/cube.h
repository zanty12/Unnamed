#pragma once

#include "../entity.h"

class Cube
{
private:
    Entity* entity_ = nullptr;

public:
    Cube() = default;
    ~Cube()= default;
    void Start();
};
