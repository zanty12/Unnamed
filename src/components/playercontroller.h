#pragma once
#include "component.h"

class PlayerController : public Component
{
public:
    PlayerController() : Component("Controller") {}
    ~PlayerController() override = default;
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
};
