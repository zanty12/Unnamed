#pragma once
#include "component.h"
#include "PxRigidActor.h"

namespace physx
{
    class PxRigidActor;
}

class CPhysXRigidBody : public Component
{
    physx::PxRigidActor* actor_ = nullptr;
    bool is_dynamic_ = false;

public:
    CPhysXRigidBody() : Component("PhysXRigidBody")
    {
    }

    CPhysXRigidBody(bool dynamic) : Component("PhysXRigidBody")
    {
        is_dynamic_ = dynamic;
    }

    ~CPhysXRigidBody() override = default;
    void Start() override;
    void Update() override {}
    void CleanUp() override;

    physx::PxRigidActor* GetActor() const { return actor_; }
    void SetDynamic(bool is_dynamic) { is_dynamic_ = is_dynamic; }
    bool IsDynamic() const { return is_dynamic_; }

};
