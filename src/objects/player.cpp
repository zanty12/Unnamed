
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
    modelRenderer->Start();
}

Player::~Player()
{
    delete entity_;
}

void Player::Update()
{
}
