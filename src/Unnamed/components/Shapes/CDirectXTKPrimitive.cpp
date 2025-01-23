#include "CDirectXTKPrimitive.h"
#include <iostream>
#include "renderer.h"
#include "manager.h"
#include "components/CTexture.h"

void CDirectXTKPrimitive::Update()
{
    original_view_ = Manager::GetActiveCamera()->GetViewMatrix();
    original_proj_ = Manager::GetActiveCamera()->GetProjectionMatrix();
    XMMATRIX world, scale, rot, trans;
    Transform world_transform = GetWorldTransform();
    rot = XMMatrixRotationQuaternion(XMLoadFloat4(&world_transform.quaternion));
    trans = XMMatrixTranslation(world_transform.position.x, world_transform.position.y, world_transform.position.z);
    scale = XMMatrixScaling(world_transform.scale.x, world_transform.scale.y, world_transform.scale.z);
    world = scale * rot * trans;
    XMStoreFloat4x4(&world_matrix_, world);
}


void CDirectXTKPrimitive::Draw()
{
    XMMATRIX viewMatrix = XMLoadFloat4x4(&original_view_);
    XMMATRIX projMatrix = XMLoadFloat4x4(&original_proj_);
    XMMATRIX world = XMLoadFloat4x4(&world_matrix_);
    switch (draw_type_)
    {
    case SOLID:
    {
        primitive_->Draw(world, viewMatrix, projMatrix, color_, nullptr, false);
        break;
    }
    case WIREFRAME:
    {
        primitive_->Draw(world, viewMatrix, projMatrix, color_, nullptr, true);
        break;
    }
    case TEXTURED:
    {
        if (texture_)
            primitive_->Draw(world, viewMatrix, projMatrix, color_, texture_->GetView(), false);
        break;
    }
    default:
    {
        primitive_->Draw(world, viewMatrix, projMatrix, Colors::Red, nullptr, true);
        break;
    }
    }
}

