#pragma once
#include "CPhysXRigidBody.h"
#include "components/Component.h"

enum JointType
{
    UNDEFINED = -1,
    Fixed,
    Revolute,
    Prismatic,
    Gear,
    RackAndPinion,
    D6
};

class CPhysXJoint : public Component
{
private:
    CPhysXRigidBody* rigidBodyA_;
    CPhysXRigidBody* rigidBodyB_;
    physx::PxJoint* joint_;
    JointType type_;

public:
    CPhysXJoint() : Component("PhysXJoint", Kinematic)
    {
        rigidBodyA_ = nullptr;
        rigidBodyB_ = nullptr;
        joint_ = nullptr;
        type_ = UNDEFINED;
    }

    bool CreateJoint(CPhysXRigidBody* rigidBodyA, CPhysXRigidBody* rigidBodyB,
                     JointType type, const physx::PxTransform& poseA = physx::PxTransform(physx::PxIdentity),
                     const physx::PxTransform& poseB = physx::PxTransform(physx::PxIdentity));
    void SetVisualize(bool visualize) const;

    void Start() override
    {
    };
    void Update() override;
    void CleanUp() override;
};
