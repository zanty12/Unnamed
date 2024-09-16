#pragma once
#include <memory>

#include "CTexture.h"
#include "components/Component.h"
#include "DirectXTK/GeometricPrimitive.h"
#include "DirectXTK/SimpleMath.h"
#include "traits/drawable.h"

enum DrawType
{
    SOLID,
    WIREFRAME,
    TEXTURED
};

class CDirectXTKPrimitive : public Component, public Drawable
{
protected:
    std::unique_ptr<DirectX::GeometricPrimitive> primitive_;
    DrawType draw_type_ = SOLID;
    SimpleMath::Color color_ = SimpleMath::Color(0.0f, 1.0f, 0.0f, 1.0f);
    CTexture* texture_ = nullptr;
    XMFLOAT4X4 world_matrix_;
    XMFLOAT4X4 original_view_, original_proj_;

public:
    CDirectXTKPrimitive() : Component("DirectXTKPrimitive", DrawCallers), Drawable(10)
    {
    }

    ~CDirectXTKPrimitive() override = default;
    virtual void Start() = 0;
    void Update() override;
    void Draw() override;
    void SetDrawType(DrawType draw_type) { draw_type_ = draw_type; }
    void SetColor(SimpleMath::Color color) { color_ = color; }
    void SetTexture(CTexture* texture) { texture_ = texture; }
    virtual void CleanUp() =0;
};
