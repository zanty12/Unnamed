#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Pinball.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/CPinballBehaviour.h"
#include "components/CAnimationModel.h"
#include "components/CTransformConstraint.h"
#include <components/PhysX/CPhysXRigidBody.h>

#include "components/Shapes/CDirectXTKSphere.h"
#include "components/PhysX/CPhysXSphere.h"

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

	CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
	entity_->AddComponent(rigidBody);



	CPhysXSphere* sphere = new CPhysXSphere();
	sphere->SetDebugView(false);
	sphere->SetIsTrigger(false);

	Transform::ScaleTo(sphere->GetLocalTransform(), XMFLOAT3(1.0f, 1.0f, 1.0f));
	entity_->AddComponent(sphere);

	CDirectXTKSphere* directXTKSphere = new CDirectXTKSphere();

	entity_->AddComponent(directXTKSphere);


	CAudio* audio = new CAudio();
	entity_->AddComponent(audio);
	audio->Load("asset/sound/wan.wav");

	CPinballBehaviour* pinballBehaviour = new CPinballBehaviour();
	entity_->AddComponent(pinballBehaviour);

	entity_->Start();

	sphere->SetRadius(1.5f);
	directXTKSphere->SetRadius(1.5f);
	directXTKSphere->SetColor(SimpleMath::Color(1.0f, 0.0f, 0.0f, 1.0f));
	//rigidBody->LockAngularAxis(true,true,true);
	rigidBody->SetMass(10.0f);
	physx::PxRigidActor* actor = rigidBody->GetActor();
	if (actor->is<physx::PxRigidDynamic>())
	{
		physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();
		//actor->setActorFlag(physx::PxActorFlag::eDISABLE_SIMULATION, false);
		dynamicActor->putToSleep();
	}
}


