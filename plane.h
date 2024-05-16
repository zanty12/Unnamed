#pragma once

#include "primitive3D.h"
#include "transform.h"


class Plane : public Primitive3D
{
private:
    Transform transform_ = Transform::Identity();
public:
    void Start() override;
    void Update(Entity* parent) override;
    void Draw() override;
};
