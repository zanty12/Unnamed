#pragma once
#include <DirectXMath.h>

#include "component.h"
#include "../traits/drawable.h"

class Camera : public Component, public Drawable
{
     DirectX::XMFLOAT3 position_;
     DirectX::XMFLOAT3 offset = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);
     DirectX::XMFLOAT3 target_;
     DirectX::XMFLOAT4X4 view_matrix_;

public:
     Camera() : Component("Camera"),Drawable(0) {}
     void Start() override;
     void Update() override;
     void CleanUp() override;
     void Draw() override;
     void SetTarget(DirectX::XMFLOAT3 target) { target_ = target;}
};
