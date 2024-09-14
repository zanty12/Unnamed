#pragma once
#include "components/Component.h"

class CPlayerController : public Component
{
public:
    CPlayerController() : Component("Controller",Controller) {}
    ~CPlayerController() override = default;
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
};
