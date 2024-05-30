#pragma once
#include "scene.h"

class TestScene : public Scene
{
public:
    TestScene() = default;
    ~TestScene() override = default;
    void Setup() override;
};
