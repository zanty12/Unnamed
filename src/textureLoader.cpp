#include "textureLoader.h"

#include "renderer.h"

std::unordered_map<std::wstring, ID3D11ShaderResourceView*> TextureLoader::loaded_textures_;

ID3D11ShaderResourceView* TextureLoader::LoadTexture(const std::wstring& path)
{
    //if texture is already loaded
    if(loaded_textures_.find(path) != loaded_textures_.end())
    {
        return loaded_textures_[path];
    }
    else
    {
        DirectX::TexMetadata metadata;
        DirectX::ScratchImage scratch_image;
        DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, scratch_image);
        ID3D11ShaderResourceView* view;
        DirectX::CreateShaderResourceView(Renderer::GetDevice(), scratch_image.GetImages(),
                                          scratch_image.GetImageCount(), metadata, &view);
        loaded_textures_[path] = view;
        return loaded_textures_[path];
    }
}
