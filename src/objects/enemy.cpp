#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"

#include "components/CCamera.h"
#include "components/CEnemyBehaviour.h"
#include "components/CModelRenderer.h"
#include "components/CRigidBody.h"
#include "components/CSphereCollider.h"
#include "components/CTransformConstraint.h"


void Enemy::Start()
{
    entity_ = Manager::MakeEntity("enemy");
    entity_->SetTag("Enemy");

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\player.obj");
    modelRenderer->Start();

    CSphereCollider* sphereCollider = new CSphereCollider();
    entity_->AddComponent(sphereCollider);
    sphereCollider->SetRadius(2.0f);
    sphereCollider->SetDynamic(true);
    sphereCollider->Start();

    CEnemyBehaviour* enemyBehaviour = new CEnemyBehaviour();
    entity_->AddComponent(enemyBehaviour);
    enemyBehaviour->Start();
}

