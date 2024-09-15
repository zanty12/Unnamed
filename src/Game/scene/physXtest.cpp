#include "physXtest.h"
#include "manager.h"
#include "system/PhysX_Impl.h"
#include "components/CPhysXBox.h"
#include "components/CPhysXSphere.h"
#include "components/CPhysXRigidBody.h"
#include "components/CModelRenderer.h"
#include "components/CPlane.h"
#include "components/CVideoTexture.h"
#include "prefab/player.h"


void physXtest::Setup()
{
    //create 125 boxes in a 5x5x5 grid
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                Entity* box = Manager::MakeEntity();
                Transform::MoveTo(box->GetTransform(), XMFLOAT3(i*1.1f, j*1.1f, k*1.1f));
				Transform::ScaleTo(box->GetTransform(), XMFLOAT3(0.5f, 0.5f, 0.5f));
                box->AddComponent(new CPhysXRigidBody(true));
                CPhysXBox* physXBox = new CPhysXBox();
                physXBox->SetDebugView(true);
                physXBox->SetMaterial(1.0f, 0.5f, 0.0f);
                box->AddComponent(physXBox);
                box->Start();
            }
        }
    }

    Entity* sphere = Manager::MakeEntity();
    Transform::MoveTo(sphere->GetTransform(), XMFLOAT3(2, 10, 0));
    sphere->AddComponent(new CPhysXRigidBody(true));
    CPhysXSphere* physXSphere = new CPhysXSphere();
    physXSphere->SetDebugView(true);
    sphere->AddComponent(physXSphere);
    sphere->Start();

    //Create a plane
    Entity* plane = Manager::MakeEntity("plane");
    CPlane* planecomponent = new CPlane();
    CVideoTexture* video_texture = new CVideoTexture("asset/video/banana.mp4");
    video_texture->SetLoop(1);
    planecomponent->SetTexture(video_texture);
    plane->AddComponent(planecomponent);
    plane->AddComponent(video_texture);
    plane->Start();
    planecomponent->SetEndUV(XMFLOAT2(10.0f,10.0f));
    PhysX_Impl::GetScene()->addActor(*physx::PxCreatePlane(
    *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 0),
    *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f))
    );

    //skybox
    Entity* skybox = Manager::MakeEntity("skybox");
    skybox->GetTransform()->scale = XMFLOAT3(100, 100, 100);
    CModelRenderer* skybox_renderer = new CModelRenderer();
    skybox_renderer->Load("asset\\model\\sky.obj");
    skybox->AddComponent(skybox_renderer);
    skybox->Start();

    Player* player = new Player();
    player->Start();
    //delete setup object after creating entity
    delete player;
}
