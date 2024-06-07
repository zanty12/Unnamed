#include "main.h"
#include "renderer.h"
#include "bullet.h"

#include "manager.h"
#include "components/bulletbehaviour.h"
#include "components/modelRenderer.h"
#include "components/rigidbody.h"

void Bullet::Start()
{
    entity_ = Manager::MakeEntity("bullet");
    entity_->GetTransform()->position = pos_;
    entity_->SetTag("Bullet");

    ModelRenderer* modelRenderer = new ModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\bullet.obj");
    modelRenderer->Start();

    RigidBody* rigidBody = new RigidBody();
    entity_->AddComponent(rigidBody);
    rigidBody->SetUseGravity(false);
    rigidBody->SetLinearVel(vel_);
    rigidBody->Start();

    BulletBehaviour* bulletBehaviour = new BulletBehaviour();
    entity_->AddComponent(bulletBehaviour);
    bulletBehaviour->Start();
}

void Bullet::Spawn()
{
    Start();
}
