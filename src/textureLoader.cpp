#include "textureLoader.h"

#include "renderer.h"

std::unordered_map<std::wstring, ID3D11Texture2D*> TextureLoader::loaded_textures_;

ID3D11Texture2D* TextureLoader::LoadTexture(const std::wstring& path)
{
    if(loaded_textures_.find(path) != loaded_textures_.end())
    {
        return loaded_textures_[path];
    }
    else
    {
        DirectX::TexMetadata metadata;
        DirectX::ScratchImage scratch_image;
        HRESULT hr = DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratch_image);
        if (FAILED(hr)) return nullptr;

        ID3D11Texture2D* texture2D = nullptr;
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = static_cast<UINT>(metadata.width);
        desc.Height = static_cast<UINT>(metadata.height);
        desc.MipLevels = static_cast<UINT>(metadata.mipLevels);
        desc.ArraySize = static_cast<UINT>(metadata.arraySize);
        desc.Format = metadata.format;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        hr = Renderer::GetDevice()->CreateTexture2D(&desc, nullptr, &texture2D);
        if (FAILED(hr)) return nullptr;

        Renderer::GetDeviceContext()->UpdateSubresource(texture2D, 0, nullptr, scratch_image.GetImages()->pixels, static_cast<UINT>(scratch_image.GetImages()->rowPitch), static_cast<UINT>(scratch_image.GetImages()->slicePitch));

        /*ID3D11ShaderResourceView* view = nullptr;
        hr = Renderer::GetDevice()->CreateShaderResourceView(texture2D, nullptr, &view);
        if (FAILED(hr)) return nullptr;*/

        loaded_textures_[path] = texture2D;
        return texture2D;
    }
}
