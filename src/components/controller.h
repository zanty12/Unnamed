#pragma once
#include "component.h"

class Controller : public Component
{
public:
    Controller() : Component("Controller") {}
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
};
