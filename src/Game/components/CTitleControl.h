#pragma once
#include "system/input.h"
#include "manager.h"
#include "scene/Load.h"
#include "scene/CrushGame.h"

class CTitleControl : public Component
{
public:
    CTitleControl() : Component("TitleControl",SceneControl){};
    ~CTitleControl() override = default;
    void Start() override{};
    void Update() override{
        if (Input::GetKeyTrigger(VK_SPACE))
        {
            Manager::SceneChange(new Load());
            /*Manager::UnloadCurrentScene();
            Manager::LoadScene(new CrushGame());*/
        }
    };
    void CleanUp() override{};
};
