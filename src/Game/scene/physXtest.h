#pragma once
#include "scene.h"

class physXtest :public Scene
{
public:
    physXtest() = default;
    ~physXtest() override = default;
    void Setup() override;
};
