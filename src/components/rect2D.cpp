#include "main.h"
#include "renderer.h"
#include "rect2D.h"

#include "entity.h"

void Rect2D::Start()
{
    //Read texture
    TexMetadata metadata;
    ScratchImage image;
    LoadFromWICFile(texture_path_.c_str(), WIC_FLAGS_NONE, &metadata, image);
    CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &texture_);
    assert(texture_);

    Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, vertex_shader_path_.c_str());
    Renderer::CreatePixelShader(&pixel_shader_, pixel_shader_path_.c_str());
}

void Rect2D::Update(Entity* parent)
{
    if (parent == nullptr)
    {
    }
    else
    {
        //update pos to parent pos
        Transform::Copy(&transform_,parent->GetTransform());
    }
}

void Rect2D::Draw()
{
    if(vertex_buffer_)
        vertex_buffer_->Release();
    //set vertex buffer
    VERTEX_3D vertex[4];

    vertex[0].Position = DirectX::XMFLOAT3((transform_.position.x - (100.0f * transform_.scale.x / 2.0f)),
                                           transform_.position.y - 100.0f *transform_.scale.y / 2.0f, 0.0f);
    vertex[0].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[0].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[0].TexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);

    vertex[1].Position = DirectX::XMFLOAT3(transform_.position.x + 100.0f *transform_.scale.x / 2.0f,
                                           transform_.position.y - 100.0f *transform_.scale.y / 2.0f, 0.0f);
    vertex[1].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[1].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[1].TexCoord = DirectX::XMFLOAT2(1.0f, 0.0f);

    vertex[2].Position = DirectX::XMFLOAT3(transform_.position.x - 100.0f *transform_.scale.x / 2.0f,
                                           transform_.position.y + 100.0f *transform_.scale.y / 2.0f, 0.0f);
    vertex[2].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[2].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[2].TexCoord = DirectX::XMFLOAT2(0.0f, 1.0f);

    vertex[3].Position = DirectX::XMFLOAT3(transform_.position.x + 100.0f *transform_.scale.x / 2.0f,
                                           transform_.position.y + 100.0f *transform_.scale.y / 2.0f, 0.0f);
    vertex[3].Normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    vertex[3].Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    vertex[3].TexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);

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
    Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture_);
    //material
    MATERIAL material;
    ZeroMemory(&material,sizeof(material));
    material.Diffuse = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
    material.TextureEnable = true;
    Renderer::SetMaterial(material);
    //primitive topology
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //draw
    Renderer::GetDeviceContext()->Draw(4, 0);
}
