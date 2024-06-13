#pragma once

#include "CPrimitive3D.h"


class CPlane : public CPrimitive3D
{
    XMFLOAT2 start_uv_ = XMFLOAT2(0.0f, 0.0f);
    XMFLOAT2 end_uv_ = XMFLOAT2(1.0f, 1.0f);
    bool billboard_ = false;
public:
    void Start() override;
    void Update() override;
    void Draw() override;
    void SetStartUV(XMFLOAT2 uv){start_uv_ = uv;}
    void SetEndUV(XMFLOAT2 uv){end_uv_ = uv;}
    void SetBillboard(bool billboard){billboard_ = billboard;}
};
