﻿#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "CPlane.h"

#include "CSprite2D.h"
#include "entity.h"


void CPlane::Start()
{
    VERTEX_3D vertex[4];

    vertex[0].Position = DirectX::XMFLOAT3(-50.0f, 0.0f, 50.0f);
    vertex[0].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[0].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[0].TexCoord = DirectX::XMFLOAT2(start_uv_.x, start_uv_.y);

    vertex[1].Position = DirectX::XMFLOAT3(50.0f, 0.0f, 50.0f);
    vertex[1].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[1].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[1].TexCoord = DirectX::XMFLOAT2(end_uv_.x, start_uv_.y);

    vertex[2].Position = DirectX::XMFLOAT3(-50.0f, 0.0f, -50.0f);
    vertex[2].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[2].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[2].TexCoord = DirectX::XMFLOAT2(start_uv_.x, end_uv_.y);

    vertex[3].Position = DirectX::XMFLOAT3(50.0f, 0.0f, -50.0f);
    vertex[3].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[3].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[3].TexCoord = DirectX::XMFLOAT2(end_uv_.x, end_uv_.y);

    //vertex buffer
    D3D11_BUFFER_DESC buffer_desc;
    ZeroMemory(&buffer_desc, sizeof(buffer_desc));
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.ByteWidth = sizeof(VERTEX_3D) * 4;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA subresource_data;
    ZeroMemory(&subresource_data, sizeof(subresource_data));
    subresource_data.pSysMem = vertex;

    Renderer::GetDevice()->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_);

    Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, vertex_shader_path_.c_str());
    Renderer::CreatePixelShader(&pixel_shader_, pixel_shader_path_.c_str());
}

void CPlane::Update()
{
    //find parent
    Entity* parent = Manager::FindEntity(parent_id_);

    if (parent_id_ < 0 || parent == nullptr)
    {
        //do nothing
    }
    else
    {
        Transform::Copy(&transform_, parent->GetTransform());
    }
    //if texture is sprite, get uv
    if (texture_->GetType() == "Sprite2D")
    {
        //get uv
        CSprite2D* sprite = dynamic_cast<CSprite2D*>(texture_);
        start_uv_ = sprite->GetStartUV();
        end_uv_ = sprite->GetEndUV();
    }
}

void CPlane::Draw()
{
    if (vertex_buffer_)
        vertex_buffer_->Release();
    VERTEX_3D vertex[4];
    vertex[0].Position = DirectX::XMFLOAT3(-50.0f, 0.0f, 50.0f);
    vertex[0].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[0].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[0].TexCoord = DirectX::XMFLOAT2(start_uv_.x, start_uv_.y);

    vertex[1].Position = DirectX::XMFLOAT3(50.0f, 0.0f, 50.0f);
    vertex[1].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[1].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[1].TexCoord = DirectX::XMFLOAT2(end_uv_.x, start_uv_.y);

    vertex[2].Position = DirectX::XMFLOAT3(-50.0f, 0.0f, -50.0f);
    vertex[2].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[2].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[2].TexCoord = DirectX::XMFLOAT2(start_uv_.x, end_uv_.y);

    vertex[3].Position = DirectX::XMFLOAT3(50.0f, 0.0f, -50.0f);
    vertex[3].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    vertex[3].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[3].TexCoord = DirectX::XMFLOAT2(end_uv_.x, end_uv_.y);

    //vertex buffer
    D3D11_BUFFER_DESC buffer_desc;
    ZeroMemory(&buffer_desc, sizeof(buffer_desc));
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.ByteWidth = sizeof(VERTEX_3D) * 4;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA subresource_data;
    ZeroMemory(&subresource_data, sizeof(subresource_data));
    subresource_data.pSysMem = vertex;

    Renderer::GetDevice()->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_);
    //input layout
    Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

    //shader
    Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, nullptr, 0);
    Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, nullptr, 0);

    //world matrix
    if (!billboard_)
    {
        DirectX::XMMATRIX world, scale, rot, trans;
        scale = DirectX::XMMatrixScaling(transform_.scale.x, transform_.scale.y, transform_.scale.z);
        rot = DirectX::XMMatrixRotationRollPitchYaw(transform_.rotation.x, transform_.rotation.y,
                                                    transform_.rotation.z);
        trans = DirectX::XMMatrixTranslation(transform_.position.x, transform_.position.y, transform_.position.z);
        world = scale * rot * trans;
        Renderer::SetWorldMatrix(world);
    }
    else
    {
        XMFLOAT4X4 view = Manager::GetActiveCamera()->GetViewMatrix();
        XMMATRIX inv_view = XMLoadFloat4x4(&view);
        inv_view = XMMatrixInverse(nullptr, inv_view);
        inv_view.r[3].m128_f32[0] = 0.0f;
        inv_view.r[3].m128_f32[1] = 0.0f;
        inv_view.r[3].m128_f32[2] = 0.0f;

        DirectX::XMMATRIX world,rot, scale, trans;
        scale = DirectX::XMMatrixScaling(transform_.scale.x, transform_.scale.y, transform_.scale.z);
        rot = DirectX::XMMatrixRotationRollPitchYaw(transform_.rotation.x, transform_.rotation.y,
                                                    transform_.rotation.z);
        trans = DirectX::XMMatrixTranslation(transform_.position.x, transform_.position.y, transform_.position.z);
        world = scale * rot*inv_view * trans;
        Renderer::SetWorldMatrix(world);
    }

    //vertex buffer
    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);

    //material
    MATERIAL material;
    ZeroMemory(&material, sizeof(material));
    material.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    material.TextureEnable = true;
    Renderer::SetMaterial(material);

    //texture
    ID3D11ShaderResourceView* view = texture_->GetView();
    Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &view);

    //primitive topology
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    //draw
    Renderer::GetDeviceContext()->Draw(4, 0);
}