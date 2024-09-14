#pragma once
#include "components/Component.h"
#include "traits/drawable.h"
#include "traits/debugmenu.h"

class CMouseCursor : public Component, public DebugMenu
{
private:
    XMFLOAT3 mouse_world_pos_;
public:
    CMouseCursor() : Component("MouseCursor")
    {
    }
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
    void DrawMenu() override;
};
