#include "title.h"

#include "manager.h"
#include "components/CRect2D.h"
#include "components/CVideoTexture.h"
#include "components/CTitleControl.h"

void Title::Setup()
{
    Entity* rect2D = Manager::MakeEntity("rect2D");
    Transform::MoveTo(rect2D->GetTransform(),XMFLOAT3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f));
    Transform::ScaleTo(rect2D->GetTransform(),XMFLOAT3(static_cast<float>(SCREEN_WIDTH) / 100.0f,static_cast<float>(SCREEN_HEIGHT) / 100.0f, 1.0f));
    CRect2D* rect2DComponent = new CRect2D();
    CVideoTexture* video_texture = new CVideoTexture("asset/video/banana.mp4");
    video_texture->SetLoop(1);
    rect2DComponent->SetTexture(video_texture);
    rect2D->AddComponent(rect2DComponent);
    rect2D->AddComponent(video_texture);

    Entity* TitleControl = Manager::MakeEntity("TitleControl");
    TitleControl->AddComponent(new CTitleControl());

    rect2D->Start();
    TitleControl->Start();
}
