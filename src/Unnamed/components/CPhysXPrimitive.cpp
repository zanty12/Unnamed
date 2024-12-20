#include "CPhysXPrimitive.h"
#include "Manager.h"

void CPhysXPrimitive::Draw()
{
    if (debug_view_)
    {
        Transform transform = parent_entity_->GetTransform();
        XMFLOAT4X4 originalView, originalProj;
        originalView = Manager::GetActiveCamera()->GetViewMatrix();
        originalProj = Manager::GetActiveCamera()->GetProjectionMatrix();
        XMMATRIX world, scale, rot, trans;
        rot = XMMatrixRotationQuaternion(XMLoadFloat4(&transform.quaternion));
        trans = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
        scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
        world = scale * rot * trans;
        XMMATRIX viewMatrix = XMLoadFloat4x4(&originalView);
        XMMATRIX projMatrix = XMLoadFloat4x4(&originalProj);
        debug_shape_->Draw(world, viewMatrix, projMatrix, Colors::Green, nullptr, true);
    }
}