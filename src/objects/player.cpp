
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

#include "components/controller.h"
#include "components/modelRenderer.h"



void Player::Start()
{
    entity_ = Manager::MakeEntity("player");
    ModelRenderer* modelRenderer = new ModelRenderer();
    entity_->AddComponent(modelRenderer);
    entity_->AddComponent(new Controller());
    modelRenderer->Load("asset\\model\\player.obj");
    Renderer::CreateVertexShader(&vertex_shader_,&vertex_layout_, "asset\\shader\\unlitTextureVS.cso");
    Renderer::CreatePixelShader(&pixel_shader_, "asset\\shader\\unlitTexturePS.cso");
}

Player::~Player()
{
    for (auto& component : entity_->GetComponents())
    {
        component->CleanUp();
        delete component;
    }
    vertex_layout_->Release();
    vertex_shader_->Release();
    pixel_shader_->Release();
}

void Player::Update()
{
}

void Player::Draw()
{
    //input layout
    Renderer::GetDeviceContext()->IASetInputLayout(vertex_layout_);

    //shader
    Renderer::GetDeviceContext()->VSSetShader(vertex_shader_, nullptr, 0);
    Renderer::GetDeviceContext()->PSSetShader(pixel_shader_, nullptr, 0);

    //world matrix
    XMMATRIX world,scale,rot,trans;
    Transform* transform = entity_->GetTransform();
    scale = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);
    rot = XMMatrixRotationRollPitchYaw(transform->rotation.x, transform->rotation.y, transform->rotation.z);
    trans = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);
    world = scale*rot*trans;
    Renderer::SetWorldMatrix(world);

    for(auto component : entity_->GetComponents())
    {
        if (component->GetType() == "ModelRenderer")
        {
            static_cast<ModelRenderer*>(component)->Draw();
        }
    }
}