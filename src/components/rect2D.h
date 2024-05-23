#pragma once
#include "primitive2D.h"

class Rect2D : public Primitive2D
{
public:
    Rect2D() = default;
    ~Rect2D() override = default;
    void Start() override;
    void Update() override;

    void Draw() override;
};
