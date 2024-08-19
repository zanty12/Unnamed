#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include "../traits/drawable.h"

class CCamera : public Component, public Drawable
{
    DirectX::XMFLOAT3 position_;
    DirectX::XMFLOAT3 offset_ = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);
    DirectX::XMFLOAT3 target_;
    DirectX::XMFLOAT4X4 view_matrix_;
    DirectX::XMFLOAT4X4 projection_matrix_;
    bool look_at_parent_ = false;
    bool active_ = false;

public:
    CCamera() : Component("Camera"), Drawable(0)
    {
    }

    void Start() override;
    void Update() override;
    void CleanUp() override;
    void Draw() override;
    void SetTarget(DirectX::XMFLOAT3 target) { target_ = target; }
    XMFLOAT3 GetOffset() { return offset_; }
    void SetOffset(XMFLOAT3 offset) { offset_ = offset; }
    void SetLookAtParent(bool look) { look_at_parent_ = look; }
    XMFLOAT3 GetPosition() { return position_; }
    bool GetActive() const { return active_; }
    void Activate();
    void Deactivate();
    XMFLOAT4X4 GetViewMatrix() { return view_matrix_; }
    XMFLOAT4X4 GetProjectionMatrix() { return projection_matrix_; }
};
