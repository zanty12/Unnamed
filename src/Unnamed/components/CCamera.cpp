#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "CCamera.h"

void CCamera::Start()
{
    if (parent_id_ < 0)
    {
        //position_ = DirectX::XMFLOAT3(0.0f + offset_.x, 0.0f + offset_.y, 0.0f + offset_.z);
        Transform::MoveTo(local_transform_, DirectX::XMFLOAT3(offset_.x, offset_.y, offset_.z));
    }
    else
    {
        //Get the transform of parent
        XMFLOAT3 parent_pos = Manager::FindEntityByID(parent_id_)->GetTransform().position;
        if(look_at_parent_)
            target_ = parent_pos;
        Transform::MoveTo(local_transform_, XMFLOAT3(offset_.x, offset_.y, offset_.z));
    }
}

void CCamera::CleanUp()
{
}

void CCamera::Update()
{
    if (parent_id_ >= 0)
    {
        //Get the transform of parent
        XMFLOAT3 parent_pos = Manager::FindEntityByID(parent_id_)->GetTransform().position;
        if(look_at_parent_)
        {
            if(smoothing_)
            {
                target_.x += (parent_pos.x - target_.x) * 0.1f;
                target_.y += (parent_pos.y - target_.y) * 0.1f;
                target_.z += (parent_pos.z - target_.z) * 0.1f;
            }
            else
            {
                target_ = parent_pos;
            }
        }
        Transform::MoveTo(local_transform_, XMFLOAT3(offset_.x, offset_.y, offset_.z));
    }
}

void CCamera::Draw()
{
    if(active_)
    {
        DirectX::XMFLOAT3 up{0.0f, 1.0f, 0.0f};
        Transform world_transform = GetWorldTransform();
        DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&world_transform.position),
                                                                 DirectX::XMLoadFloat3(&target_),
                                                                 DirectX::XMLoadFloat3(&up));
        Renderer::SetViewMatrix(viewMatrix);

        DirectX::XMStoreFloat4x4(&view_matrix_, viewMatrix);

        //projection matrix
        DirectX::XMMATRIX projectionMatrix;
        projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
        DirectX::XMStoreFloat4x4(&projection_matrix_, projectionMatrix);

        Renderer::SetProjectionMatrix(projectionMatrix);
    }
}

void CCamera::Activate()
{
    active_ = true;
    Manager::SetActiveCamera(this);
}

void CCamera::Deactivate()
{
    active_ = false;
}
