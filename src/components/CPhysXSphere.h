#pragma once
#include "component.h"
#include "PxActor.h"

class CPhysXSphere : public Component
{
private:
    physx::PxShape* shape_ = nullptr;
public:
    CPhysXSphere() : Component("PhysXPrimitive") {}
    ~CPhysXSphere() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
