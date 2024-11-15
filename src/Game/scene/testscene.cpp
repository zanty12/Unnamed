﻿#include "testscene.h"
#include "manager.h"
#include "components/CAudio.h"
#include "prefab/player.h"
#include "components/CCamera.h"
#include "components/CParticleEmitter.h"
#include "components/CPlane.h"
#include "components/CTerrain.h"
#include "components/CRect2D.h"
#include "components/CSprite2D.h"
#include "components/CText2D.h"
#include "components/CTexture2D.h"
#include "components/CVideoTexture.h"
#include "prefab/enemy.h"
#include "prefab/explosion.h"


void TestScene::Setup()
{
    Entity* rect2D = Manager::MakeEntity("rect2D");
    Transform::MoveTo(rect2D->GetTransform(),XMFLOAT3(200.0f,200.0f, 0.0f));
    CRect2D* rect2DComponent = new CRect2D();
    CTexture2D* texture2d = new CTexture2D();
    rect2DComponent->SetTexture(texture2d);
    rect2D->AddComponent(rect2DComponent);
    rect2D->AddComponent(texture2d);
    CAudio* bgm = new CAudio;
    bgm->Load("asset/sound/bgm.wav");
    rect2D->AddComponent(bgm);


    Player* player = new Player();
    player->Start();
    //delete setup object after creating entity
    delete player;

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

    Entity* text = Manager::MakeEntity("score");
    Transform::MoveTo(text->GetTransform(),XMFLOAT3(0,0, 0.0f));
    Transform::ScaleTo(text->GetTransform(),XMFLOAT3(200.0f,100.0f,0.0f));
    CText2D* textComponent = new CText2D();
    textComponent->SetFontColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
    textComponent->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD);
    textComponent->SetFontSize(50);
    textComponent->SetText(L"Score: 0");
    textComponent->SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    text->AddComponent(textComponent);

    Entity* particle = Manager::MakeEntity("particle");
    CParticleEmitter* particleComponent = new CParticleEmitter();

    particle->AddComponent(particleComponent);

    //Create a plane
    Entity* plane = Manager::MakeEntity("Terrain");
	plane->GetTransform().scale = XMFLOAT3(100, 1.0, 100);
    CTerrain* planecomponent = new CTerrain();
    CTexture2D* texture_2d = new CTexture2D(L"asset/texture/cat.png");
    planecomponent->SetTexture(texture_2d);
    plane->AddComponent(planecomponent);
    plane->AddComponent(texture_2d);
    plane->Start();
    planecomponent->SetEndUV(XMFLOAT2(1.0f, 1.0f));
    PhysX_Impl::GetScene()->addActor(*physx::PxCreatePlane(
        *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 0),
        *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 0.5f))
    );

    rect2D->Start();
    bgm->Play(true);
    text->Start();
    particle->Start();
}


