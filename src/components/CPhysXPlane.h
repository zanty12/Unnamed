#pragma once
#include "component.h"
#include "PxActor.h"

class CPhysXPlane : public Component
{
private:
    physx::PxShape* plane_shape_ = nullptr;
public:
    CPhysXPlane() : Component("PhysXPrimitive") {}
    ~CPhysXPlane() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
};
