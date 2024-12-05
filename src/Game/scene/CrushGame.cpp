#include "CrushGame.h"
#include "physXtest.h"
#include "manager.h"
#include "system/PhysX_Impl.h"
#include "components/CPhysXBox.h"
#include "components/CPhysXSphere.h"
#include "components/CPhysXRigidBody.h"
#include "components/CModelRenderer.h"
#include "components/CPlane.h"
#include "components/CVideoTexture.h"
#include "prefab/cube.h"
#include "prefab/pinball.h"
#include "prefab/player.h"
#include "gamemode/GMCrush.h"

#include "components/CText2D.h"


void CrushGame::Setup()
{
    //create 125 boxes in a 5x5x5 grid
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                Cube* box = new Cube();
                Transform transform = Transform{ XMFLOAT3{(float)i * 1.1f, (float)j+0.5f, (float)k * 1.1f}, XMFLOAT3{1.0f, 1.0f, 1.0f}, XMFLOAT4{0.0f, 0.0f, 0.0f,1.0f} };
                box->SetTransform(transform);
                box->Start();
                delete box;
                
				count++;
            }
        }
    }
    GMCrush* gameMode = dynamic_cast<GMCrush*> (Manager::GetGameMode());
    if (gameMode) {
		gameMode->SetBlocks(count);
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
    Transform::MoveTo(plane->GetTransform(), XMFLOAT3(0, -0.5f, 0));
    Transform::ScaleTo(plane->GetTransform(), XMFLOAT3(5.0f, 1.0f, 5.0f));
    CPlane* planecomponent = new CPlane();
    CVideoTexture* video_texture = new CVideoTexture("asset/video/banana.mp4");
    video_texture->SetLoop(1);
    planecomponent->SetTexture(video_texture);
    plane->AddComponent(planecomponent);
    plane->AddComponent(video_texture);
    //add rigidbody
    CPhysXRigidBody* plane_rigid_body = new CPhysXRigidBody(false);
    plane->AddComponent(plane_rigid_body);
    CPhysXBox* plane_physXBox = new CPhysXBox();
    plane_physXBox->SetDebugView(false);
    plane->AddComponent(plane_physXBox);
    Transform::ScaleTo(plane_physXBox->GetLocalTransform(), XMFLOAT3(4.0f, 1.0f, 4.0f));
    plane->Start();
    planecomponent->SetEndUV(XMFLOAT2(1.0f, 1.0f));
    /*PhysX_Impl::GetScene()->addActor(*physx::PxCreatePlane(
            *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 0),
            *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f))
    );*/

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

    //Create Surrounding Walls
    Entity* wall1 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall1->GetTransform(), XMFLOAT3(-10.0f, 5.0f, 0));
    Transform::ScaleTo(wall1->GetTransform(), XMFLOAT3(0.1f, 10.0f, 20.0f));
    CPhysXRigidBody* wall_rigid_body = new CPhysXRigidBody(false);
    wall1->AddComponent(wall_rigid_body);
    CPhysXBox* wall_physXBox = new CPhysXBox();
    wall_physXBox->SetDebugView(true);
    wall1->AddComponent(wall_physXBox);
    wall1->Start();

    Entity* wall2 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall2->GetTransform(), XMFLOAT3(10.0f, 5.0f, 0));
    Transform::ScaleTo(wall2->GetTransform(), XMFLOAT3(0.1f, 10.0f, 20.0f));
    CPhysXRigidBody* wall_rigid_body2 = new CPhysXRigidBody(false);
    wall2->AddComponent(wall_rigid_body2);
    CPhysXBox* wall_physXBox2 = new CPhysXBox();
    wall_physXBox2->SetDebugView(true);
    wall2->AddComponent(wall_physXBox2);
    wall2->Start();

    Entity* wall3 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall3->GetTransform(), XMFLOAT3(0, 5.0f, -10.0f));
    Transform::ScaleTo(wall3->GetTransform(), XMFLOAT3(20.0f, 10.0f, 0.1f));
    CPhysXRigidBody* wall_rigid_body3 = new CPhysXRigidBody(false);
    wall3->AddComponent(wall_rigid_body3);
    CPhysXBox* wall_physXBox3 = new CPhysXBox();
    wall_physXBox3->SetDebugView(true);
    wall3->AddComponent(wall_physXBox3);
    wall3->Start();

    Entity* wall4 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall4->GetTransform(), XMFLOAT3(0, 5.0f, 10.0f));
    Transform::ScaleTo(wall4->GetTransform(), XMFLOAT3(20.0f, 10.0f, 0.1f));
    CPhysXRigidBody* wall_rigid_body4 = new CPhysXRigidBody(false);
    wall4->AddComponent(wall_rigid_body4);
    CPhysXBox* wall_physXBox4 = new CPhysXBox();
    wall_physXBox4->SetDebugView(true);
    wall4->AddComponent(wall_physXBox4);
    wall4->Start();

    //add a top wall
	Entity* wall5 = Manager::MakeEntity("wall");
	Transform::MoveTo(wall5->GetTransform(), XMFLOAT3(0, 10.0f, 0));
	Transform::ScaleTo(wall5->GetTransform(), XMFLOAT3(20.0f, 0.1f, 20.0f));
	CPhysXRigidBody* wall_rigid_body5 = new CPhysXRigidBody(false);
	wall5->AddComponent(wall_rigid_body5);
	CPhysXBox* wall_physXBox5 = new CPhysXBox();
	wall_physXBox5->SetDebugView(true);
	wall5->AddComponent(wall_physXBox5);
	wall5->Start();

    Entity* text = Manager::MakeEntity("score");
    Transform::MoveTo(text->GetTransform(), XMFLOAT3(0, 0, 0.0f));
    Transform::ScaleTo(text->GetTransform(), XMFLOAT3(200.0f, 100.0f, 0.0f));
    CText2D* textComponent = new CText2D();
    textComponent->SetFontColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
    textComponent->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD);
    textComponent->SetFontSize(50);
    textComponent->SetText(L"Score: 0");
    textComponent->SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    text->AddComponent(textComponent);
	text->Start();
}
