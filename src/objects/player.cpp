#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/custom/CPlayerController.h"
#include "components/animationModel.h"
#include "components/CTransformConstraint.h"


void Player::Start()
{
    entity_ = Manager::MakeEntity("player");
    entity_->SetTag("Player");
    Transform::SetQuaternionMode(entity_->GetTransform(),true);

    entity_->AddComponent(new CPlayerController());

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\player.obj");
    modelRenderer->Start();
    /*AnimationModel* animModel = new AnimationModel();
    animModel->Load("asset\\model\\Akai.fbx");
    entity_->AddComponent(animModel);
    animModel->Start();*/

    CCamera* camera = new CCamera();
    entity_->AddComponent(camera);
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->Activate();
    camera->Start();

    /*CRigidBody* rigidBody = new CRigidBody();
    entity_->AddComponent(rigidBody);
    rigidBody->Start();*/

    CTransformConstraint* transformConstraint = new CTransformConstraint();
    entity_->AddComponent(transformConstraint);

    CAudio* audio = new CAudio();
    entity_->AddComponent(audio);
    audio->Load("asset/sound/wan.wav");
}

