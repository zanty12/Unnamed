#pragma once
#include "CPhysXPrimitive.h"

class CPhysXSphere : public CPhysXPrimitive
{
public:
    CPhysXSphere() = default;
    ~CPhysXSphere() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
