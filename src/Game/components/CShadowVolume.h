#pragma once
#include "components/CModelRenderer.h"
#include "components/Component.h"
#include "DirectXTK/VertexTypes.h"
#include "traits/drawable.h"

class CShadowVolume : public Component, public Drawable
{
private:
    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};

    ID3D11ShaderResourceView* env_texture_;

    CModelRenderer* model_renderer_;
public:
    CShadowVolume() : Component("ShadowVolume", DrawCallers), Drawable(2) {}
    void Start() override;
    void Update() override;
    void Draw() override;
    void CleanUp() override;
};
