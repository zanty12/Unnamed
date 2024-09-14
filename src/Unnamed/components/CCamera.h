#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include "../traits/drawable.h"

class CCamera : public Component, public Drawable
{
    DirectX::XMFLOAT3 offset_ = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);
    DirectX::XMFLOAT3 target_;
    DirectX::XMFLOAT4X4 view_matrix_;
    DirectX::XMFLOAT4X4 projection_matrix_;
    bool look_at_parent_ = false;
    bool active_ = false;
    bool smoothing_ = false;

public:
    CCamera() : Component("Camera",Camera), Drawable(0)
    {
    }

    void Start() override;
    void Update() override;
    void CleanUp() override;
    void Draw() override;
    void SetTarget(DirectX::XMFLOAT3 target) { target_ = target; }
    XMFLOAT3 GetTarget() const { return target_; }
    XMFLOAT3 GetOffset() const { return offset_; }
    void SetOffset(XMFLOAT3 offset) { offset_ = offset; }
    void SetLookAtParent(bool look) { look_at_parent_ = look; }
    bool GetActive() const { return active_; }
    void Activate();
    void Deactivate();
    void SetSmoothing(bool smooth) { smoothing_ = smooth; }
    bool GetSmoothing() const{ return smoothing_; }
    XMFLOAT4X4 GetViewMatrix() const{ return view_matrix_; }
    XMFLOAT4X4 GetProjectionMatrix() const { return projection_matrix_; }
};
