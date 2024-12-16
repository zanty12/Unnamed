#pragma once
#include "components/CPrimitive2D.h"

//a 2D rectangle with base width and length of 100px
class CScreenStencil : public CPrimitive2D
{
    XMFLOAT2 start_uv_;
    XMFLOAT2 end_uv_;
public:
    CScreenStencil() = default;
    ~CScreenStencil() override = default;
    void Start() override;
    void Update() override;

    void Draw() override;
};
