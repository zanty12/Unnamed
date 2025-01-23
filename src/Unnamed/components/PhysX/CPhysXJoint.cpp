#include "CPhysXJoint.h"
#include "system/PhysX_Impl.h"


bool CPhysXJoint::CreateJoint(CPhysXRigidBody* rigidBodyA,
                              CPhysXRigidBody* rigidBodyB,
                              JointType type, const physx::PxTransform& poseA, const physx::PxTransform& poseB)
{
    rigidBodyA_ = rigidBodyA;
    rigidBodyB_ = rigidBodyB;
    type_ = type;
    physx::PxPhysics* physics = PhysX_Impl::GetPhysics();
    physx::PxRigidActor* actorA = rigidBodyA_->GetActor();
    physx::PxRigidActor* actorB = rigidBodyB_->GetActor();
    switch (type)
    {
    case Fixed:
        joint_ = physx::PxFixedJointCreate(*physics, actorA, poseA, actorB,
                                           poseB);
        break;
    case Revolute:
        joint_ = physx::PxRevoluteJointCreate(*physics, actorA, poseA, actorB,
                                              poseB);
        break;
    case Prismatic:
        joint_ = physx::PxPrismaticJointCreate(*physics, actorA, poseA, actorB,
                                               poseB);
        break;
    case Gear:
        joint_ = physx::PxGearJointCreate(*physics, actorA, poseA, actorB,
                                          poseB);
        break;
    case RackAndPinion:
        joint_ = physx::PxRackAndPinionJointCreate(*physics, actorA, poseA, actorB,
                                                   poseB);
        break;
    default:
        joint_ = nullptr;
    }
    if (joint_ != nullptr)
    {
        return true;
    }
    return false;
}

void CPhysXJoint::SetVisualize(bool visualize) const
{
    if (joint_ != nullptr)
    {
        joint_->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, visualize);
    }
}

void CPhysXJoint::Update()
{
}

void CPhysXJoint::CleanUp()
{
    if (joint_ != nullptr)
    {
        joint_->release();
    }
}

