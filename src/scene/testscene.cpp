#include "testscene.h"
#include "manager.h"
#include "objects/player.h"
#include "components/CCamera.h"
#include "components/CPlane.h"
#include "components/CRect2D.h"
#include "components/CSprite2D.h"
#include "components/CTexture2D.h"
#include "components/CVideoTexture.h"
#include "objects/bullet.h"
Player* player;

void TestScene::Setup()
{
    Entity* rect2D = Manager::MakeEntity("rect2D");
    Transform::MoveTo(rect2D->GetTransform(),XMFLOAT3(200.0f,200.0f, 0.0f));
    CRect2D* rect2DComponent = new CRect2D();
    CTexture2D* texture2d = new CTexture2D();
    rect2DComponent->SetTexture(texture2d);
    rect2D->AddComponent(rect2DComponent);
    rect2D->AddComponent(texture2d);

    Entity* plane = Manager::MakeEntity("plane");
    CPlane* planecomponent = new CPlane();
    CVideoTexture* video_texture = new CVideoTexture("asset/video/banana.mp4");
    video_texture->SetLoop(1);
    planecomponent->SetTexture(video_texture);
    plane->AddComponent(planecomponent);
    plane->AddComponent(video_texture);
    planecomponent->SetEndUV(XMFLOAT2(10.0f,10.0f));

    Entity* explosion = Manager::MakeEntity("explosion");
    Transform::ScaleTo(explosion->GetTransform(),XMFLOAT3(0.1f,0.1f,0.1f));
    Transform::RotateTo(explosion->GetTransform(),XMFLOAT3(-3.14f/2.0f,0.0,0.0f));
    CPlane* explosion_component = new CPlane();
    CSprite2D* sprite2d = new CSprite2D();
    sprite2d->SetWidth(4);
    sprite2d->SetHeight(4);
    sprite2d->SetLoop(0);
    sprite2d->SetFPS(16);
    explosion_component->SetBillboard(1);
    explosion_component->SetTexture(sprite2d);
    explosion->AddComponent(explosion_component);
    explosion->AddComponent(sprite2d);

    player = new Player();
    player->Start();

    rect2D->Start();
    plane->Start();
    explosion->Start();
}

