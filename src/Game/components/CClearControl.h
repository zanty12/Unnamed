#pragma once
#include "system/input.h"
#include "manager.h"
#include "scene/Title.h"
#include "scene/CrushGame.h"

class CClearControl : public Component
{
public:
    CClearControl() : Component("ClearControl", SceneControl) {};
    ~CClearControl() override = default;
    void Start() override {};
    void Update() override {
        if (Input::GetKeyTrigger(VK_SPACE))
        {
            Manager::SceneChange(new Title());
            /*Manager::UnloadCurrentScene();
            Manager::LoadScene(new CrushGame());*/
        }
    };
    void CleanUp() override {};
};
