#pragma once
#include "components/Component.h"

class CPlayerController : public Component
{
private:
    int animation_frame_ = 0;
    int forward_ = 0;
public:
    CPlayerController() : Component("Controller",Controller) {}
    ~CPlayerController() override = default;
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
};
