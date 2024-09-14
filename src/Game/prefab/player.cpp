#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/CPlayerController.h"
#include "components/animationModel.h"
#include "components/CTransformConstraint.h"
#include <components/CPhysXRigidBody.h>
#include <components/CPhysXCapsule.h>

#include "components/CPlayerMenu.h"


void Player::Start()
{
    entity_ = Manager::MakeEntity("player");
    entity_->SetTag("Player");

    entity_->AddComponent(new CPlayerController());

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\player.obj");
    modelRenderer->Start();
	Transform* model = modelRenderer->GetLocalTransform();
	Transform::MoveTo(model, XMFLOAT3(0.0f, -1.0f, 0.0f));
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

	CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
	entity_->AddComponent(rigidBody);
	rigidBody->Start();
    //rigidBody->SetMass(0.0f);0
    rigidBody->LockAngularAxis(true,true,true);

	CPhysXCapsule* capsule = new CPhysXCapsule();
	capsule->SetDebugView(true);
	capsule->SetIsTrigger(false);
    Transform::ScaleTo(capsule->GetLocalTransform(), XMFLOAT3(1.0f, 2.0f, 1.0f));
	entity_->AddComponent(capsule);
	capsule->Start();

    /*CTransformConstraint* transformConstraint = new CTransformConstraint();
    entity_->AddComponent(transformConstraint);*/

    CAudio* audio = new CAudio();
    entity_->AddComponent(audio);
    audio->Load("asset/sound/wan.wav");

	CPlayerMenu* playerMenu = new CPlayerMenu();
	entity_->AddComponent(playerMenu);
	playerMenu->Start();
}


