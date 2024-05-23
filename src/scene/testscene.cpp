#include "testscene.h"
#include "../manager.h"
#include "../objects/player.h"
#include "../components/camera.h"
#include "../components/controller.h"
#include "../components/plane.h"
#include "../components/rect2D.h"
Player* player;

void TestScene::Setup()
{
    Entity* rect2D = Manager::MakeEntity("rect2D");
    rect2D->AddComponent(new Rect2D());
    Entity* camera = Manager::MakeEntity("camera");
    camera->AddComponent(new Camera());
    Entity* plane = Manager::MakeEntity("plane");
    plane->AddComponent(new Plane());

    player = new Player();


    rect2D->Start();
    camera->Start();
    plane->Start();
    player->Start();
}

