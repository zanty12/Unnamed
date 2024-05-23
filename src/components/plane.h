#pragma once

#include "primitive3D.h"


class Plane : public Primitive3D
{
public:
    void Start() override;
    void Update() override;
    void Draw() override;
};
