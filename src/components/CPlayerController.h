#pragma once
#include "Component.h"

class CPlayerController : public Component
{
public:
    CPlayerController() : Component("Controller") {}
    ~CPlayerController() override = default;
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
};
