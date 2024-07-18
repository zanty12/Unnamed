#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "CCamera.h"

void CCamera::Start()
{
    if (parent_id_ < 0)
    {
        position_ = DirectX::XMFLOAT3(0.0f + offset_.x, 0.0f + offset_.y, 0.0f + offset_.z);
    }
    else
    {
        //Get the transform of parent
        position_ = Manager::FindEntityByID(parent_id_)->GetTransform()->position;
        if(look_at_parent_)
            target_ = position_;
        position_.x += offset_.x;
        position_.y += offset_.y;
        position_.z += offset_.z;
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
        position_ = Manager::FindEntityByID(parent_id_)->GetTransform()->position;
        if(look_at_parent_)
        {
            if(smoothing_)
            {
                target_.x += (position_.x - target_.x) * 0.1;
                target_.y += (position_.y - target_.y) * 0.1;
                target_.z += (position_.z - target_.z) * 0.1;
            }
            else
            {
                target_ = position_;
            }
        }
        position_.x += offset_.x;
        position_.y += offset_.y;
        position_.z += offset_.z;
    }
}

void CCamera::Draw()
{
    if(active_)
    {
        DirectX::XMFLOAT3 up{0.0f, 1.0f, 0.0f};
        DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position_),
                                                                 DirectX::XMLoadFloat3(&target_),
                                                                 DirectX::XMLoadFloat3(&up));
        Renderer::SetViewMatrix(viewMatrix);

        DirectX::XMStoreFloat4x4(&view_matrix_, viewMatrix);

        //projection matrix
        DirectX::XMMATRIX projectionMatrix;
        projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

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
