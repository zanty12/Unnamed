#pragma once
#include "entity.h"

class Bullet
{
private:
    Entity* entity_ = nullptr;
    XMFLOAT3 vel_ = XMFLOAT3(0.0f, 0.0f, 1.0f);
public:
    Bullet() = default;
    ~Bullet()= default;
    void Start();
    void SetVelocity(XMFLOAT3 vel) { vel_ = vel; }

    
};
