#pragma once
#include "scene.h"

class JointCrush : public Scene
{
public:
    JointCrush()  = default;
    ~JointCrush() override= default;
    void Setup() override;
};
