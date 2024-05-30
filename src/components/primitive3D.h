#pragma once
#include <d3d11.h>

#include "component.h"
#include "texture.h"
#include "../traits/drawable.h"
#include "../transform.h"

class Primitive3D : public Component, public Drawable
{
protected:
    //directx
    ID3D11Buffer* vertex_buffer_{};
    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};

    // Data
    std::string vertex_shader_path_ = "asset\\shader\\unlitTextureVS.cso";
    std::string pixel_shader_path_= "asset\\shader\\unlitTexturePS.cso";
    Transform transform_ = Transform::Identity();
    Texture* texture_ = nullptr;

public:
    Primitive3D() : Component("Primitive3D"){}
    void CleanUp() override;
    void SetTexture(Texture* texture) { texture_ = texture; }
};
