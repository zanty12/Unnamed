#pragma once
#include "CTexture.h"
#include "renderer.h"
#include "component.h"

#include "traits/drawable.h"

class CTerrain : public Component, public Drawable
{
    //directx
    ID3D11Buffer* vertex_buffer_{};
	ID3D11Buffer* index_buffer_{};
    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};

    // Data
    std::string vertex_shader_path_ = "asset\\shader\\unlitTextureVS.cso";
    std::string pixel_shader_path_= "asset\\shader\\unlitTexturePS.cso";
    CTexture* texture_ = nullptr;
    XMFLOAT2 start_uv_ = XMFLOAT2(0.0f, 0.0f);
    XMFLOAT2 end_uv_ = XMFLOAT2(1.0f, 1.0f);
    VERTEX_3D vertex_[21][21];

public:
    CTerrain(): Component("Terrain",DrawCallers),Drawable(2){}
    void Start() override;
    void Update() override;
    void Draw() override;
    void CleanUp() override;
	void SetTexture(CTexture* texture) { texture_ = texture; }
	void SetEndUV(XMFLOAT2 end_uv) { end_uv_ = end_uv; }
	void SetStartUV(XMFLOAT2 start_uv) { start_uv_ = start_uv; }
	float GetHeight(XMFLOAT3 position);
};

