#pragma once
#include "component.h"

class Controller : public Component
{
public:
    Controller() : Component("Controller") {}
    void Start() override;
    void Update(Entity* parent) override;
    void CleanUp() override;
};
