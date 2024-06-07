#include "testscene.h"
#include "manager.h"
#include "objects/player.h"
#include "components/camera.h"
#include "components/plane.h"
#include "components/rect2D.h"
#include "components/texture2D.h"
#include "components/videotexture.h"
#include "objects/bullet.h"
Player* player;

void TestScene::Setup()
{
    Entity* rect2D = Manager::MakeEntity("rect2D");
    Transform::MoveTo(rect2D->GetTransform(),XMFLOAT3(200.0f,200.0f, 0.0f));
    Rect2D* rect2DComponent = new Rect2D();
    Texture2D* texture2d = new Texture2D();
    rect2DComponent->SetTexture(texture2d);
    rect2D->AddComponent(rect2DComponent);
    rect2D->AddComponent(texture2d);

    Entity* plane = Manager::MakeEntity("plane");
    Plane* planecomponent = new Plane();
    VideoTexture* video_texture = new VideoTexture("asset/video/banana.mp4");
    video_texture->SetLoop(1);
    planecomponent->SetTexture(video_texture);
    plane->AddComponent(planecomponent);
    plane->AddComponent(video_texture);

    player = new Player();
    player->Start();

    rect2D->Start();
    plane->Start();
}

