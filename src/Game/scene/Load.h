#pragma once
#include "scene.h"

class Load : public Scene
{
public:
     Load() = default;
     ~Load() override = default;
     void Setup() override;
};
