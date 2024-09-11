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
        /*//create dynamic actor
        physx::PxRigidDynamic* rigid_dynamic = PhysX_Impl::GetPhysics()->createRigidDynamic(
            physx::PxTransform(Transform::ToPhysXTransform(transform)));*/
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
        debug_shape_ = GeometricPrimitive::CreateBox(Renderer::GetDeviceContext(), transform->scale,false);
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

void CPhysXBox::Draw()
{
    if (view_)
    {
        Entity* parent = Manager::FindEntityByID(parent_id_);
        if (!parent) {
            std::cerr << "Parent entity not found" << std::endl;
            return;
        }
        Transform* transform = parent->GetTransform();
        if (!transform) {
            std::cerr << "Transform not found" << std::endl;
            return;
        }
        XMFLOAT4X4 originalView, originalProj;
        originalView = Manager::GetActiveCamera()->GetViewMatrix();
        originalProj = Manager::GetActiveCamera()->GetProjectionMatrix();
        XMMATRIX world, scale, rot, trans;
        rot = XMMatrixRotationQuaternion(XMLoadFloat4(&transform->quaternion));
        trans = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
        scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
        world = scale * rot * trans;
        XMMATRIX viewMatrix = XMLoadFloat4x4(&originalView);
        XMMATRIX projMatrix = XMLoadFloat4x4(&originalProj);
        debug_shape_->Draw(world, viewMatrix, projMatrix, Colors::Green, nullptr, true);
        Renderer::LoadState();
        Manager::GetActiveCamera()->Draw();
    }
}
