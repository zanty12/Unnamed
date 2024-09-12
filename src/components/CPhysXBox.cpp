#include "CPhysXBox.h"
#include "CPhysXRigidBody.h"
#include "system/PhysX_Impl.h"
#include "Manager.h"
#include "renderer.h"


void CPhysXBox::Start()
{
    Entity* parent = Manager::FindEntityByID(parent_id_);
    Transform* transform = parent->GetTransform();
    if (parent->GetComponent<CPhysXRigidBody>())
    {
        physx::PxRigidActor* ac = parent->GetComponent<CPhysXRigidBody>()->GetActor();
        // 形状(Box)を作成
        physx::PxShape* box_shape
            = PhysX_Impl::GetPhysics()->createShape(
                // Boxの大きさ
                physx::PxBoxGeometry(transform->scale.x / 2.0f, transform->scale.y / 2.0f, transform->scale.z / 2.0f),
                // 摩擦係数と反発係数の設定
                *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f)
            );
        // 形状を紐づけ
        box_shape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        ac->attachShape(*box_shape);
        shape_ = box_shape;
        debug_shape_ = GeometricPrimitive::CreateBox(Renderer::GetDeviceContext(), transform->scale);
    }
    else
    {
        std::cerr << "Parent entity does not have a PhysX actor" << std::endl;
    }
}

void CPhysXBox::CleanUp()
{
    shape_->getActor()->detachShape(*shape_);
}

