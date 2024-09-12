#pragma once
#include "entity.h"
#include "traits/object/spawnable.h"

class Bullet : public Spawnable
{
private:
    Entity* entity_;
    XMFLOAT3 pos_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    XMFLOAT3 vel_ = XMFLOAT3(0.0f, 0.0f, 1.0f);
public:
    Bullet() = default;
    ~Bullet()= default;
    void Start();
    void Spawn() override;
    void SetVelocity(XMFLOAT3 vel) { vel_ = vel; }
    void SetPosition(XMFLOAT3 pos) { pos_ = pos; }
};
