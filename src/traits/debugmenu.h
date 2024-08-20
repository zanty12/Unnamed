#pragma once
#include "manager.h"
#include "trait.h"
#include "imgui_impl_hal.h"

class DebugMenu : public Trait
{
public:
    DebugMenu() : Trait("DebugMenu")
    {
        Manager::RegisterDebugMenu(this);
    };
    virtual ~DebugMenu() = default;
    virtual void DrawMenu() = 0;
};
