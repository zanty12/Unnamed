#include "GMShooting.h"
#include "manager.h"
#include "components/CText2D.h"
#include "scene/title.h"

void Shooting::Update()
{
    if (point_ >= 5)
    {
        point_ = 0;
        Manager::UnloadCurrentScene();
        Manager::LoadScene(new Title());
    }
}

void Shooting::AddPoint()
{
    point_++;
    Entity* score = Manager::FindEntityByName("score");
    if (score)
    {
        score->GetComponent<CText2D>()->SetText(L"Score: " + std::to_wstring(point_));
    }
}