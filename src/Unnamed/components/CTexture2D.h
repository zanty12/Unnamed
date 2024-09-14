#pragma once
#include "../main.h"
#include "../renderer.h"

#include "CTexture.h"
#include "system/textureLoader.h"

class CTexture2D : public CTexture
{
private:
    std::wstring texture_path_ = L"asset\\texture\\Rider.png";
    ID3D11Texture2D* texture_resource_ = NULL;

public:
    CTexture2D() = default;

    CTexture2D(const std::wstring& path) :texture_path_(path)
    {
    }

    ~CTexture2D() override = default;

    void Start() override
    {
        //Texture
        /*DirectX::TexMetadata metadata;
        DirectX::ScratchImage scratch_image;
        DirectX::LoadFromWICFile(texture_path_.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratch_image);
        DirectX::CreateShaderResourceView(Renderer::GetDevice(), scratch_image.GetImages(),
                                          scratch_image.GetImageCount(), metadata, &texture_resource_);*/
        texture_resource_ = TextureLoader::LoadTexture(texture_path_);
        assert(texture_resource_);
    }

    void Update() override
    {
    }

    void CleanUp() override
    {
        texture_resource_->Release();
    }

    ID3D11ShaderResourceView* GetView()
    {
        ID3D11ShaderResourceView* view = nullptr;
        HRESULT hr = Renderer::GetDevice()->CreateShaderResourceView(texture_resource_, nullptr, &view);
        if (FAILED(hr)) return nullptr;
        return view;
    }

    void SetTexturePath(const std::wstring& path) { texture_path_ = path; }
};
