#pragma once
#include <d3d11.h>

#include "components/Component.h"
#include "components/CTexture.h"
#include "processpriority.h"
#include "traits/drawable.h"

class CPrimitive3D : public Component, public Drawable
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
    CTexture* texture_ = nullptr;

public:
    CPrimitive3D() : Component("Primitive3D",DrawCallers),Drawable(2){}
    void CleanUp() override;
    void SetTexture(CTexture* texture) { texture_ = texture; }
};
