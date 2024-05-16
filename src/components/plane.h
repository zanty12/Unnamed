#pragma once

#include "primitive3D.h"


class Plane : public Primitive3D
{
public:
    void Start() override;
    void Update(Entity* parent) override;
    void Draw() override;
};
