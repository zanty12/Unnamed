#include "CPhysXSphere.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"
#include "renderer.h"

void CPhysXSphere::Start()
{
    Entity* parent = Manager::FindEntityByID(parent_id_);
    if (parent->GetComponent<CPhysXRigidBody>())
    {
        physx::PxRigidActor* ac = parent->GetComponent<CPhysXRigidBody>()->GetActor();
        // Œ`ó‚ðì¬
        /*physx::PxShape* shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Box‚Ì‘å‚«‚³
                physx::PxSphereGeometry(local_transform_->scale.x),
                // –€ŽCŒW”‚Æ”½”­ŒW”‚ÌÝ’è
                *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_)
            );
        // Œ`ó‚ð•R‚Ã‚¯
        shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*shape);*/
        //create exclusive shape
		Transform world_transform = GetWorldTransform();
        physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(*ac,physx::PxSphereGeometry(world_transform.scale.x), *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_));
        shape_ = shape;
        debug_shape_ = GeometricPrimitive::CreateSphere(Renderer::GetDeviceContext(), world_transform.scale.x, 8,false);
        shape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, simulate_);
        shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, is_trigger_);
        shape_->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, query_);
    }
    else
    {
        std::cerr << "Parent entity does not have a PhysX actor" << std::endl;
    }
}

void CPhysXSphere::CleanUp()
{
}
