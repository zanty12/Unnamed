#pragma once
#include <d3d11.h>

#include "../entity.h"

class Player
{
private:
    Entity* entity_ = nullptr;

public:
    Player() = default;
    ~Player();
    void Start();
    void Update();
};
