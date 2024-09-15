#pragma once
#include "scene.h"

class CubeGame : public Scene
{
public:
    CubeGame() = default;
    ~CubeGame() override = default;
    void Setup() override;
};
