#pragma once
#include "Component.h"

class CTexture : public Component
{
public:
    CTexture() : Component("Texture",RenderResources) {}
    virtual ~CTexture() = default;

    virtual ID3D11ShaderResourceView* GetView() = 0;
};
