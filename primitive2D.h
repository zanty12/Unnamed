#pragma once
#include <d3d11.h>

#include "Component.h"
#include "drawables.h"

class Primitive2D : public Component, public Drawable
{
protected:
    // DirectX resources
    ID3D11Buffer* vertex_buffer_ = NULL;
    ID3D11ShaderResourceView* texture_ = NULL;
    ID3D11VertexShader* vertex_shader_ = NULL;
    ID3D11PixelShader* pixel_shader_ = NULL;
    ID3D11InputLayout* vertex_layout_ = NULL;

    // Data
    std::wstring texture_path_ = L"data/texture/Rider.png";
    std::string vertex_shader_path_ = "data/shader/unlitTextureVS.cso";
    std::string pixel_shader_path_= "data/shader/unlitTexturePS.cso";
public:
    Primitive2D() : Component("Primitive2D") {}
    virtual ~Primitive2D() = default;

    void CleanUp() override;

    void SetTexturePath(const std::wstring& path) { texture_path_ = path; }
    void SetVertexShaderPath(const std::string& path) { vertex_shader_path_ = path; }
    void SetPixelShaderPath(const std::string& path) { pixel_shader_path_ = path; }
    std::wstring GetTexturePath() const { return texture_path_; }
    std::string GetVertexShaderPath() const { return vertex_shader_path_; }
    std::string GetPixelShaderPath() const { return pixel_shader_path_; }
};
