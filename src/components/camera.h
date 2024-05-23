#pragma once
#include <DirectXMath.h>

#include "component.h"
#include "../traits/drawable.h"

class Camera : public Component, public Drawable
{
     DirectX::XMFLOAT3 position_;
     DirectX::XMFLOAT3 target_;
     DirectX::XMFLOAT4X4 view_matrix_;

public:
     Camera() : Component("Camera"),Drawable() {}
     void Start() override;
     void Update(Entity* parent) override;
     void CleanUp() override;
     void Draw() override;
};
