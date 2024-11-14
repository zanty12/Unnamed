#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "entity.h"
#include "CRect2D.h"

#include "CSprite2D.h"

void CRect2D::Start()
{
    //Read texture
    //texture_->Start();

    Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, vertex_shader_path_.c_str());
    Renderer::CreatePixelShader(&pixel_shader_, pixel_shader_path_.c_str());
    if (texture_->GetType() == "Sprite2D")
    {
        //get uv
        CSprite2D* sprite = dynamic_cast<CSprite2D*>(texture_);
        start_uv_ = sprite->GetStartUV();
        end_uv_ = sprite->GetEndUV();
    }
    else
    {
        start_uv_ = XMFLOAT2(0.0f, 0.0f);
        end_uv_ = XMFLOAT2(1.0f, 1.0f);
    }
}

void CRect2D::Update()
{
    //if texture is sprite, get uv
    if (texture_->GetType() == "Sprite2D")
    {
        //get uv
        CSprite2D* sprite = dynamic_cast<CSprite2D*>(texture_);
        start_uv_ = sprite->GetStartUV();
        end_uv_ = sprite->GetEndUV();
    }
}

void CRect2D::Draw()
{
    if (vertex_buffer_)
        vertex_buffer_->Release();
    //set vertex buffer
    VERTEX_3D vertex[4];
	Transform world_transform = GetWorldTransform();

    vertex[0].Position = DirectX::XMFLOAT3((world_transform.position.x - (100.0f * world_transform.scale.x / 2.0f)),
        world_transform.position.y - 100.0f * world_transform.scale.y / 2.0f, 0.0f);
    vertex[0].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[0].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[0].TexCoord = DirectX::XMFLOAT2(start_uv_.x, start_uv_.y);

    vertex[1].Position = DirectX::XMFLOAT3(world_transform.position.x + 100.0f * world_transform.scale.x / 2.0f,
        world_transform.position.y - 100.0f * world_transform.scale.y / 2.0f, 0.0f);
    vertex[1].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[1].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[1].TexCoord = DirectX::XMFLOAT2(end_uv_.x, start_uv_.y);

    vertex[2].Position = DirectX::XMFLOAT3(world_transform.position.x - 100.0f * world_transform.scale.x / 2.0f,
        world_transform.position.y + 100.0f * world_transform.scale.y / 2.0f, 0.0f);
    vertex[2].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[2].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[2].TexCoord = DirectX::XMFLOAT2(start_uv_.x, end_uv_.y);

    vertex[3].Position = DirectX::XMFLOAT3(world_transform.position.x + 100.0f * world_transform.scale.x / 2.0f,
        world_transform.position.y + 100.0f * world_transform.scale.y / 2.0f, 0.0f);
    vertex[3].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[3].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[3].TexCoord = DirectX::XMFLOAT2(end_uv_.x, end_uv_.y);

    D3D11_BUFFER_DESC bd{};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(VERTEX_3D) * 4;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA sd{};
    sd.pSysMem = vertex;

    Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertex_buffer_);
    //input layout
    Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);
    //shader
    Renderer::GetDeviceContext()->VSSetShader(vertex_shader_,NULL, 0);
    Renderer::GetDeviceContext()->PSSetShader(pixel_shader_,NULL, 0);
    //matrix
    Renderer::SetWorldViewProjection2D();
    //vertex buffer
    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
    //texture
    ID3D11ShaderResourceView* view = texture_->GetView();
    Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &view);
    //material
    MATERIAL material;
    ZeroMemory(&material, sizeof(material));
    material.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    material.TextureEnable = true;
    Renderer::SetMaterial(material);
    //primitive topology
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //draw
    Renderer::GetDeviceContext()->Draw(4, 0);
}
