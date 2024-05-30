#pragma once
#include "../main.h"
#include "../renderer.h"

#include "component.h"
#include "texture.h"

class Texture2D : public Texture
{
private:
    std::wstring texture_path_ = L"asset\\texture\\Rider.png";
    ID3D11ShaderResourceView* view_ = NULL;

public:
    Texture2D() : Texture("Texture2D") {}
Texture2D(const std::wstring& path) : Texture("Texture2D"), texture_path_(path) {}
    ~Texture2D() override = default;

    void Start() override
    {
        //Texture
        DirectX::TexMetadata metadata;
        DirectX::ScratchImage scratch_image;
        DirectX::LoadFromWICFile(texture_path_.c_str(),DirectX::WIC_FLAGS_NONE,&metadata,scratch_image);
        DirectX::CreateShaderResourceView(Renderer::GetDevice(),scratch_image.GetImages(),scratch_image.GetImageCount(),metadata,&view_);
        assert(view_);
    }
    void Update() override {}
    void CleanUp() override
    {
        view_->Release();
    }

    ID3D11ShaderResourceView* GetView()
    {
        return view_;
    }

    void SetTexturePath(const std::wstring& path) { texture_path_ = path; }
};
