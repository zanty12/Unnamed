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

void CPhysXRigidBody::Update()
{
    if(actor_->is<physx::PxRigidDynamic>()->isSleeping())
    {
        return;
    }
    //copy actor transform to entity transform
    Entity* parent = Manager::FindEntityByID(parent_id_);
    Transform* transform = parent->GetTransform();
    physx::PxTransform actor_transform = actor_->getGlobalPose();
    Transform::MoveTo(transform, XMFLOAT3(actor_transform.p.x, actor_transform.p.y, actor_transform.p.z));
    XMFLOAT4 quat = XMFLOAT4(actor_transform.q.x, actor_transform.q.y, actor_transform.q.z, actor_transform.q.w);
    Transform::RotateToQuat(transform, quat);
}

void CPhysXRigidBody::CleanUp()
{
    actor_->release();
}
