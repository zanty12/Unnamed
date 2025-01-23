#include "main.h"
#include "renderer.h"
#include "bullet.h"

#include "manager.h"
#include "components/CBulletBehaviour.h"
#include "components/CModelRenderer.h"
#include <components/PhysX/CPhysXSphere.h>
#include <components/PhysX/CPhysXRigidBody.h>

void Bullet::Start()
{
    entity_ = Manager::MakeEntity("bullet");
    entity_->GetTransform().position = pos_;
    entity_->SetTag("Bullet");

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\bullet.obj");
    modelRenderer->Start();

    CBulletBehaviour* bulletBehaviour = new CBulletBehaviour();
    entity_->AddComponent(bulletBehaviour);

	CPhysXRigidBody* rigidBody = new CPhysXRigidBody();
	rigidBody->SetDynamic(true);
	entity_->AddComponent(rigidBody);

	CPhysXSphere* sphere = new CPhysXSphere();
    sphere->SetIsTrigger(true);
	sphere->SetDebugView(true);
	entity_->AddComponent(sphere);

	entity_->Start();
	rigidBody->SetLinearVelocity(vel_);
	rigidBody->SetEnableGravity(false);
}

void Bullet::Spawn()
{
    Start();
}
