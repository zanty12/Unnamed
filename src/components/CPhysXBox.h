#pragma once
#include "component.h"
#include "PxActor.h"

class CPhysXBox : public Component
{
private:
    physx::PxShape* box_shape_ = nullptr;
public:
    CPhysXBox() : Component("PhysXBox") {}
    ~CPhysXBox() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
