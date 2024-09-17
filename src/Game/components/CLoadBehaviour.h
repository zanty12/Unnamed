#pragma once
#include "components/component.h"

class CLoadBehaviour : public Component
{
private:
    float timer_ = 2.0f;
public:
    CLoadBehaviour() : Component("LoadBehaviour",SceneControl) {}
    void Start() override{};
    void Update() override;
    void CleanUp() override{}
};
