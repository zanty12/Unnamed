#pragma once
#include <d3d11.h>

#include "Component.h"
#include "texture.h"
#include "../transform.h"
#include "../traits/drawable.h"

class Primitive2D : public Component, public Drawable
{
protected:
    // DirectX resources
    ID3D11Buffer* vertex_buffer_ = NULL;
    ID3D11VertexShader* vertex_shader_ = NULL;
    ID3D11PixelShader* pixel_shader_ = NULL;
    ID3D11InputLayout* vertex_layout_ = NULL;

    // Data
    std::string vertex_shader_path_ = "asset\\shader\\unlitTextureVS.cso";
    std::string pixel_shader_path_= "asset\\shader\\unlitTexturePS.cso";
    Transform transform_ = Transform::Identity();
    Texture* texture_ = nullptr;
public:
    Primitive2D() : Component("Primitive2D") {}
    virtual ~Primitive2D() = default;

    void CleanUp() override;

    void SetVertexShaderPath(const std::string& path) { vertex_shader_path_ = path; }
    void SetPixelShaderPath(const std::string& path) { pixel_shader_path_ = path; }
    void SetTransform(Transform target) {}
    void SetTexture(Texture* texture) { texture_ = texture; }

    std::string GetVertexShaderPath() const { return vertex_shader_path_; }
    std::string GetPixelShaderPath() const { return pixel_shader_path_; }
    Transform* GetTransform() {return &transform_;}

};
