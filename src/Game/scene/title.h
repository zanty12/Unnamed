#pragma once
#include "scene.h"

class Title : public Scene
{
public:
    Title() = default;
    ~Title() override = default;
    void Setup() override;
};
