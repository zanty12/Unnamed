#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/CPlayerController.h"
#include "components/CAnimationModel.h"
#include "components/CTransformConstraint.h"
#include <components/CPhysXRigidBody.h>
#include <components/CPhysXCapsule.h>

#include "components/CPlayerMenu.h"


void Player::Start()
{
    entity_ = Manager::MakeEntity("player");
    entity_->SetTag("Player");
    Transform::MoveTo(entity_->GetTransform(), XMFLOAT3(0.0f, 0.5f, -20.0f));
	Transform::ScaleTo(entity_->GetTransform(), XMFLOAT3(0.01f, 0.01f, 0.01f));

    entity_->AddComponent(new CPlayerController());

    /*CModelRenderer* modelRenderer = new CModelRenderer();
	modelRenderer->GetLocalTransform()->scale = XMFLOAT3(100.0f, 100.0f, 100.0f);
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\player.obj");
    modelRenderer->Start();
	Transform* model = modelRenderer->GetLocalTransform();
	Transform::MoveTo(model, XMFLOAT3(0.0f, -1.0f, 0.0f));*/
    CAnimationModel* animModel = new CAnimationModel();
    animModel->Load("asset\\model\\Akai.fbx");
	animModel->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	animModel->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");
    entity_->AddComponent(animModel);
	//rotate model by 180 degrees
	Transform::RotateToQuat(animModel->GetLocalTransform(), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f));
    //animModel->Start();

    CCamera* camera = new CCamera();
    entity_->AddComponent(camera);
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->Activate();


    CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
    entity_->AddComponent(rigidBody);
    //rigidBody->SetMass(0.0f);0


    CPhysXCapsule* capsule = new CPhysXCapsule();
    capsule->SetDebugView(false);
    capsule->SetIsTrigger(false);
    Transform::ScaleTo(capsule->GetLocalTransform(), XMFLOAT3(100.0f, 200.0f, 100.0f));
    entity_->AddComponent(capsule);


    /*CTransformConstraint* transformConstraint = new CTransformConstraint();
    entity_->AddComponent(transformConstraint);*/

    CAudio* audio = new CAudio();
    entity_->AddComponent(audio);
    audio->Load("asset/sound/wan.wav");

    CPlayerMenu* playerMenu = new CPlayerMenu();
    entity_->AddComponent(playerMenu);

    entity_->Start();
    rigidBody->LockAngularAxis(true, true, true);
}
