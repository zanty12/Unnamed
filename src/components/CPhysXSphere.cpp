#include "CPhysXSphere.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"

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
        // 形状(Box)を作成
        physx::PxShape* box_shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Boxの大きさ
                physx::PxSphereGeometry(transform->scale.x),
                // 摩擦係数と反発係数の設定
                *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f)
            );
        // 形状を紐づけ
        box_shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*box_shape);
        shape_ = box_shape;
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
