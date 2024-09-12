#include "CPhysXCapsule.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"
#include "renderer.h"

void CPhysXCapsule::Start()
{
    Entity* parent = Manager::FindEntityByID(parent_id_);
    Transform* transform = parent->GetTransform();
    if (parent->GetComponent<CPhysXRigidBody>())
    {
        physx::PxRigidActor* ac = parent->GetComponent<CPhysXRigidBody>()->GetActor();
        /*//create dynamic actor
        physx::PxRigidDynamic* rigid_dynamic = PhysX_Impl::GetPhysics()->createRigidDynamic(
            physx::PxTransform(Transform::ToPhysXTransform(transform)));*/
        // 形状を作成
        /*physx::PxShape* shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Boxの大きさ
                physx::PxCapsuleGeometry(transform->scale.x / 2.0f, transform->scale.y / 2.0f),
                // 摩擦係数と反発係数の設定
                *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_)
            );
        // 形状を紐づけ
        shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*shape);*/
        //create exclusive shape
        physx::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(
            *ac, physx::PxCapsuleGeometry(transform->scale.x / 2.0f, transform->scale.y / 2.0f),
            *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_));
        shape_ = shape;
        debug_shape_ = GeometricPrimitive::CreateCylinder(Renderer::GetDeviceContext(), transform->scale.y,
                                                          transform->scale.x, 16);
        if (is_trigger_)
        {
            shape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
            shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
        }
    }
    else
    {
        std::cerr << "Parent entity does not have a PhysX actor" << std::endl;
    }
}

void CPhysXCapsule::CleanUp()
{
}
