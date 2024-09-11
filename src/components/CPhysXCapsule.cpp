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
        // 形状(Box)を作成
        physx::PxShape* shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Boxの大きさ
                physx::PxBoxGeometry(transform->scale.x / 2.0f, transform->scale.y / 2.0f, transform->scale.z / 2.0f),
                // 摩擦係数と反発係数の設定
                *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f)
            );
        // 形状を紐づけ
        shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*shape);
        shape_ = shape;
        debug_shape_ = GeometricPrimitive::CreateCylinder(Renderer::GetDeviceContext(), transform->scale.y, transform->scale.x, 16);
    }
    else
    {
        std::cerr << "Parent entity does not have a PhysX actor" << std::endl;
    }
}

void CPhysXCapsule::CleanUp()
{
    shape_->getActor()->detachShape(*shape_);
}
