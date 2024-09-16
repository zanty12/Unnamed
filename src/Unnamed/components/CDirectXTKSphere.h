#pragma once
#include "CDirectXTKPrimitive.h"

class CDirectXTKSphere : public CDirectXTKPrimitive
{
private:
    float radius_ = 1.0f;
public:
    void Start() override;
    void CleanUp() override;
    void SetRadius(float radius) { radius_ = radius; }
};
