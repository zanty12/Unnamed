#include "CPhysXCapsule.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"
#include "renderer.h"

void CPhysXCapsule::Start()
{
    Entity* parent = Manager::FindEntityByID(parent_id_);
    if (parent->GetComponent<CPhysXRigidBody>())
    {
        physx::PxRigidActor* ac = parent->GetComponent<CPhysXRigidBody>()->GetActor();
        /*//create dynamic actor
        physx::PxRigidDynamic* rigid_dynamic = PhysX_Impl::GetPhysics()->createRigidDynamic(
            physx::PxTransform(Transform::ToPhysXTransform(local_transform_)));*/
        // Œ`ó‚ðì¬
        /*physx::PxShape* shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Box‚Ì‘å‚«‚³
                physx::PxCapsuleGeometry(local_transform_->scale.x / 2.0f, local_transform_->scale.y / 2.0f),
                // –€ŽCŒW”‚Æ”½”­ŒW”‚ÌÝ’è
                *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_)
            );
        // Œ`ó‚ð•R‚Ã‚¯
        shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*shape);*/
        //create exclusive shape
		Transform world_transform = GetWorldTransform();
		physx::PxTransform relativePose = Transform::ToPhysXTransform(local_transform_);
       
		relativePose.q = relativePose.q * (physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
        physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(
            *ac, physx::PxCapsuleGeometry(world_transform.scale.x / 2.0f, world_transform.scale.y / 2.0f),
            *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_));
		shape->setLocalPose(relativePose);
        shape_ = shape;
        debug_shape_ = GeometricPrimitive::CreateCylinder(Renderer::GetDeviceContext(), world_transform.scale.y,
            world_transform.scale.x, 8,false);
        shape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, simulate_);
        shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, is_trigger_);
        shape_->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, query_);
    }
    else
    {
        std::cerr << "Parent entity does not have a PhysX actor" << std::endl;
    }
}

void CPhysXCapsule::CleanUp()
{
}
