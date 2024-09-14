#pragma once
#include "scene.h"

class Game : public Scene
{
public:
    Game() = default;
    ~Game() override = default;
    void Setup() override;
};
