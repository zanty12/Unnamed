#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

void Camera::Start()
{
    if (parent_id_ < 0)
    {
        position_ = DirectX::XMFLOAT3(0.0f + offset.x, 0.0f + offset.y, 0.0f + offset.z);
        target_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    }
    else
    {
        //Get the transform of parent
        position_ = Manager::FindEntity(parent_id_)->GetTransform()->position;
        target_ = position_;
        position_.x += offset.x;
        position_.y += offset.y;
        position_.z += offset.z;
    }
}

void Camera::CleanUp()
{
}

void Camera::Update()
{
    if (parent_id_ >= 0)
    {
        //Get the transform of parent
        position_ = Manager::FindEntity(parent_id_)->GetTransform()->position;
        target_ = position_;
        position_.x += offset.x;
        position_.y += offset.y;
        position_.z += offset.z;
    }
}

void Camera::Draw()
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
