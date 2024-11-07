#pragma once

#include "entity.h"
#include "traits/object/spawnable.h"

class Cube : public Spawnable
{
private:
    Entity* entity_ = nullptr;
	Transform transform_ = Transform{ XMFLOAT3{0.0f, 0.0f, 0.0f}, XMFLOAT3{0.0f, 0.0f, 0.0f}, XMFLOAT3{1.0f, 1.0f, 1.0f} };
public:
    Cube() = default;
    ~Cube()= default;
    void Start();
	void Spawn() override;
    void SetTransform(const Transform& transform) { Transform::Copy(transform_, transform); }
};
