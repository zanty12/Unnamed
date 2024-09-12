#include "CPhysXSphere.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"
#include "renderer.h"

void CPhysXSphere::Start()
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
        physx::PxShape* shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Boxの大きさ
                physx::PxSphereGeometry(transform->scale.x),
                // 摩擦係数と反発係数の設定
                *PhysX_Impl::GetPhysics()->createMaterial(static_friction_, dynamic_friction_, restitution_)
            );
        // 形状を紐づけ
        shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*shape);
        shape_ = shape;
        debug_shape_ = GeometricPrimitive::CreateSphere(Renderer::GetDeviceContext(), transform->scale.x, 8);
        if(is_trigger_)
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

void CPhysXSphere::CleanUp()
{
    shape_->getActor()->detachShape(*shape_);
}
