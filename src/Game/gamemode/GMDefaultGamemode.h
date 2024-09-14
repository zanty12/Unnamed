#pragma once
#include "manager.h"
#include "GameMode.h"
#include "Game/scene/title.h"
#include "components/CText2D.h"

class DefaultGameMode : public GameMode
{
private:
    int point_ = 0;

public:
    DefaultGameMode() = default;
    ~DefaultGameMode() override = default;

    void Update() override
    {
        if (point_ >= 5)
        {
            point_ = 0;
            Manager::UnloadCurrentScene();
            Manager::LoadScene(new Title());
        }
    }

    void AddPoint()
    {
        point_++;
        Entity* score = Manager::FindEntityByName("score");
        if (score)
        {
            score->GetComponent<CText2D>()->SetText(L"Score: " + std::to_wstring(point_));
        }
    }
};
