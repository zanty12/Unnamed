#pragma once
#include "CPhysXPrimitive.h"

class CPhysXSphere : public CPhysXPrimitive
{
private:
    float radius_ = 1.0f;
public:
    CPhysXSphere() = default;
    ~CPhysXSphere() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;

    void SetRadius(float radius) { radius_ = radius; }
    float GetRadius() { return radius_; }
};
