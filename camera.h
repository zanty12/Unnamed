#pragma once
#include "component.h"

class Camera : public Component
{
public:
     void Start() override;
     void Update() override;
     void CleanUp() override;
     void Draw();
};
