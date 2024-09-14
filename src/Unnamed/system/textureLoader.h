#pragma once
#include "main.h"
#include <string>
#include <unordered_map>

class TextureLoader
{
    static std::unordered_map<std::wstring, ID3D11Texture2D*> loaded_textures_;

public:
    static ID3D11Texture2D* LoadTexture(const std::wstring& path);

    static void CleanUp()
    {
        for (auto view : loaded_textures_)
        {
            view.second->Release();
        }
        loaded_textures_.clear();
    }
};
