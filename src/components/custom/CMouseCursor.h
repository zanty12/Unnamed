#pragma once
#include "components/Component.h"
#include "traits/drawable.h"

class CMouseCursor : public Component
{
private:
    bool draw_ = true;
public:
    CMouseCursor() : Component("MouseCursor")
    {
    }
    void Start() override{}
    void Update() override;
    void CleanUp() override{}
};
