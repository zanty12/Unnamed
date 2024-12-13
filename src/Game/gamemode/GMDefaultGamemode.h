#pragma once
#include "manager.h"
#include "GameMode.h"
#include "scene/title.h"
#include "components/CText2D.h"

class DefaultGameMode : public GameMode
{
public:
    DefaultGameMode() = default;
    ~DefaultGameMode() override = default;

    void Update() override
    {}

};
