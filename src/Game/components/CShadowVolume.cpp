#include "CShadowVolume.h"

#include "entity.h"
#include "system/renderPL.h"

void CShadowVolume::Start()
{
    model_renderer_ = new CModelRenderer();
    model_renderer_->Load("asset\\model\\sphere_smooth.obj");
    //add to entity
    model_renderer_->AttachTo(parent_id_,parent_entity_);
    model_renderer_->Start();
    //remove to prevent double drawing
    RenderPL::RemoveDrawable(model_renderer_);

    Renderer::CreateVertexShader(&vertex_shader_, &vertex_layout_, "asset\\shader\\unlitTextureVS.cso");
    Renderer::CreatePixelShader(&pixel_shader_, "asset\\shader\\unlitTexturePS.cso");

    TexMetadata metadata;
    ScratchImage image;
    LoadFromWICFile(L"asset\\texture\\earthenvmap.png", WIC_FLAGS_NONE, &metadata, image);
    CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &env_texture_);
    assert(env_texture_);
}

void CShadowVolume::Update()
{
}

void CShadowVolume::Draw()
{
    Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);
    Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, nullptr, 0);
    Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, nullptr, 0);

    Transform world_transform = GetWorldTransform();
    XMMATRIX world, scale, rot, trans;
    scale = XMMatrixScaling(world_transform.scale.x, world_transform.scale.y, world_transform.scale.z);
    rot = XMMatrixRotationQuaternion(XMLoadFloat4(&world_transform.quaternion));
    trans = XMMatrixTranslation(world_transform.position.x, world_transform.position.y, world_transform.position.z);
    world = scale * rot * trans;
    Renderer::SetWorldMatrix(world);

    //Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &env_texture_);

    Renderer::SetBlendMaskEnable(true);

    Renderer::SetStencilEnable(true);

    Renderer::SetCullEnable(false);

    // 頂点バッファ設定
    MODEL* model = model_renderer_->GetModel();
    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &model->VertexBuffer, &stride, &offset);

    // インデックスバッファ設定
    Renderer::GetDeviceContext()->IASetIndexBuffer(model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // プリミティブトポロジ設定
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    for (unsigned int i = 0; i < model->SubsetNum; i++)
    {
        // マテリアル設定
        Renderer::SetMaterial(model->SubsetArray[i].Material.Material);

        // テクスチャ設定
        if (model->SubsetArray[i].Material.Texture)
            Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &model->SubsetArray[i].Material.Texture);

        // ポリゴン描画
        Renderer::GetDeviceContext()->DrawIndexed(model->SubsetArray[i].IndexNum, model->SubsetArray[i].StartIndex,
                                                  0);
    }

    Renderer::SetBlendMaskEnable(false);

    Renderer::SetDepthEnable(true);

    Renderer::SetCullEnable(true);
}

void CShadowVolume::CleanUp()
{
    delete model_renderer_;
    vertex_shader_->Release();
    pixel_shader_->Release();
    vertex_layout_->Release();
    env_texture_->Release();
}
