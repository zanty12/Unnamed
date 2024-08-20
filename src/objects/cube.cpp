#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "cube.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/CRigidBody.h"
#include "components/CTransformConstraint.h"


void Cube::Start()
{
    entity_ = Manager::MakeEntity("Cube");
    entity_->SetTag("Cube");
	Transform::Copy(entity_->GetTransform(), &transform_);

    CModelRenderer* modelRenderer = new CModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\roundedcube.obj");

    CRigidBody* rigidBody = new CRigidBody();
    entity_->AddComponent(rigidBody);

    CTransformConstraint* transformConstraint = new CTransformConstraint();
    entity_->AddComponent(transformConstraint);

    CAudio* audio = new CAudio();
    entity_->AddComponent(audio);
    audio->Load("asset/sound/wan.wav");
    entity_->Start();
}

void Cube::Spawn() 
{
    Start();
}

