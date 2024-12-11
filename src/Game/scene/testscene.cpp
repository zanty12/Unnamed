#include "testscene.h"
#include "manager.h"
#include "components/CAudio.h"
#include "prefab/player.h"
#include "components/CCamera.h"
#include "components/CDirectXTKSphere.h"
#include "components/CModelRenderer.h"
#include "components/CParticleEmitter.h"
#include "components/CPhysXBox.h"
#include "components/CPhysXRigidBody.h"
#include "components/CPhysXSphere.h"
#include "components/CPlane.h"
#include "components/CTerrain.h"
#include "components/CRect2D.h"
#include "components/CSprite2D.h"
#include "components/CText2D.h"
#include "components/CTexture2D.h"
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
    Transform::MoveTo(cube->GetTransform(), XMFLOAT3(3.0f, 5.0f, 0.0f));
    cube->SetTag("Cube");

    CModelRenderer* modelRenderer = new CModelRenderer();
    cube->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\roundedcube.obj");
    //Transform local = Transform{ XMFLOAT3{0.0f, -0.5f, 0.0f}, XMFLOAT3{1.0f, 1.0f, 1.0f}, XMFLOAT4{0.0f,0.0f,0.0f,1.0f} };
    //modelRenderer->SetLocalTransform(local);

    CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
    cube->AddComponent(rigidBody);
    CPhysXBox* physXBox = new CPhysXBox();
    physXBox->SetMaterial(1.0f, 1.0f, 0.0f);
    cube->AddComponent(physXBox);
    cube->Start();
    rigidBody->SetMass(10.0f);
    physx::PxRigidActor* actor = rigidBody->GetActor();
    physXBox->SetQuery(false);

    /*Player* player = new Player();
    player->Start();
    //delete setup object after creating entity
    delete player;*/

    /*Enemy* enemy = new Enemy();
    enemy->Start();
    Transform::MoveBy(enemy->GetEntity()->GetTransform(),XMFLOAT3(-4.0f,0.0f, 5.0f));
    delete enemy;

    Enemy* enemy2 = new Enemy();
    enemy2->Start();
    Transform::MoveBy(enemy2->GetEntity()->GetTransform(),XMFLOAT3(-2.0f,0.0f, 5.0f));
    delete enemy2;

    Enemy* enemy3 = new Enemy();
    enemy3->Start();
    Transform::MoveBy(enemy3->GetEntity()->GetTransform(),XMFLOAT3(0.0f,0.0f, 5.0f));
    delete enemy3;

    Enemy* enemy4 = new Enemy();
    enemy4->Start();
    Transform::MoveBy(enemy4->GetEntity()->GetTransform(),XMFLOAT3(2.0f,0.0f, 5.0f));
    delete enemy4;

    Enemy* enemy5 = new Enemy();
    enemy5->Start();
    Transform::MoveBy(enemy5->GetEntity()->GetTransform(),XMFLOAT3(4.0f,0.0f, 5.0f));
    delete enemy5;*/

    /*Entity* text = Manager::MakeEntity("score");
    Transform::MoveTo(text->GetTransform(),XMFLOAT3(0,0, 0.0f));
    Transform::ScaleTo(text->GetTransform(),XMFLOAT3(200.0f,100.0f,0.0f));
    CText2D* textComponent = new CText2D();
    textComponent->SetFontColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
    textComponent->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD);
    textComponent->SetFontSize(50);
    textComponent->SetText(L"Score: 0");
    textComponent->SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    text->AddComponent(textComponent);*/

    /*Entity* particle = Manager::MakeEntity("particle");
    CParticleEmitter* particleComponent = new CParticleEmitter();

    particle->AddComponent(particleComponent);*/

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
        *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 0.5f),
        *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f))
    );

    //camera
    Entity* cam = Manager::MakeEntity("Camera");
    CCamera* camera = new CCamera();
    cam->AddComponent(camera);
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->Activate();
    cam->Start();

    //skybox
    Entity* skybox = Manager::MakeEntity("skybox");
    skybox->GetTransform().scale = XMFLOAT3(100, 100, 100);
    CModelRenderer* skybox_renderer = new CModelRenderer();
    skybox_renderer->Load("asset\\model\\sky.obj");
    skybox->AddComponent(skybox_renderer);
    skybox->Start();

    //a static sphere to act as a island
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

    /*Pinball* player = new Pinball();
    player->Start();
    //delete setup object after creating entity
    delete player;*/

    /*rect2D->Start();
    bgm->Play(true);*/
    /*text->Start();*/
    /*particle->Start();*/
}


