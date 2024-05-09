#include "camera.h"

#include "main.h"
#include "renderer.h"

void Camera::Start()
{
    if(parent_id_ > -1)
    {
        //Get the parent's transform
    }
    else
    {
        position_ = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);
    }
    target_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void Camera::CleanUp()
{

}

void Camera::Update()
{

}

void Camera::Draw()
{
    DirectX::XMFLOAT3 up{0.0f,1.0f,0.0f};
    DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position_), DirectX::XMLoadFloat3(&target_), DirectX::XMLoadFloat3(&up));
    Renderer::SetViewMatrix(viewMatrix);

    DirectX::XMStoreFloat4x4(&view_matrix_, viewMatrix);

    //projection matrix
    DirectX::XMMATRIX projectionMatrix;
    projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, (float) SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

    Renderer::SetProjectionMatrix(projectionMatrix);
}