#pragma once
#include <d3d11.h>

#include "component.h"
#include "traits/drawable.h"
#include "transform.h"

class Primitive3D : public Component, public Drawable
{
protected:
    ID3D11Buffer* vertex_buffer_{};
    ID3D11ShaderResourceView* texture_{};

    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};

    // Data
    std::wstring texture_path_ = L"data/texture/cat.png";
    std::string vertex_shader_path_ = "data/shader/unlitTextureVS.cso";
    std::string pixel_shader_path_= "data/shader/unlitTexturePS.cso";
    Transform transform_ = Transform::Identity();

public:
    Primitive3D() : Component("Primitive3D"){}
    void CleanUp() override;
};
