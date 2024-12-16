#pragma once
#include "scene.h"

class StencilTest : public Scene
{
public:
    StencilTest() = default;
    ~StencilTest() override = default;
    void Setup() override;
};
