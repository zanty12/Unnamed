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

#include "components/CDirectXTKSphere.h"
#include "components/CPhysXSphere.h"

void Pinball::Start()
{
	entity_ = Manager::MakeEntity("Pinball");
	entity_->SetTag("Pinball");
	Transform::MoveTo(entity_->GetTransform(), XMFLOAT3(0.0f, 0.5f, -9.0f));

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
	rigidBody->SetMass(10.0f);
	//rigidBody->LockAngularAxis(true,true,true);
	physx::PxRigidActor* actor = rigidBody->GetActor();
	if (actor->is<physx::PxRigidDynamic>())
	{
		physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();
		//actor->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, false);
		dynamicActor->putToSleep();
	}

	CPhysXSphere* sphere = new CPhysXSphere();
	sphere->SetDebugView(false);
	sphere->SetIsTrigger(false);
	sphere->SetRadius(1.5f);
	Transform::ScaleTo(sphere->GetLocalTransform(), XMFLOAT3(1.0f, 1.0f, 1.0f));
	entity_->AddComponent(sphere);
	sphere->Start();

	CDirectXTKSphere* directXTKSphere = new CDirectXTKSphere();
	directXTKSphere->SetRadius(1.5f);
	entity_->AddComponent(directXTKSphere);
	directXTKSphere->SetColor(SimpleMath::Color(1.0f, 0.0f, 0.0f, 1.0f));
	directXTKSphere->Start();

	/*CTransformConstraint* transformConstraint = new CTransformConstraint();
	entity_->AddComponent(transformConstraint);*/

	CAudio* audio = new CAudio();
	entity_->AddComponent(audio);
	audio->Load("asset/sound/wan.wav");

	CPinballBehaviour* pinballBehaviour = new CPinballBehaviour();
	entity_->AddComponent(pinballBehaviour);
	pinballBehaviour->Start();
}


