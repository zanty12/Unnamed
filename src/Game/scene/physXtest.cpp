#include "physXtest.h"
#include "manager.h"
#include "system/PhysX_Impl.h"
#include "components/PhysX/CPhysXBox.h"
#include "components/PhysX/CPhysXSphere.h"
#include "components/PhysX/CPhysXRigidBody.h"
#include "components/CModelRenderer.h"
#include "components/Shapes/CPlane.h"
#include "components/CVideoTexture.h"
#include "components/depreciated/CRigidBody.h"
#include "prefab/pinball.h"
#include "prefab/player.h"


void physXtest::Setup()
{
    //create 500 boxes in a 10x10x5 grid
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                Entity* box = Manager::MakeEntity();
                Transform::MoveTo(box->GetTransform(), XMFLOAT3(i*1.1f, j*1.0f+0.5f, k*1.1f));
				//Transform::ScaleTo(box->GetTransform(), XMFLOAT3(0.5f, 0.5f, 0.5f));
                CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
                box->AddComponent(rigidBody);
                CPhysXBox* physXBox = new CPhysXBox();
                physXBox->SetDebugView(false);
                physXBox->SetSimulate(true);
                physXBox->SetMaterial(1.0f, 0.5f, 0.0f);
                box->AddComponent(physXBox);
                box->Start();
                physx::PxRigidActor* actor = rigidBody->GetActor();
                if(actor->is<physx::PxRigidDynamic>())
                {
                    physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();
                    dynamicActor->putToSleep();
                }
            }
        }
    }

    /*Entity* sphere = Manager::MakeEntity();
    Transform::MoveTo(sphere->GetTransform(), XMFLOAT3(2, 10, 0));
    sphere->AddComponent(new CPhysXRigidBody(true));
    CPhysXSphere* physXSphere = new CPhysXSphere();
    physXSphere->SetDebugView(true);
    sphere->AddComponent(physXSphere);
    sphere->Start();*/

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
    skybox->GetTransform().scale = XMFLOAT3(100, 100, 100);
    CModelRenderer* skybox_renderer = new CModelRenderer();
    skybox_renderer->Load("asset\\model\\sky.obj");
    skybox->AddComponent(skybox_renderer);
    skybox->Start();

    Pinball* player = new Pinball();
    player->Start();
    //delete setup object after creating entity
    delete player;
}
