#include "CPhysXRigidBody.h"
#include "manager.h"
#include "system/PhysX_Impl.h"

void CPhysXRigidBody::Start()
{
    Entity* parent = Manager::FindEntityByID(parent_id_);
    Transform* transform = parent->GetTransform();
    if (is_dynamic_)
    {
        physx::PxRigidDynamic* rigid_dynamic = PhysX_Impl::GetPhysics()->createRigidDynamic(
            physx::PxTransform(Transform::ToPhysXTransform(transform)));
        actor_ = rigid_dynamic;
    }
    else
    {
        physx::PxRigidStatic* rigid_static = PhysX_Impl::GetPhysics()->createRigidStatic(
            physx::PxTransform(Transform::ToPhysXTransform(transform)));
        actor_ = rigid_static;
    }
    PhysX_Impl::GetScene()->addActor(*actor_);
}

void CPhysXRigidBody::CleanUp()
{
    actor_->release();
}