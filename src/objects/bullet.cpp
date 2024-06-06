#include "main.h"
#include "renderer.h"
#include "bullet.h"

#include "manager.h"
#include "components/modelRenderer.h"
#include "components/rigidbody.h"

void Bullet::Start()
{
    entity_ = Manager::MakeEntity("bullet");
    entity_->SetTag("Bullet");
    ModelRenderer* modelRenderer = new ModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\bullet.obj");
    modelRenderer->Start();

    RigidBody* rigidBody = new RigidBody();
    entity_->AddComponent(rigidBody);
    rigidBody->SetUseGravity(false);
    rigidBody->Start();
    rigidBody->SetLinearVel(vel_);
}

