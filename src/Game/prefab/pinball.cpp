#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Pinball.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/CPinballBehaviour.h"
#include "components/animationModel.h"
#include "components/CTransformConstraint.h"
#include <components/CPhysXRigidBody.h>
#include <components/CPhysXCapsule.h>

#include "components/CPhysXSphere.h"

void Pinball::Start()
{
    entity_ = Manager::MakeEntity("Pinball");
    entity_->SetTag("Pinball");
	Transform::MoveTo(entity_->GetTransform(), XMFLOAT3(0.0f, 0.0f, -20.0f));

    /*CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\Pinball.obj");
    modelRenderer->Start();
	Transform* model = modelRenderer->GetLocalTransform();
	Transform::MoveTo(model, XMFLOAT3(0.0f, -1.0f, 0.0f));*/
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
    //rigidBody->LockAngularAxis(true,true,true);

	CPhysXSphere* sphere = new CPhysXSphere();
	sphere->SetDebugView(true);
	sphere->SetIsTrigger(false);
    Transform::ScaleTo(sphere->GetLocalTransform(), XMFLOAT3(1.0f, 1.0f, 1.0f));
	entity_->AddComponent(sphere);
	sphere->Start();

    /*CTransformConstraint* transformConstraint = new CTransformConstraint();
    entity_->AddComponent(transformConstraint);*/

    CAudio* audio = new CAudio();
    entity_->AddComponent(audio);
    audio->Load("asset/sound/wan.wav");

	CPinballBehaviour* pinballBehaviour = new CPinballBehaviour();
	entity_->AddComponent(pinballBehaviour);
	pinballBehaviour->Start();
}


