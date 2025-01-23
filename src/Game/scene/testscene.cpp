#include "testscene.h"
#include "manager.h"
#include "title.h"
#include "components/CAudio.h"
#include "prefab/player.h"
#include "components/CCamera.h"
#include "components/Shapes/CDirectXTKSphere.h"
#include "components/CModelRenderer.h"
#include "components/CParticleEmitter.h"
#include "components/PhysX/CPhysXBox.h"
#include "components/PhysX/CPhysXRigidBody.h"
#include "components/PhysX/CPhysXSphere.h"
#include "components/Shapes/CPlane.h"
#include "components/CTerrain.h"
#include "components/CRect2D.h"
#include "components/CSprite2D.h"
#include "components/CText2D.h"
#include "components/CTexture2D.h"
#include "components/CTitleControl.h"
#include "components/CVideoTexture.h"
#include "components/CWater.h"
#include "prefab/cube.h"
#include "prefab/enemy.h"
#include "prefab/explosion.h"
#include "prefab/Pinball.h"


void TestScene::Setup()
{
    /*Entity* rect2D = Manager::MakeEntity("rect2D");
    Transform::MoveTo(rect2D->GetTransform(),XMFLOAT3(200.0f,200.0f, 0.0f));
    CRect2D* rect2DComponent = new CRect2D();
    CTexture2D* texture2d = new CTexture2D();
    rect2DComponent->SetTexture(texture2d);
    rect2D->AddComponent(rect2DComponent);
    rect2D->AddComponent(texture2d);
    CAudio* bgm = new CAudio;
    bgm->Load("asset/sound/bgm.wav");
    rect2D->AddComponent(bgm);*/

    //create a cube
    Entity* cube = Manager::MakeEntity("Cube");
    Transform::MoveTo(cube->GetTransform(), XMFLOAT3(3.0f, 2.0f, -1.0f));
    Transform::ScaleTo(cube->GetTransform(),XMFLOAT3(2.0f,2.0f,2.0f));
    cube->SetTag("Cube");

    CModelRenderer* modelRenderer = new CModelRenderer();
    cube->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\WoodenCrate.obj");
    Transform local = Transform{ XMFLOAT3{0.0f, -1.6f, 0.0f}, XMFLOAT3{0.2f, 0.2f, 0.2f}, XMFLOAT4{0.0f,0.0f,0.0f,1.0f} };
    modelRenderer->SetLocalTransform(local);

    CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
    cube->AddComponent(rigidBody);
    CPhysXBox* physXBox = new CPhysXBox();
    physXBox->SetMaterial(1.0f, 1.0f, 0.0f);
    cube->AddComponent(physXBox);
    cube->Start();
    rigidBody->SetMass(100.0f);
    physXBox->SetQuery(false);
    rigidBody->SetLinearDamping(10.0f);
    rigidBody->SetAngularDamping(10.0f);
    rigidBody->LockAngularAxis(false, true, false);

    //create a cube
    Entity* cube2 = Manager::MakeEntity("Cube2");
    Transform::MoveTo(cube2->GetTransform(), XMFLOAT3(6.0f, 2.0f, -1.0f));
    Transform::ScaleTo(cube2->GetTransform(),XMFLOAT3(2.0f,2.0f,2.0f));
    cube2->SetTag("Cube");

    CModelRenderer* modelRenderer2 = new CModelRenderer();
    cube2->AddComponent(modelRenderer2);
    modelRenderer2->Load("asset\\model\\WoodenCrate.obj");
    Transform local2 = Transform{ XMFLOAT3{0.0f, -1.6f, 0.0f}, XMFLOAT3{0.2f, 0.2f, 0.2f}, XMFLOAT4{0.0f,0.0f,0.0f,1.0f} };
    modelRenderer2->SetLocalTransform(local2);

    CPhysXRigidBody* rigidBody2 = new CPhysXRigidBody(true);
    cube2->AddComponent(rigidBody2);
    CPhysXBox* physXBox2 = new CPhysXBox();
    physXBox2->SetMaterial(1.0f, 1.0f, 0.0f);
    cube2->AddComponent(physXBox2);
    cube2->Start();
    rigidBody2->SetMass(100.0f);
    physXBox2->SetQuery(false);
    rigidBody2->SetLinearDamping(10.0f);
    rigidBody2->SetAngularDamping(10.0f);
    rigidBody2->LockAngularAxis(false, true, false);


    //skybox
    Entity* skybox = Manager::MakeEntity("skybox");
    skybox->GetTransform().scale = XMFLOAT3(100, 100, 100);
    CModelRenderer* skybox_renderer = new CModelRenderer();
    skybox_renderer->Load("asset\\model\\sky.obj");
    skybox->AddComponent(skybox_renderer);
    skybox->Start();

    //a static sphere to act as an island
    Entity* island = Manager::MakeEntity("island");
    island->GetTransform().scale = XMFLOAT3(5, 5, 5);
    Transform::MoveTo(island->GetTransform(), XMFLOAT3(-5.0f, -2.0f, -4.0f));
    CPhysXRigidBody* island_rigid_body = new CPhysXRigidBody(true);
    island->AddComponent(island_rigid_body);
    island_rigid_body->SetDynamic(false);
    island_rigid_body->SetMass(0.0f);
    CPhysXSphere* island_sphere = new CPhysXSphere();
    island_sphere->SetRadius(1.0f);
    island_sphere->SetMaterial(1.0f, 1.0f, 0.0f);
    island_sphere->SetQuery(false);
    island->AddComponent(island_sphere);
    CModelRenderer* island_renderer = new CModelRenderer();
    island_renderer->Load("asset\\model\\island.obj");
    island->AddComponent(island_renderer);
    island->Start();

    //Create a plane
    Entity* plane = Manager::MakeEntity("Water");
	plane->GetTransform().scale = XMFLOAT3(100, 1.0, 100);
    CWater* water = new CWater();
    CTexture2D* texture_2d = new CTexture2D(L"asset/texture/water.png");
    water->SetTexture(texture_2d);
    plane->AddComponent(water);
    plane->AddComponent(texture_2d);
    plane->Start();
    water->SetEndUV(XMFLOAT2(1.0f, 1.0f));
    PhysX_Impl::GetScene()->addActor(*physx::PxCreatePlane(
        *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 1.0f),
        *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 1.0f))
    );

    //camera
    Entity* cam = Manager::MakeEntity("Camera");
    Transform::MoveBy(cam->GetTransform(), XMFLOAT3(0.0f, 2.0f, 0.0f));
    CCamera* camera = new CCamera();
    cam->AddComponent(camera);
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->Activate();
    camera->SetOffset(XMFLOAT3(0.0f, 3.0f, -10.0f));
    cam->Start();


    Entity* TitleControl = Manager::MakeEntity("TitleControl");
    TitleControl->AddComponent(new CTitleControl());
    Transform::MoveTo(TitleControl->GetTransform(), XMFLOAT3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
    Transform::ScaleTo(TitleControl->GetTransform(), XMFLOAT3(SCREEN_WIDTH/100.0f, SCREEN_HEIGHT/100.0f, 0.0f));
    CTexture2D* texture = new CTexture2D(L"asset/texture/title2.png");
    CRect2D* rect = new CRect2D();
    //rect->SetDrawPriority(10);
    rect->SetTexture(texture);
    TitleControl->AddComponent(rect);
    TitleControl->AddComponent(texture);
    TitleControl->Start();
}


