#pragma once
#include "GameMode.h"

class Shooting : public GameMode
{
private:
    int point_ = 0;
public:
    Shooting() = default;
    ~Shooting() override = default;
    void Update() override;
    void AddPoint();
};
