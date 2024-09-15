#pragma once
#include "scene.h"

class CrushGame : public Scene
{
public:
    CrushGame()  = default;
    ~CrushGame() override= default;
    void Setup() override;
};
