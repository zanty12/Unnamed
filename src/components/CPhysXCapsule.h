#pragma once
#include "CPhysXPrimitive.h"

class CPhysXCapsule : public CPhysXPrimitive
{
public:
    CPhysXCapsule() = default;
    ~CPhysXCapsule() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
