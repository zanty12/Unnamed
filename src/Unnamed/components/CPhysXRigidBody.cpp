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
	if (!is_dynamic_)
    {
		//copy actor transform to component transform
		physx::PxTransform actor_transform = actor_->getGlobalPose();
		Transform worldTransform = GetWorldTransform();
		actor_transform.p = physx::PxVec3(worldTransform.position.x, worldTransform.position.y, worldTransform.position.z);
		actor_transform.q = physx::PxQuat(worldTransform.quaternion.x, worldTransform.quaternion.y, worldTransform.quaternion.z, worldTransform.quaternion.w);
		actor_->setGlobalPose(actor_transform);
	}
	else
	{
		//copy actor transform to Parent transform
		physx::PxTransform actor_transform = actor_->getGlobalPose();
		Entity* parent = Manager::FindEntityByID(parent_id_);
		Transform* transform = parent->GetTransform();
		Transform::MoveTo(transform, XMFLOAT3(actor_transform.p.x, actor_transform.p.y, actor_transform.p.z));
		XMFLOAT4 quat = XMFLOAT4(actor_transform.q.x, actor_transform.q.y, actor_transform.q.z, actor_transform.q.w);
		Transform::RotateToQuat(transform, quat);
	}
}

void CPhysXRigidBody::CleanUp()
{
    actor_->release();
}

void CPhysXRigidBody::SetLinearVelocity(const DirectX::XMFLOAT3& velocity)
{
	if (is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setLinearVelocity(physx::PxVec3(velocity.x, velocity.y, velocity.z));
	}

}

void CPhysXRigidBody::SetAngularVelocity(const DirectX::XMFLOAT3& velocity)
{
	if(is_dynamic_)
	{
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setAngularVelocity(physx::PxVec3(velocity.x, velocity.y, velocity.z));
	}
}

void CPhysXRigidBody::SetMass(float mass)
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setMass(mass);
	}
}

void CPhysXRigidBody::SetLinearDamping(float damping)
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setLinearDamping(damping);
	}
}

void CPhysXRigidBody::SetAngularDamping(float damping)
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setAngularDamping(damping);
	}
}

void CPhysXRigidBody::SetEnableGravity(bool enable)
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, !enable);
	}
}

void CPhysXRigidBody::SetMassSpaceInertiaTensor(const DirectX::XMFLOAT3& inertia_tensor) {
	if (is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		dynamic->setMassSpaceInertiaTensor(physx::PxVec3(inertia_tensor.x, inertia_tensor.y, inertia_tensor.z));
	}
}

void CPhysXRigidBody::SetGlobalPosition(const DirectX::XMFLOAT3& position)
{
	physx::PxTransform actor_transform = actor_->getGlobalPose();
	actor_transform.p = physx::PxVec3(position.x, position.y, position.z);
	actor_->setGlobalPose(actor_transform);
}

void CPhysXRigidBody::SetGlobalRotation(const DirectX::XMFLOAT4& rotation)
{
	physx::PxTransform actor_transform = actor_->getGlobalPose();
	actor_transform.q = physx::PxQuat(rotation.x, rotation.y, rotation.z, rotation.w);
	actor_->setGlobalPose(actor_transform);
}

void CPhysXRigidBody::LockLinearAxis(bool x, bool y, bool z)
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		if(x)
		{
			dynamic->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
		}
		if(y)
		{
			dynamic->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);
		}
		if(z)
		{
			dynamic->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
		}
	}
}

void CPhysXRigidBody::LockAngularAxis(bool x, bool y, bool z)
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		if(x)
		{
			dynamic->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		}
		if(y)
		{
			dynamic->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
		}
		if(z)
		{
			dynamic->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
		}
	}
}


float CPhysXRigidBody::GetMass() const
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		return dynamic->getMass();
	}
	return 0.0f;
}

float CPhysXRigidBody::GetLinearDamping() const
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		return dynamic->getLinearDamping();
	}
	return 0.0f;
}

float CPhysXRigidBody::GetAngularDamping() const
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		return dynamic->getAngularDamping();
	}
	return 0.0f;
}

DirectX::XMFLOAT3 CPhysXRigidBody::GetLinearVelocity() const
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		physx::PxVec3 velocity = dynamic->getLinearVelocity();
		return XMFLOAT3(velocity.x, velocity.y, velocity.z);
	}
	return XMFLOAT3(0.0f, 0.0f, 0.0f);
}

DirectX::XMFLOAT3 CPhysXRigidBody::GetAngularVelocity() const
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		physx::PxVec3 velocity = dynamic->getAngularVelocity();
		return XMFLOAT3(velocity.x, velocity.y, velocity.z);
	}
	return XMFLOAT3(0.0f, 0.0f, 0.0f);
}

bool CPhysXRigidBody::GetEnableGravity() const
{
	if(is_dynamic_)
	{
		//cast to dynamic
		physx::PxRigidDynamic* dynamic = actor_->is<physx::PxRigidDynamic>();
		return dynamic->getActorFlags() & physx::PxActorFlag::eDISABLE_GRAVITY;
	}
	return false;
}
