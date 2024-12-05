#pragma once

#include "entity.h"
#include "traits/object/spawnable.h"

class Cube : public Spawnable
{
private:
    Entity* entity_ = nullptr;
	Transform transform_ = Transform::Identity();
public:
    Cube() = default;
    ~Cube()= default;
    void Start();
	void Spawn() override;
    void SetTransform(const Transform& transform) { Transform::Copy(transform_, transform); }
};
