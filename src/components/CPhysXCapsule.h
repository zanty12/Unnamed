#pragma once
#include "component.h"
#include "PxActor.h"

class CPhysXCapsule : public Component
{
private:
    physx::PxShape* shape_ = nullptr;
public:
    CPhysXCapsule() : Component("PhysXPrimitive") {}
    ~CPhysXCapsule() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
