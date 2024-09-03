#include "title.h"

#include "manager.h"
#include "components/CRect2D.h"
#include "components/CText2D.h"
#include "components/CTexture2D.h"
#include "components/CVideoTexture.h"
#include "components/custom/CTitleControl.h"

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

    Entity* text = Manager::MakeEntity("text");
    Transform::MoveTo(text->GetTransform(),XMFLOAT3(SCREEN_WIDTH/2 - 110.0f,SCREEN_HEIGHT/2 - 200.0f, 0.0f));
    Transform::ScaleTo(text->GetTransform(),XMFLOAT3(150.0f,100.0f,0.0f));
    CText2D* textComponent = new CText2D();
    textComponent->SetText(L"Title");
    textComponent->SetFontColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    textComponent->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD);
    textComponent->SetFontSize(50);
    textComponent->SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    text->AddComponent(textComponent);

    rect2D->Start();
    TitleControl->Start();
    text->Start();
}
