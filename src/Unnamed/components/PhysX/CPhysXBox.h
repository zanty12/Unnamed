#pragma once
#include "CPhysXPrimitive.h"

class CPhysXBox : public CPhysXPrimitive
{
public:
    CPhysXBox() = default;
    ~CPhysXBox() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
