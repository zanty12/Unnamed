#pragma once
#include <DirectXMath.h>
#include "components/Component.h"
#include "system/PhysX_Impl.h"

namespace physx
{
    class PxRigidActor;
}

struct PhysXUserData
{
    std::string name;
    int id;
    std::string tag;
    std::vector<int> collision_ids;
	std::vector<std::string> ignore_tags_;
};

class CPhysXRigidBody : public Component
{
    physx::PxRigidActor* actor_ = nullptr;
    bool is_dynamic_ = true;
	bool contact_on_ = false;
	//PhysXUserData* user_data_ = nullptr;

public:
    CPhysXRigidBody() : Component("PhysXRigidBody",Kinematic)
    {
    }

    CPhysXRigidBody(bool dynamic) : Component("PhysXRigidBody",Kinematic)
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
    void SetLinearVelocity(const DirectX::XMFLOAT3& velocity);
    void SetAngularVelocity(const DirectX::XMFLOAT3& velocity);
    void SetMass(float mass);
    void SetLinearDamping(float damping);
    void SetAngularDamping(float damping);
    void SetEnableGravity(bool enable);
	void SetMassSpaceInertiaTensor(const DirectX::XMFLOAT3& inertia_tensor);
	void SetGlobalPosition(const DirectX::XMFLOAT3& position);
	void SetGlobalRotation(const DirectX::XMFLOAT4& rotation);
    void LockLinearAxis(bool x, bool y, bool z);
    void LockAngularAxis(bool x, bool y, bool z);
	void SetContact(bool contact) { contact_on_ = contact; }

    

    //getter
    float GetMass() const;
    float GetLinearDamping() const;
    float GetAngularDamping() const;
    DirectX::XMFLOAT3 GetLinearVelocity() const;
    DirectX::XMFLOAT3 GetAngularVelocity() const;
    bool GetEnableGravity() const;

    void ClearCollisions();
    void AddCollisionFilter(std::string tag);

};
