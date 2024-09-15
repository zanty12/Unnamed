#pragma once
#include "Component.h"
#include <d3d11.h>

class CTexture : public Component
{
public:
    CTexture() : Component("Texture",RenderResources) {}
    virtual ~CTexture() = default;

    virtual ID3D11ShaderResourceView* GetView() = 0;
};
