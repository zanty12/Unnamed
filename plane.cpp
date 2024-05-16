#include "main.h"
#include "renderer.h"
#include "plane.h"

void Plane::Start()
{
    VERTEX_3D vertex[4];

    vertex[0].Position = DirectX::XMFLOAT3(-50.0f,0.0f,50.0f);
    vertex[0].Normal = DirectX::XMFLOAT3(0.0f,1.0f,0.0f);
    vertex[0].Diffuse = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
    vertex[0].TexCoord = DirectX::XMFLOAT2(0.0f,0.0f);

    vertex[1].Position = DirectX::XMFLOAT3(50.0f,0.0f,50.0f);
    vertex[1].Normal = DirectX::XMFLOAT3(0.0f,1.0f,0.0f);
    vertex[1].Diffuse = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
    vertex[1].TexCoord = DirectX::XMFLOAT2(20.0f,0.0f);

    vertex[2].Position = DirectX::XMFLOAT3(-50.0f,0.0f,-50.0f);
    vertex[2].Normal = DirectX::XMFLOAT3(0.0f,1.0f,0.0f);
    vertex[2].Diffuse = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
    vertex[2].TexCoord = DirectX::XMFLOAT2(0.0f,20.0f);

    vertex[3].Position = DirectX::XMFLOAT3(50.0f,0.0f,-50.0f);
    vertex[3].Normal = DirectX::XMFLOAT3(0.0f,1.0f,0.0f);
    vertex[3].Diffuse = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
    vertex[3].TexCoord = DirectX::XMFLOAT2(20.0f,20.0f);

    //vertex buffer
    D3D11_BUFFER_DESC buffer_desc;
    ZeroMemory(&buffer_desc,sizeof(buffer_desc));
    buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    buffer_desc.ByteWidth = sizeof(VERTEX_3D) * 4;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA subresource_data;
    ZeroMemory(&subresource_data,sizeof(subresource_data));
    subresource_data.pSysMem = vertex;

    Renderer::GetDevice()->CreateBuffer(&buffer_desc,&subresource_data,&vertex_buffer_);

    //Texture]
    DirectX::TexMetadata metadata;
    DirectX::ScratchImage scratch_image;
    DirectX::LoadFromWICFile(texture_path_.c_str(),DirectX::WIC_FLAGS_NONE,&metadata,scratch_image);
    DirectX::CreateShaderResourceView(Renderer::GetDevice(),scratch_image.GetImages(),scratch_image.GetImageCount(),metadata,&texture_);
    assert(texture_);

    Renderer::CreateVertexShader(&vertex_shader_,&vertex_layout_,vertex_shader_path_.c_str());
    Renderer::CreatePixelShader(&pixel_shader_,pixel_shader_path_.c_str());

}

void Plane::Update(Entity* parent)
{
    if(parent_id_ < 0)
    {
        //do nothing
    }
    else
    {

    }
}

void Plane::Draw()
{
    //input layout
    Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

    //shader
    Renderer::GetDeviceContext()->VSSetShader(vertex_shader_,nullptr,0);
    Renderer::GetDeviceContext()->PSSetShader(pixel_shader_,nullptr,0);

    //world matrix
    DirectX::XMMATRIX world,scale,rot,trans;
    scale = DirectX::XMMatrixScaling(transform_.scale.x,transform_.scale.y,transform_.scale.z);
    rot = DirectX::XMMatrixRotationRollPitchYaw(transform_.rotation.x,transform_.rotation.y,transform_.rotation.z);
    trans= DirectX::XMMatrixTranslation(transform_.position.x,transform_.position.y,transform_.position.z);
    world = scale * rot * trans;
    Renderer::SetWorldMatrix(world);

    //vertex buffer
    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    Renderer::GetDeviceContext()->IASetVertexBuffers(0,1,&vertex_buffer_,&stride,&offset);

    //material
    MATERIAL material;
    ZeroMemory(&material,sizeof(material));
    material.Diffuse = DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
    material.TextureEnable = true;
    Renderer::SetMaterial(material);

    //texture
    Renderer::GetDeviceContext()->PSSetShaderResources(0,1,&texture_);

    //primitive topology
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    //draw
    Renderer::GetDeviceContext()->Draw(4,0);
}


