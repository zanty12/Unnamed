#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

#include "components/camera.h"
#include "components/controller.h"
#include "components/modelRenderer.h"
#include "components/rigidbody.h"
#include "components/transformconstraint.h"


void Player::Start()
{
    entity_ = Manager::MakeEntity("player");
    entity_->SetTag("Player");

    entity_->AddComponent(new Controller());

    ModelRenderer* modelRenderer = new ModelRenderer();
    entity_->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\player.obj");
    modelRenderer->Start();

    Camera* camera = new Camera();
    entity_->AddComponent(camera);
    camera->Start();

    RigidBody* rigidBody = new RigidBody();
    entity_->AddComponent(rigidBody);
    rigidBody->Start();

    TransformConstraint* transformConstraint = new TransformConstraint();
    entity_->AddComponent(transformConstraint);
}

