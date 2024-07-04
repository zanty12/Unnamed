#include "main.h"
#include "renderer.h"
#include "bullet.h"

#include "manager.h"
#include "components/CBulletBehaviour.h"
#include "components/CModelRenderer.h"
#include "components/CRigidBody.h"
#include "components/CSphereCollider.h"

void Bullet::Start()
{
    entity_ = Manager::MakeEntity("bullet");
    entity_->GetTransform()->position = pos_;
    entity_->SetTag("Bullet");

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\bullet.obj");
    modelRenderer->Start();

    CRigidBody* rigidBody = new CRigidBody();
    entity_->AddComponent(rigidBody);
    rigidBody->SetUseGravity(false);
    rigidBody->SetLinearVel(vel_);
    rigidBody->Start();

    CSphereCollider* sphereCollider = new CSphereCollider();
    entity_->AddComponent(sphereCollider);
    sphereCollider->SetRadius(0.5f);
    sphereCollider->SetDynamic(true);
    sphereCollider->Start();

    CBulletBehaviour* bulletBehaviour = new CBulletBehaviour();
    entity_->AddComponent(bulletBehaviour);
    bulletBehaviour->Start();
}

void Bullet::Spawn()
{
    Start();
}
