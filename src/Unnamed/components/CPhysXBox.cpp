#include "CPhysXBox.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"
#include "renderer.h"


void CPhysXBox::Start()
{
    if (parent_entity_->GetComponent<CPhysXRigidBody>())
    {
        physx::PxRigidActor* ac = parent_entity_->GetComponent<CPhysXRigidBody>()->GetActor();
        // Œ`ó(Box)‚ðì¬
        /*physx::PxShape* box_shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Box‚Ì‘å‚«‚³
                physx::PxBoxGeometry(local_transform_->scale.x / 2.0f, local_transform_->scale.y / 2.0f, local_transform_->scale.z / 2.0f),
                // –€ŽCŒW”‚Æ”½”­ŒW”‚ÌÝ’è
                *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_)
            );
        // Œ`ó‚ð•R‚Ã‚¯
        box_shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*box_shape);*/
        //create exclusive shape
		Transform world_transform = GetWorldTransform();    
        physx::PxShape* box_shape = physx::PxRigidActorExt::createExclusiveShape(
            *ac, physx::PxBoxGeometry(world_transform.scale.x / 2.0f, world_transform.scale.y / 2.0f, world_transform.scale.z / 2.0f),
            *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_));
        shape_ = box_shape;
        debug_shape_ = GeometricPrimitive::CreateBox(Renderer::GetDeviceContext(), world_transform.scale,false);
        shape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, simulate_);
        shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, is_trigger_);
        shape_->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, query_);
    }
    else
    {
        std::cerr << "Parent entity does not have a PhysX actor" << std::endl;
    }
}

void CPhysXBox::CleanUp()
{
}
