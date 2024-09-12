#pragma once
#include <DirectXMath.h>
#include "component.h"
#include "system/PhysX_Impl.h"

namespace physx
{
    class PxRigidActor;
}

class CPhysXRigidBody : public Component
{
    physx::PxRigidActor* actor_ = nullptr;
    bool is_dynamic_ = true;
	bool is_trigger_ = false;

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
    void Update() override;
    void CleanUp() override;

    physx::PxRigidActor* GetActor() const { return actor_; }
    void SetDynamic(bool is_dynamic) { is_dynamic_ = is_dynamic; }
    bool IsDynamic() const { return is_dynamic_; }
	void SetIsTrigger(bool is_trigger) { is_trigger_ = is_trigger; }
	bool IsTrigger() const { return is_trigger_; }
    void SetLinearVelocity(const DirectX::XMFLOAT3& velocity);
    void SetAngularVelocity(const DirectX::XMFLOAT3& velocity);
    void SetMass(float mass);
    void SetLinearDamping(float damping);
    void SetAngularDamping(float damping);
    void SetEnableGravity(bool enable);

    //getter
    float GetMass() const;
    float GetLinearDamping() const;
    float GetAngularDamping() const;
    DirectX::XMFLOAT3 GetLinearVelocity() const;
    DirectX::XMFLOAT3 GetAngularVelocity() const;
    bool GetEnableGravity() const;
};
