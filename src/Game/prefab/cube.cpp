#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "cube.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/Shapes/CDirectXTKBox.h"
#include "components/CModelRenderer.h"
#include "components/PhysX/CPhysXBox.h"
#include "components/PhysX/CPhysXRigidBody.h"
#include "components/CTransformConstraint.h"
#include "components/CCubeBehaviour.h" 


void Cube::Start()
{
    entity_ = Manager::MakeEntity("Cube");
    entity_->SetTag("Cube");
	Transform::Copy(entity_->GetTransform(), transform_);

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\WoodenCrate.obj");
    Transform local = Transform{ XMFLOAT3{0.0f, -0.5f, 0.0f}, XMFLOAT3{0.2f, 0.2f, 0.2f}, XMFLOAT4{0.0f,0.0f,0.0f,1.0f} };
    modelRenderer->SetLocalTransform(local);
    /*CDirectXTKBox* box = new CDirectXTKBox();
    entity_->AddComponent(box);*/

    CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
    entity_->AddComponent(rigidBody);
    CPhysXBox* physXBox = new CPhysXBox();
    physXBox->SetMaterial(1.0f, 1.0f, 0.0f);
    entity_->AddComponent(physXBox);
    entity_->Start();
    physx::PxRigidActor* actor = rigidBody->GetActor();
    rigidBody->AddCollisionFilter("Cube");
    physXBox->SetQuery(false);
    if (actor->is<physx::PxRigidDynamic>())
    {
        physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();
        dynamicActor->putToSleep();
    }

	CCubeBehaviour* cubeBehaviour = new CCubeBehaviour();
	entity_->AddComponent(cubeBehaviour);
	cubeBehaviour->Start();
}

void Cube::Spawn() 
{
    Start();
}

