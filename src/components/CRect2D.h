#pragma once
#include "CPrimitive2D.h"

class CRect2D : public CPrimitive2D
{
    XMFLOAT2 start_uv_;
    XMFLOAT2 end_uv_;
public:
    CRect2D() = default;
    ~CRect2D() override = default;
    void Start() override;
    void Update() override;

    void Draw() override;
};
