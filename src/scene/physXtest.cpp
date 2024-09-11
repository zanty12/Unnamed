#include "physXtest.h"
#include "manager.h"
#include "system/PhysX_Impl.h"
#include "components/CPhysXBox.h"
#include "components/CPhysXSphere.h"
#include "components/CPhysXRigidBody.h"
#include "components/CModelRenderer.h"
#include "objects/player.h"


void physXtest::Setup()
{
    Entity* box = Manager::MakeEntity();
    Transform::MoveTo(box->GetTransform(), XMFLOAT3(0, 5, 0));
    box->AddComponent(new CPhysXRigidBody(true));
    CPhysXBox* physXBox = new CPhysXBox();
    physXBox->SetDebugView(true);
    box->AddComponent(physXBox);

    /*CModelRenderer* modelRenderer = new CModelRenderer();
    box->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\roundedcube.obj");*/
    box->Start();

    Entity* sphere = Manager::MakeEntity();
    Transform::MoveTo(sphere->GetTransform(), XMFLOAT3(2, 5, 0));
    sphere->AddComponent(new CPhysXRigidBody(true));
    CPhysXSphere* physXSphere = new CPhysXSphere();
    physXSphere->SetDebugView(true);
    sphere->AddComponent(physXSphere);

    sphere->Start();

    PhysX_Impl::GetScene()->addActor(*physx::PxCreatePlane(
    *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 0),
    *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f))
);

    Player* player = new Player();
    player->Start();
    //delete setup object after creating entity
    delete player;
}
