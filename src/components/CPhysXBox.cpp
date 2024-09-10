#include "CPhysXBox.h"

#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"

void CPhysXBox::Start()
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
                physx::PxBoxGeometry(transform->scale.x, transform->scale.y, transform->scale.z),
            // 摩擦係数と反発係数の設定
            *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f)
            );
        // 形状を紐づけ
        box_shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*box_shape);
        box_shape_ = box_shape;
    }
    else
    {
        std::cerr<<"Parent entity does not have a PhysX actor"<<std::endl;
    }
}

void CPhysXBox::CleanUp()
{
    box_shape_->getActor()->detachShape(*box_shape_);
}

