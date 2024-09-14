#include "game.h"
#include "manager.h"
#include "components/CAudio.h"
#include "prefab/player.h"
#include "components/CCamera.h"
#include "components/CPlane.h"
#include "components/CRect2D.h"
#include "components/CSprite2D.h"
#include "components/CText2D.h"
#include "components/CTexture2D.h"
#include "components/CVideoTexture.h"
#include "components/CPlayerController.h"
#include "prefab/cube.h"
#include "components/CMouseCursor.h"
#include <components/CModelRenderer.h>


void Game::Setup()
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
    rect2D->AddComponent(bgm);
    rect2D->Start();
    bgm->Play(true);*/

    Entity* plane = Manager::MakeEntity("plane");
    CPlane* planecomponent = new CPlane();
    CTexture2D* texture_2d = new CTexture2D(L"asset/texture/calibrate.png");
    planecomponent->SetTexture(texture_2d);
    plane->AddComponent(planecomponent);
    plane->AddComponent(texture_2d);
    planecomponent->SetEndUV(XMFLOAT2(100.0f,100.0f));
    plane->Start();


    /*Cube* cube1 = new Cube();
    cube1->Start();
    delete cube1;*/

    Entity* Camera = Manager::MakeEntity("Camera");
    CCamera* camera = new CCamera();
    Camera->AddComponent(camera);
    camera->Activate();
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->SetOffset(XMFLOAT3(0.0f, 20.0f, -1.0f));
    Camera->AddComponent(new CPlayerController());
    Camera->Start();


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
    text->Start();

    Entity* mouse = Manager::MakeEntity("mouse");
    CMouseCursor* mouseComponent = new CMouseCursor();
    mouse->AddComponent(mouseComponent);
    CModelRenderer* model = new CModelRenderer();
    mouse->AddComponent(model);
    model->Load("asset\\model\\roundedcube.obj");
    mouse->Start();
}


