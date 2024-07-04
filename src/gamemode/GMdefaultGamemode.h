#pragma once
#include "manager.h"
#include "GameMode.h"
#include "scene/title.h"

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
    }
};
