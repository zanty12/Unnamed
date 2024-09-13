#pragma once

#include "../entity.h"

class Enemy
{
private:
    Entity* entity_ = nullptr;

public:
    Enemy() = default;
    ~Enemy()= default;
    void Start();
    Entity* GetEntity() { return entity_; }
};
