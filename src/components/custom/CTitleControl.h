#pragma once
#include "system/input.h"
#include "manager.h"
#include "scene/game.h"
#include "scene/testscene.h"

class CTitleControl : public Component
{
public:
    CTitleControl() : Component("TitleControl"){};
    ~CTitleControl() override = default;
    void Start() override{};
    void Update() override{
        if (Input::GetKeyTrigger(VK_SPACE))
        {
            Manager::UnloadCurrentScene();
            Manager::LoadScene(new TestScene());
        }
    };
    void CleanUp() override{};
};
